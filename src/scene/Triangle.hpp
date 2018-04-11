//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_TRIANGLE_HPP
#define RENDERER_TRIANGLE_HPP

#include "../common.h"
#include "Viewport.hpp"


namespace McRenderer {
    using namespace glm;
    using namespace std;
    struct Triangle {
        vec4 vertices[3] { vec4(0), vec4(0), vec4(0) };
        vec4 normal {0,0,1,0};
        vec4 colour {1.0f};
        vec2 uvCoords[3] = { vec2(0,0), vec2(1,0), vec2(1,1) };
        vec4 tangent;
        vec4 bitangent;

        int materialId{-1};

        Triangle() {}
        Triangle(vec4 v0, vec4 v1, vec4 v2) : vertices{ v0, v1, v2 } {}
        Triangle(vec4 v0, vec4 v1, vec4 v2, vec4 normal) : vertices{ v0, v1, v2 }, normal{normal} {}
        Triangle(vec4 v0, vec4 v1, vec4 v2, vec4 normal, vec4 colour)
                : vertices{ v0, v1, v2 }, normal{normal}, colour{colour} {}

        static inline void computeBarycentricCoord(vec4 v0,
                                                   vec4 v1,
                                                   vec4 v2,
                                                   vec4 point,
                                                   vec3& barycentric) {
            vec3 e0 = vec3(v1 - v0);
            vec3 e1 = vec3(v2 - v0);
            vec3 e2 = vec3(point - v0);

            float d[5] = {
                    glm::dot(e0, e0),
                    glm::dot(e0, e1),
                    glm::dot(e1,e1),
                    glm::dot(e2, e0),
                    glm::dot(e2, e1)
            };
            float denom = d[0] * d[2] - d[1] * d[1];
            if(denom < 0.0000001f) {
                return;
            }
            denom = 1 / denom;
            barycentric.y = (d[2] * d[3] - d[1] * d[4]) * denom;
            barycentric.z = (d[0] * d[4] - d[1] * d[3]) * denom;
            barycentric.x = 1 - barycentric.y - barycentric.z;
        }
    };
    void computeNormal(Triangle &triangle);
    void computeTangentBasis(Triangle &triangle);


}


#endif //RENDERER_TRIANGLE_HPP
