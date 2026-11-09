/*
    This file is part of Nori, a simple educational ray tracer

    Copyright (c) 2015 by Wenzel Jakob

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

#include <nori/warp.h>
#include <nori/vector.h>
#include <nori/frame.h>

NORI_NAMESPACE_BEGIN

Point2f Warp::squareToUniformSquare(const Point2f &sample) {
    return sample;
}

float Warp::squareToUniformSquarePdf(const Point2f &sample) {
    return ((sample.array() >= 0).all() && (sample.array() <= 1).all()) ? 1.0f : 0.0f;
}

Point2f Warp::squareToTent(const Point2f &sample) {
    throw NoriException("Warp::squareToTent() is not yet implemented!");
}

float Warp::squareToTentPdf(const Point2f &p) {
    throw NoriException("Warp::squareToTentPdf() is not yet implemented!");
}

Point2f Warp::squareToUniformDisk(const Point2f &sample) {
    float r = sqrt(sample.x());
    float theta = 2 * M_PI * sample.y();

    return Point2f(r * cos(theta), r * sin(theta));
}

float Warp::squareToUniformDiskPdf(const Point2f &p) {
    if(p.x() * p.x() + p.y() * p.y() <= 1.0f){
        return 1.0f / M_PI;
    }

    return 0.0f;
}

Point2f Warp::squareToUniformTriangle(const Point2f& sample) {
    float sqrtu = sqrt(sample.x());

    float u = 1.0f - sqrtu;
    float v = sample.y() * sqrtu;

    return Point2f(u, v);
}

float Warp::squareToUniformTrianglePdf(const Point2f& p) {
    if(p.x() >= 0.0f && p.y() >= 0.0f && p.x() + p.y() <= 1.0f){
        return 2.0f; // area = (1*1)/2 = 0.5 --> pdf = 1 / 0.5 = 2.0
    }

    return 0.0f;
}


Vector3f Warp::squareToUniformSphere(const Point2f &sample) {
    /*
    double phi = 2 * M_PI * sample.x();
    double theta = acos(1 - 2 * sample.y());

    double x = sin(theta) * cos(phi);
    double y = sin(theta) * sin(phi);
    double z = cos(theta);

    return Vector3f(x, y, z);
    */

    float z = 1.0f - 2.0f * sample.x();
    float r = sqrt(std::max(0.0f, 1.0f - z*z));
    float phi = 2 * M_PI * sample.y();

    return Vector3f(r * cos(phi), r * sin(phi), z);
}

float Warp::squareToUniformSpherePdf(const Vector3f &v) {
    return 1.0 / (4 * M_PI);
}

Vector3f Warp::squareToUniformHemisphere(const Point2f &sample) {
    /*
    double phi = 2 * M_PI * sample.y();
    double theta = acos(sample.x());

    double x = sin(theta) * cos(phi);
    double y = sin(theta) * sin(phi);
    double z = cos(theta);

    return Vector3f(x, y, z);
    */
    
    float z = sample.x();
    float r = sqrt(std::max(0.0f, 1.0f - z*z));
    float phi = 2 * M_PI * sample.y();
    
    return Vector3f(r * cos(phi), r * sin(phi), z);
}

float Warp::squareToUniformHemispherePdf(const Vector3f &v) {
    if(v.z() < 0.0){
        return 0.0;
    }
    return 1 / (2 * M_PI);
}

Vector3f Warp::squareToCosineHemisphere(const Point2f &sample) {
    double phi = 2 * M_PI * sample.x();
    double theta = acos(sqrt(1 - sample.y()));

    double x = sin(theta) * cos(phi);
    double y = sin(theta) * sin(phi);
    double z = cos(theta);

    return Vector3f(x, y, z);
}

float Warp::squareToCosineHemispherePdf(const Vector3f &v) {
    if(v.z() < 0.0){
        return 0.0;
    }
    return v.z() / M_PI;
}

Vector3f Warp::squareToBeckmann(const Point2f &sample, float alpha) {
    float phi = 2 * M_PI * sample.x();
    float theta = atan(sqrt(-alpha * alpha * log(1 - sample.y())));

    float x = sin(theta) * cos(phi);
    float y = sin(theta) * sin(phi);
    float z = cos(theta);

    return Vector3f(x, y, z);
}

float Warp::squareToBeckmannPdf(const Vector3f &m, float alpha) {
    if(m.z() <= 0.0f){
        return 0.0f;
    }

    float cosTheta = m.z();
    float tanTheta = sqrt(1 - cosTheta * cosTheta) / cosTheta;

    float pdf = exp(-tanTheta * tanTheta / (alpha * alpha)) / (M_PI * alpha * alpha * cosTheta * cosTheta * cosTheta);

    return pdf;
}

NORI_NAMESPACE_END