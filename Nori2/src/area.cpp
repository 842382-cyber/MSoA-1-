/*
    This file is part of Nori, a simple educational ray tracer

    Copyright (c) 2015 by Wenzel Jakob
	
	v1 - Dec 01 2020
	Copyright (c) 2020 by Adrian Jarabo

    Nori is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    Nori is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <nori/emitter.h>
#include <nori/warp.h>
#include <nori/mesh.h>
#include <nori/texture.h>

NORI_NAMESPACE_BEGIN

class AreaEmitter : public Emitter {
public:
	AreaEmitter(const PropertyList &props) {
		m_type = EmitterType::EMITTER_AREA;
		m_radiance = new ConstantSpectrumTexture(props.getColor("radiance", Color3f(1.f)));
		m_scale = props.getFloat("scale", 1.);
	}

	virtual std::string toString() const {
		return tfm::format(
			"AreaLight[\n"
			"  radiance = %s,\n"
			"  scale = %f,\n"
			"]",
			m_radiance->toString(), m_scale);
	}

	// We don't assume anything about the visibility of points specified in 'ref' and 'p' in the EmitterQueryRecord.
	virtual Color3f eval(const EmitterQueryRecord & lRec) const {
		if (!m_mesh)
			throw NoriException("There is no shape attached to this Area light!");

		// This function call can be done by bsdf sampling routines.
		// Hence the ray was already traced for us - i.e a visibility test was already performed.
		// Hence just check if the associated normal in emitter query record and incoming direction are not backfacing

    /* Area lights only emit on the front side */
    if (lRec.n.dot(-lRec.wi) <= 0.0f)
        return Color3f(0.0f);

    /* Return emitted radiance */
    return m_scale * m_radiance->eval(lRec.uv);
}


	virtual Color3f sample(EmitterQueryRecord & lRec, const Point2f & sample, float optional_u) const {
		if (!m_mesh)
			throw NoriException("There is no shape attached to this Area light!");

    /* Sample a point on the mesh surface*/
    m_mesh->samplePosition(
        sample,   // random 2D sample
        lRec.p,   // sampled position on light
        lRec.n,   // sampled normal
        lRec.uv   // sampled texture coordinates
    );
	
	/* Sample a point on the mesh surface*/
    lRec.wi = lRec.p - lRec.ref;
    
    lRec.dist = lRec.wi.norm(); /* Store the distance */

    
    if (lRec.dist <= Epsilon) /* Avoid divisions by zero */
        return Color3f(0.0f);

    lRec.wi /= lRec.dist;	/* Normalize the direction vector */

	/* Reject samples coming from the back side of the area light*/
	float cosTheta = lRec.n.dot(-lRec.wi);
	
	if (cosTheta <= 0.0f) /* Area lights only emit on the front side */
		return Color3f(0.0f);

    /* Convert the mesh area pdf into a solid-angle pdf */
    float pdfArea = m_mesh->pdf(lRec.p);

    lRec.pdf =
        pdfArea *
        (lRec.dist * lRec.dist) /
        cosTheta;

    if (lRec.pdf <= 0.0f)
        return Color3f(0.0f);	
	
	Color3f Le = m_scale * m_radiance->eval(lRec.uv); /* Evaluate emitted radiance */
	
	return Le / lRec.pdf;

	}

	// Returns probability with respect to solid angle given by all the information inside the emitterqueryrecord.
	// Assumes all information about the intersection point is already provided inside.
	// WARNING: Use with care. Malformed EmitterQueryRecords can result in undefined behavior. 
	//			Plus no visibility is considered.
	
	virtual float pdf(const EmitterQueryRecord &lRec) const {
		if (!m_mesh)
			throw NoriException("There is no shape attached to this Area light!");

    	float cosTheta = lRec.n.dot(-lRec.wi); /* Compute the cosine between the light normal and the direction towards the shaded point */

    	if (cosTheta <= 0.0f) /* Backfacing samples cannot contribute to illumination */
    	    return 0.0f;

    	float pdfArea = m_mesh->pdf(lRec.p); /* Surface-area density provided by Mesh::pdf() */

    	/* Convert the density from area measure to solid-angle measure:  pdf_omega = pdf_area * r² / cos(theta) */
    		return pdfArea * (lRec.dist * lRec.dist) /  cosTheta;
		}

		// Get the parent mesh
		void setParent(NoriObject *parent)
	{
		auto type = parent->getClassType();
		if (type == EMesh)
			m_mesh = static_cast<Mesh*>(parent);
	}

	// Set children
	void addChild(NoriObject* obj, const std::string& name = "none") {
		switch (obj->getClassType()) {
		case ETexture:
			if (name == "radiance")
			{
				delete m_radiance;
				m_radiance = static_cast<Texture*>(obj);
			}
			else
				throw NoriException("AreaEmitter::addChild(<%s>,%s) is not supported!",
					classTypeName(obj->getClassType()), name);
			break;

		default:
			throw NoriException("AreaEmitter::addChild(<%s>) is not supported!",
				classTypeName(obj->getClassType()));
		}
	}
protected:
	Texture* m_radiance;
	float m_scale;
};

NORI_REGISTER_CLASS(AreaEmitter, "area")
NORI_NAMESPACE_END
