//
// Created by Zaiyang Li on 31/01/2018.
//

#include "Triangle.hpp"

namespace McRenderer {
    glm::vec4 computeTriangleNormal(glm::vec4 *vertices) {
        vec4 e1 = vertices[1] - vertices[0];
        vec4 e2 = vertices[2] - vertices[0];

        vec3 normal = glm::cross(vec3(e1), vec3(e2));
        return vec4(normal, 0.0f);
    }


}
