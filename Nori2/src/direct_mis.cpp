#include <nori/warp.h>
#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>

NORI_NAMESPACE_BEGIN

class DirectMIS: public Integrator {
public:
    DirectMIS(const PropertyList& props) {
        // No parameters this time
    }

    /// Balance heuristic for Multiple Importance Sampling
    static inline float balanceHeuristic(float fPdf, float gPdf) {
        float sum = fPdf + gPdf;
        if (sum <= 0.0f)
            return 0.0f;
        return fPdf / sum;
    }

    Color3f Li(const Scene* scene, Sampler* sampler, const Ray3f& ray) const {
        Color3f Lo(0.0f);

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
        if (!bsdf)
            return Lo;

        //Emitter Sampling Strategy (EMS)
        float pdflight = 0.0f;
        const Emitter* em = scene->sampleEmitter(sampler->next1D(), pdflight);
        if (pdflight > 0.0f && em) {
            EmitterQueryRecord emitterRecord(its.p);
            Color3f Le = em->sample(emitterRecord, sampler->next2D(), 0.0f);
            if (emitterRecord.pdf > 0.0f && !Le.isZero()) {
                float cosTheta = its.shFrame.n.dot(emitterRecord.wi);
                if (cosTheta > 0.0f) {
                    Ray3f shadowRay(its.p, emitterRecord.wi, Epsilon, emitterRecord.dist * (1.0f - 1e-4f));
                    if (!scene->rayIntersect(shadowRay)) {
                        BSDFQueryRecord bsdfRecord(its.toLocal(-ray.d), its.toLocal(emitterRecord.wi), its.uv, ESolidAngle);
                        Color3f f = bsdf->eval(bsdfRecord);
                        if (!f.isZero()) {
                            float pdf_ems = pdflight * emitterRecord.pdf;
                            float pdf_mats = bsdf->pdf(bsdfRecord);

                            float w_ems = balanceHeuristic(pdf_ems, pdf_mats);
                            Lo += w_ems * (Le * cosTheta * f) / pdflight;
                        }
                    }
                }
            }
        }

        // Material Sampling Strategy (MATS)
        BSDFQueryRecord bRec(its.toLocal(-ray.d), its.uv);
        Color3f weight = bsdf->sample(bRec, sampler->next2D());
        if (!weight.isZero()) {
            Vector3f wo = its.toWorld(bRec.wo);
            Ray3f bsdfRay(its.p, wo);
            Intersection its_light;
            if (scene->rayIntersect(bsdfRay, its_light)) {
                if (its_light.mesh->isEmitter()) {
                    EmitterQueryRecord emitterRecord(its_light.mesh->getEmitter(), its.p, its_light.p, its_light.shFrame.n, its_light.uv);
                    Color3f Le = its_light.mesh->getEmitter()->eval(emitterRecord);
                    if (!Le.isZero()) {
                        float w_mats = 1.0f;
                        if (bRec.measure != EDiscrete) {
                            float pdf_mats = bsdf->pdf(bRec);
                            float pdflight_mats = scene->pdfEmitter(its_light.mesh->getEmitter());
                            float pdf_ems = pdflight_mats * its_light.mesh->getEmitter()->pdf(emitterRecord);

                            w_mats = balanceHeuristic(pdf_mats, pdf_ems);
                        }
                        Lo += w_mats * Le * weight;
                    }
                }
            } else {
                float pdf_env = 0.0f;
                Color3f Le = scene->getBackground(bsdfRay, pdf_env);
                if (!Le.isZero()) {
                    float w_mats = 1.0f;
                    if (bRec.measure != EDiscrete) {
                        float pdf_mats = bsdf->pdf(bRec);
                        float pdflight_env = 1.0f / float(scene->getLights().size());
                        float pdf_ems = pdflight_env * pdf_env;

                        w_mats = balanceHeuristic(pdf_mats, pdf_ems);
                    }
                    Lo += w_mats * Le * weight;
                }
            }
        }

        return Lo;
    }

    std::string toString() const {
        return "Direct MIS []";
    }
};

NORI_REGISTER_CLASS(DirectMIS, "direct_mis");
NORI_NAMESPACE_END
