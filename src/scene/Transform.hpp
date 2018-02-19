//
// Created by Zaiyang Li on 25/01/2018.
//

#ifndef RENDERER_TRANSFORM_HPP
#define RENDERER_TRANSFORM_HPP

#include <glm/vec4.hpp>

namespace McRenderer {
    using namespace glm;
    struct Transform {
        vec4 translation;
        vec4 rotation;
        vec4 scale;
    };
}


#endif //RENDERER_TRANSFORM_HPP
