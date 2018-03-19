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
        result.normal = v1.normal * t + v2.normal * oneMinusT;
        result.colour = v1.colour * t + v2.colour * oneMinusT;
        result.textCoord = v1.textCoord * t + v2.textCoord * oneMinusT;
    }

    void
    McRenderer::Interpolate(const VertexShaderOutputParams &v1,
                            const VertexShaderOutputParams &v2,
                            float t1, float t2,
                            VertexShaderOutputParams &result) {
        result.position = v1.position * t1 + v2.position * t2;
        result.normal = v1.normal * t1 + v2.normal * t2;
        result.colour = v1.colour * t1 + v2.colour * t2;
        result.textCoord = v1.textCoord * t1 + v2.textCoord * t2;
    }
}