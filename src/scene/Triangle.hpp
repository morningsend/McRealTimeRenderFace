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
    void computeTriangleNormal(Triangle& triangle);
    void clipTriangle3D(const Triangle& triangle, vector<Triangle>& result);
}


#endif //RENDERER_TRIANGLE_HPP
