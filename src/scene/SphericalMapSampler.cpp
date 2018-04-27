//
// Created by Zaiyang Li on 03/04/2018.
//

#include "SphericalMapSampler.hpp"
#include <cmath>

namespace McRenderer {
    const float INVERSE2PI =0.1591549f;
    const float INVERSEPI = 0.3183099f;
    const float PI_2 = 1.5707963f;
    inline vec3 SphericalMapSampler::sample(vec3 normal) const {
        vec2 sphericalCoord = cartesianToSphericalPolar(normal);
        // map spherical coordinate 2pi x pi to unit square uv space [1]
        sphericalCoord.x *= INVERSE2PI;
        sphericalCoord.y *= (sphericalCoord.y + PI_2)*INVERSEPI;
        return texture->sample(sphericalCoord);
    }

    inline vec2 SphericalMapSampler::cartesianToSphericalPolar(vec3 vector) const{
        float r = sqrt(dot(vector, vector));
        float theta = acos(vector.z / r);
        float phi = atan2(vector.y, vector.x);
        return glm::vec2(theta, phi);
    }
}