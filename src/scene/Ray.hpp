//
// Created by Zaiyang Li on 25/01/2018.
//

#ifndef RENDERER_RAY_HPP
#define RENDERER_RAY_HPP

#include "../common.h"
#include "Triangle.hpp"

namespace McRenderer {
    using namespace glm;
    const float EPSILON = 0.00001f;
    struct Ray {
        vec3 origin;
        vec3 direction;
    };

    bool castRay(const Ray& ray, const Triangle& triangle, vec3& hitLocation);
}


#endif //RENDERER_RAY_HPP
