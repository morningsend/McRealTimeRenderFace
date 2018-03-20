//
// Created by Zaiyang Li on 19/03/2018.
//

#include "VertexShader.hpp"

namespace McRenderer {
    void Interpolate(const VertexShaderOutputParams &v1,
                     const VertexShaderOutputParams &v2,
                     float t,
                     VertexShaderOutputParams &result) {
        float oneMinusT = 1 - t;
        result.position = v1.position * t + v2.position * oneMinusT;
        result.viewPosition = v1.viewPosition * t + v2.viewPosition * oneMinusT;
        result.normal = v1.normal * t + v2.normal * oneMinusT;
        result.colour = v1.colour * t + v2.colour * oneMinusT;
        result.textCoord = v1.textCoord * t + v2.textCoord * oneMinusT;
    }

    void Interpolate(const VertexShaderOutputParams &v1,
                            const VertexShaderOutputParams &v2,
                            float t1, float t2,
                            VertexShaderOutputParams &result) {
        result.position = v1.position * t1 + v2.position * t2;
        result.viewPosition = v1.viewPosition * t1 + v2.viewPosition * t2;
        result.normal = v1.normal * t1 + v2.normal * t2;
        result.colour = v1.colour * t1 + v2.colour * t2;
        result.textCoord = v1.textCoord * t1 + v2.textCoord * t2;
    }

    void McRenderer::Interpolate(const VertexShaderOutputParams *triangleAttributes, vec3 barycentric,
                                 VertexShaderOutputParams &result) {

        result.position = triangleAttributes[0].position * barycentric[0];
        result.viewPosition = triangleAttributes[0].viewPosition * barycentric[0];
        result.normal = triangleAttributes[0].normal * barycentric[0];
        result.colour = triangleAttributes[0].colour * barycentric[0];
        result.textCoord = triangleAttributes[0].textCoord * barycentric[0];
        for(int j = 1; j < 3; j++) {
            result.position += triangleAttributes[j].position * barycentric[j];
            result.viewPosition += triangleAttributes[j].viewPosition * barycentric[j];
            result.normal += triangleAttributes[j].normal * barycentric[j];
            result.colour += triangleAttributes[j].colour * barycentric[j];
            result.textCoord += triangleAttributes[j].textCoord * barycentric[j];
        }

    }
}