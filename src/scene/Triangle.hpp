//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_TRIANGLE_HPP
#define RENDERER_TRIANGLE_HPP

#include <glm/glm.hpp>
namespace McRenderer {
    using namespace glm;
    struct Triangle {
        vec3 vertices[3];
        vec3 normal;

    };
}


#endif //RENDERER_TRIANGLE_HPP
