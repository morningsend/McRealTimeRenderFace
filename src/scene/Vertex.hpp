//
// Created by Zaiyang Li on 30/01/2018.
//

#ifndef RENDERER_VERTEX_HPP
#define RENDERER_VERTEX_HPP

#include <glm/glm.hpp>
namespace McRenderer {
    using namespace glm;
    struct Vertex {
        vec4 position;
        vec4 normal;
        vec3 color;
        vec2 uvCoord;
    };
}


#endif //RENDERER_VERTEX_HPP
