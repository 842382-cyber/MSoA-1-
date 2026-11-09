#include <nori/warp.h>
#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>

NORI_NAMESPACE_BEGIN

class DirectEmitterSampling: public Integrator {
public:
    DirectEmitterSampling(const PropertyList& props) {
        // No parameters this time
    }

    Color3f Li(const Scene* scene, Sampler* sampler, const Ray3f& ray) const {

        Color3f Lo(0.);
        
        // Find the surface that is visible in the requested direction
        Intersection its;

        if (!scene->rayIntersect(ray, its))
            return scene->getBackground(ray);

        if (its.mesh->isEmitter()){
            // If the intersection point is on an emitter, add its emitted radiance
            EmitterQueryRecord emitterRecord(its.mesh->getEmitter(), ray.o, its.p, its.shFrame.n, its.uv);
            Lo += its.mesh->getEmitter()->eval(emitterRecord);
        }

        if (scene->getLights().empty())
            return Lo;

        float pdflight;
        // Sample one of the lights in the scene randomly and get its pdf
        const Emitter* em = scene->sampleEmitter(sampler->next1D(), pdflight);
        if(pdflight <= 0.f){
            return Lo; // The pdf is invalid, return 0
        }
        
        EmitterQueryRecord emitterRecord(its.p);

        // Here we sample the light source, getting its importance weight (Le / pdf)
        // and direction.
        Color3f Le = em->sample(emitterRecord, sampler->next2D(), 0.);
        if(emitterRecord.pdf <= 0.f || Le.isZero()){
            return Lo; // The pdf is invalid or the radiance is zero, return 0
        }

        // Check if the light source is in the positive hemisphere of the shading normal
        float cosTheta = its.shFrame.n.dot(emitterRecord.wi);
        if (cosTheta <= 0.0f){
            return Lo; // The light source is below the surface, return 0
        }
            
        Ray3f shadowRay(its.p, emitterRecord.wi, Epsilon, emitterRecord.dist * (1.0f - 1e-4f));
        if (scene->rayIntersect(shadowRay)) {
            return Lo; // The light source is occluded, return 0
        }

        // Finally, we evaluate the BSDF. For that, we need to build
        // a BSDFQueryRecord from the outgoing direction (the direction
        // of the primary ray, in ray.d), and the incoming direction
        // (the direction to the light source, in emitterRecord.wi).
        // Note that: a) the BSDF assumes directions in the local frame
        // of reference; and b) that both the incoming and outgoing
        // directions are assumed to start from the intersection point.
        BSDFQueryRecord bsdfRecord(its.toLocal(-ray.d), its.toLocal(emitterRecord.wi), its.uv, ESolidAngle);

        // em->sample() already returns Le / emitterRecord.pdf, so we only divide by pdflight
        Lo += (Le * cosTheta * its.mesh->getBSDF()->eval(bsdfRecord)) / pdflight;
        
        return Lo;
    }

    std::string toString() const {
        return "Direct Emitter Sampling []";
    }
};

NORI_REGISTER_CLASS(DirectEmitterSampling, "direct_ems");
NORI_NAMESPACE_END