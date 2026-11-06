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

        float pdflight;
        EmitterQueryRecord emitterRecord(its.p);

        // Sample one of the lights in the scene randomly and get its pdf
        const Emitter* em = scene->sampleEmitter(sampler->next1D(), pdflight);
        
        // Here we sample the point sources, getting its radiance
        // and direction.
        Color3f Le = em->sample(emitterRecord, sampler->next2D(), 0.);

        // Here perform a visibility query, to check whether the light
        // source "em" is visible from the intersection point.
        // For that, we create a ray object (shadow ray)
        // and compute the intersection

        // Check if the light source is below the surface
        float cosTheta = its.shFrame.n.dot(emitterRecord.wi);
        if (cosTheta <= 0.0f){
            return Lo; // The light source is below the surface, return 0
        }
            
        Intersection its_shadow;
        if(scene->rayIntersect(Ray3f(its.p + its.shFrame.n * Epsilon, emitterRecord.wi), its_shadow) && its_shadow.t <= emitterRecord.dist){
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
        // For each light, we accomulate the incident light times the
        // foreshortening times the BSDF term (i.e. the render equation).

        // Divide by the product of the  pdf of choosing the light source and the pdf of choosing the point on the light source
        Lo += (Le * cosTheta * its.mesh->getBSDF()->eval(bsdfRecord)) / (pdflight * emitterRecord.pdf);
        
        return Lo;
    }

    std::string toString() const {
        return "Direct Emitter Sampling []";
    }
};

NORI_REGISTER_CLASS(DirectEmitterSampling, "direct_ems");
NORI_NAMESPACE_END