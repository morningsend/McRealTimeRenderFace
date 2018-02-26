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
        vec4 vertices[3] { vec4(0), vec4(0), vec4(0) };
        vec4 normal {0,0,1,0};

        Triangle() {}
        Triangle(vec4 v0, vec4 v1, vec4 v2) : vertices{ v0, v1, v2 } {}
        Triangle(vec4 v0, vec4 v1, vec4 v2, vec4 normal) : vertices{ v0, v1, v2 }, normal{normal} {}
    };
    void computeTriangleNormal(Triangle& triangle);
    void clipTriangle3D(const Triangle& triangle, vector<Triangle>& result);
}


#endif //RENDERER_TRIANGLE_HPP
