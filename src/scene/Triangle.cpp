//
// Created by Zaiyang Li on 31/01/2018.
//

#include "Triangle.hpp"
#include "Line.hpp"
namespace McRenderer {

    void computeTriangleNormal(Triangle& triangle) {
        vec4 e1 = triangle.vertices[1] - triangle.vertices[0];
        vec4 e2 = triangle.vertices[2] - triangle.vertices[0];

        triangle.normal = glm::normalize(vec4(glm::cross(vec3(e1), vec3(e2)), 0));
    }
    void clipTriangle3D(const Triangle& triangle, vector<Triangle>& result) {

    }

}
