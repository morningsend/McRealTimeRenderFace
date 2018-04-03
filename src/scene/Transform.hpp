//
// Created by Zaiyang Li on 25/01/2018.
//

#ifndef RENDERER_TRANSFORM_HPP
#define RENDERER_TRANSFORM_HPP

#include <glm/glm.hpp>

namespace McRenderer {
    using namespace glm;
    struct Transform {
        vec3 translation;
        vec3 rotation;
        vec3 scale;

        mat4x4 matrix();
    };
}

#endif //RENDERER_TRANSFORM_HPP
