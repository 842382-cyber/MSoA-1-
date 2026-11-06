#include <nori/warp.h>
#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>

NORI_NAMESPACE_BEGIN

class DirectWhittedIntegrator: public Integrator {
public:
    DirectWhittedIntegrator(const PropertyList& props) {
        // No parameters this time
    }

    Color3f Li(const Scene* scene, Sampler* sampler, const Ray3f& ray) const {

        Color3f Lo(0.);
        
        // Find the surface that is visible in the requested direction
        Intersection its;

        if (!scene->rayIntersect(ray, its))
            return scene->getBackground(ray);

        EmitterQueryRecord emitterRecord(its.p);

        // Get all lights in the scene
        const std::vector<Emitter*> lights = scene->getLights();
        
        // Let's iterate over all emitters
        for (unsigned int i = 0; i <lights.size(); ++i)
        {
            const Emitter* em = lights[i];
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
                continue; // The light source is below the surface, skip to the next light
            }

            Intersection its_shadow;            
            if(scene->rayIntersect(Ray3f(its.p + its.shFrame.n * Epsilon, emitterRecord.wi), its_shadow) && its_shadow.t <= emitterRecord.dist){
                continue; // The light source is occluded, skip to the next light
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
            Lo += Le * cosTheta * its.mesh->getBSDF()->eval(bsdfRecord);
        }
        return Lo;
    }

    std::string toString() const {
        return "Direct Whitted Integrator []";
    }
};

NORI_REGISTER_CLASS(DirectWhittedIntegrator, "direct_whitted");
NORI_NAMESPACE_END