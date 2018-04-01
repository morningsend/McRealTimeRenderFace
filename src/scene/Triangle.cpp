//
// Created by Zaiyang Li on 31/01/2018.
//

#include "Triangle.hpp"
#include "Line.hpp"
namespace McRenderer {

    void computeNormal(Triangle &triangle) {
        vec4 e1 = triangle.vertices[1] - triangle.vertices[0];
        vec4 e2 = triangle.vertices[2] - triangle.vertices[0];

        triangle.normal = glm::normalize(vec4(glm::cross(vec3(e1), vec3(e2)), 0));
    }

    void computeTangentBasis(Triangle &triangle) {
        vec4 e1 = triangle.vertices[1] - triangle.vertices[0];
        vec4 e2 = triangle.vertices[2] - triangle.vertices[0];

        vec2 uvDelta1 = triangle.uvCoords[1] - triangle.uvCoords[0];
        vec2 uvDelta2 = triangle.uvCoords[2] - triangle.uvCoords[0];

        float inverseDet = 1.0f / (uvDelta1.x * uvDelta2.y - uvDelta2.x * uvDelta1.y);

        vec4 tangent = (e1 * uvDelta2.y - e2 * uvDelta1.y) * inverseDet;
        vec4 bitangent = (e2 * uvDelta1.x - e1 * uvDelta2.x) * inverseDet;

        triangle.bitangent = glm::normalize(bitangent);
        triangle.tangent = glm::normalize(tangent);
    }
}
