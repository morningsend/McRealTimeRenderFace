//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_TRIANGLE_HPP
#define RENDERER_TRIANGLE_HPP
#include <vector>
#include <glm/glm.hpp>
#include "Viewport.hpp"

namespace McRenderer {
    using namespace glm;
    using namespace std;
    struct Triangle {
        vec4 vertices[3];
        vec4 normal;

    };
    vec4 computeTriangleNormal(vec4 vertices[3]);
    void clipTriangle2D(const Triangle& triangle, const Viewport& viewport, vector<Triangle>& result);
}


#endif //RENDERER_TRIANGLE_HPP
