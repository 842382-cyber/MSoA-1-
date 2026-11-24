#include <nori/warp.h>
#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>

NORI_NAMESPACE_BEGIN

class PathTracingMIS: public Integrator {
public:
    PathTracingMIS(const PropertyList& props) {
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

        const BSDF* bsdf = its.mesh->getBSDF();
        if(!bsdf){
            return Lo;
        }

        BSDFQueryRecord bRec(its.toLocal(-ray.d), its.uv);
        Color3f weight = bsdf->sample(bRec, sampler->next2D());

        if (weight.isZero()) {
            return Lo;
        }

        Vector3f wo = its.toWorld(bRec.wo);
            
        Ray3f bsdfRay(its.p, wo);
        Intersection its_light;
        if (scene->rayIntersect(bsdfRay, its_light)) {
            if (its_light.mesh->isEmitter()){
                EmitterQueryRecord emitterRecord(its_light.mesh->getEmitter(), its.p, its_light.p, its_light.shFrame.n, its_light.uv);
                Color3f Le = its_light.mesh->getEmitter()->eval(emitterRecord);

                // bsdf->sample() returns (fr * cos(theta)) / pdf
                Lo += Le * weight;
            }
        } else {
            Lo += scene->getBackground(bsdfRay) * weight;
        }
        
        return Lo;
    }

    std::string toString() const {
        return "Path Tracing MIS []";
    }
};

NORI_REGISTER_CLASS(PathTracingMIS, "path_mis");
NORI_NAMESPACE_END
