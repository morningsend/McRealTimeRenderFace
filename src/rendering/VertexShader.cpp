//
// Created by Zaiyang Li on 19/03/2018.
//

#include <iostream>
#include "VertexShader.hpp"

namespace McRenderer {
    void interpolate(const VertexShaderOutputParams &v1,
                     const VertexShaderOutputParams &v2,
                     float t,
                     VertexShaderOutputParams &result) {
        float oneMinusT = 1 - t;
        result.position = v1.position * oneMinusT + v2.position * t;
        result.worldPosition = v1.worldPosition * oneMinusT + v2.worldPosition * t;
        result.viewPosition = v1.viewPosition * oneMinusT + v2.viewPosition * t;
        result.normal = v1.normal * oneMinusT + v2.normal * t;
        result.tangent = v1.tangent * oneMinusT + v2.tangent * t;
        result.bitangent = v1.bitangent * oneMinusT + v2.bitangent * t;
        result.colour = v1.colour * oneMinusT + v2.colour * t;
        result.textCoord = v1.textCoord * oneMinusT + v2.textCoord * t;
    }

    void Interpolate(const VertexShaderOutputParams &v1,
                            const VertexShaderOutputParams &v2,
                            float t1, float t2,
                            VertexShaderOutputParams &result) {
        result.position = v1.position * t1 + v2.position * t2;
        result.worldPosition = v1.worldPosition * t1 + v2.worldPosition * t2;
        result.viewPosition = v1.viewPosition * t1 + v2.viewPosition * t2;
        result.normal = v1.normal * t1 + v2.normal * t2;
        result.tangent = v1.tangent * t1 + v2.tangent * t2;
        result.bitangent = v1.bitangent * t1 + v2.bitangent * t2;
        result.colour = v1.colour * t1 + v2.colour * t2;
        result.textCoord = v1.textCoord * t1 + v2.textCoord * t2;

    }

    void interpolateBarycentric(const VertexShaderOutputParams *triangleAttributes, vec3 barycentric,
                                            VertexShaderOutputParams &result) {

        result.position = triangleAttributes[0].position * barycentric[0];
        result.worldPosition = triangleAttributes[0].worldPosition * barycentric[0];
        result.viewPosition = triangleAttributes[0].viewPosition * barycentric[0];
        result.normal = triangleAttributes[0].normal * barycentric[0];
        result.tangent = triangleAttributes[0].tangent * barycentric[0];
        result.bitangent = triangleAttributes[0].bitangent * barycentric[0];
        result.colour = triangleAttributes[0].colour * barycentric[0];
        result.textCoord = triangleAttributes[0].textCoord * barycentric[0];
        for(int j = 1; j < 3; j++) {
            result.position += triangleAttributes[j].position * barycentric[j];
            result.worldPosition += triangleAttributes[j].worldPosition * barycentric[j];
            result.viewPosition += triangleAttributes[j].viewPosition * barycentric[j];
            result.normal += triangleAttributes[j].normal * barycentric[j];
            result.tangent += triangleAttributes[j].tangent * barycentric[j];
            result.bitangent += triangleAttributes[j].bitangent * barycentric[j];
            result.colour += triangleAttributes[j].colour * barycentric[j];
            result.textCoord += triangleAttributes[j].textCoord * barycentric[j];
        }

    }
    /**
     * Perspective correct interpolation
     * @param v1
     * @param v2
     * @param t
     * @param result
     */
    void perspectiveInterpolate(const VertexShaderOutputParams &v1, const VertexShaderOutputParams &v2, float t,
                                VertexShaderOutputParams &result) {
        // C = Z [C0/Z0*(1-t) + C1/Z1*t]
        // => C = Z/Z0*(1-t) * C0 + Z/Z1*t* C1
        // => C = A * C0 + B * C1 where A = Z/Z0*(1-t), B = Z/Z1*t

        result.position = v1.position * (1 - t) + v2.position * (t);

        float A = result.position.z / v1.position.z * (1-t);
        float B = result.position.z / v2.position.z * t;

        result.worldPosition = v1.worldPosition * A + v2.worldPosition * B;
        result.viewPosition = v1.viewPosition * A + v2.viewPosition * B;
        result.normal = v1.normal * A + v2.normal * B;
        result.tangent = v1.tangent * A + v2.tangent * B;
        result.bitangent = v1.bitangent * A + v2.bitangent * B;
        result.colour = v1.colour * A + v2.colour * B;
        result.textCoord = v1.textCoord * A + v2.textCoord * B;

    }

    // f = a1 * f1 / z1 + a2 * f2 / z2 + a3 * f3 / z3 / (a1 / z1 + a2 / z2 + a3 / z3)
    void perspectiveInterpolateBarycentric(const VertexShaderOutputParams *triangleAttributes,
                                           vec3 barycentricCoords,
                                           VertexShaderOutputParams &result) {
        vec3 perspetiveCorrectBarycentricCoords = vec3(
                barycentricCoords.x / triangleAttributes[0].position.z,
                barycentricCoords.y / triangleAttributes[1].position.z,
                barycentricCoords.z / triangleAttributes[2].position.z
        );
        //std::cout << "position before: " << triangleAttributes[0].position[0] << ' ' << triangleAttributes[1].position[1] << ' '<< triangleAttributes[0].position[2] << ' '<< triangleAttributes[0].position[3] << std::endl;
        perspetiveCorrectBarycentricCoords = normalize(perspetiveCorrectBarycentricCoords);
        //std::cout << "perspective correct barycentric: " << perspetiveCorrectBarycentricCoords[0] << ' ' << perspetiveCorrectBarycentricCoords[1] << ' '<< perspetiveCorrectBarycentricCoords[2] << std::endl;
        result.position = triangleAttributes[0].position * perspetiveCorrectBarycentricCoords[0];
        result.worldPosition = triangleAttributes[0].worldPosition * perspetiveCorrectBarycentricCoords[0];
        result.viewPosition = triangleAttributes[0].viewPosition * perspetiveCorrectBarycentricCoords[0];
        result.normal = triangleAttributes[0].normal * perspetiveCorrectBarycentricCoords[0];
        result.tangent = triangleAttributes[0].tangent * perspetiveCorrectBarycentricCoords[0];
        result.bitangent = triangleAttributes[0].bitangent * perspetiveCorrectBarycentricCoords[0];
        result.colour = triangleAttributes[0].colour * perspetiveCorrectBarycentricCoords[0];
        result.textCoord = triangleAttributes[0].textCoord * perspetiveCorrectBarycentricCoords[0];

        for(int j = 1; j < 3; j++) {
            result.position += triangleAttributes[j].position * perspetiveCorrectBarycentricCoords[j];
            result.worldPosition += triangleAttributes[j].worldPosition * perspetiveCorrectBarycentricCoords[j];
            result.viewPosition += triangleAttributes[j].viewPosition * perspetiveCorrectBarycentricCoords[j];
            result.normal += triangleAttributes[j].normal * perspetiveCorrectBarycentricCoords[j];
            result.tangent += triangleAttributes[j].tangent * perspetiveCorrectBarycentricCoords[j];
            result.bitangent += triangleAttributes[j].bitangent * perspetiveCorrectBarycentricCoords[j];
            result.colour += triangleAttributes[j].colour * perspetiveCorrectBarycentricCoords[j];
            result.textCoord += triangleAttributes[j].textCoord * perspetiveCorrectBarycentricCoords[j];
        }

        //std::cout << "position after: " << result.position[0] << ' ' << result.position[1] << ' '<< result.position[2] << ' ' << result.position[3] << std::endl;
        /*
        std::cout << "position before: " << result.position[0] << ' ' << result.position[1] << ' '<< result.position[2] << ' '<< result.position[3] << std::endl;
        result.position = result.position * sum;

        result.worldPosition = result.worldPosition * sum;
        result.viewPosition = result.viewPosition * sum;
        result.normal = result.normal * sum;
        result.tangent = result.tangent * sum;
        result.bitangent = result.bitangent * sum;
        result.colour = result.colour * sum;
        result.textCoord = result.textCoord * sum;*/
        if(result.position.x > result.position.w) {
            std::cout <<"x out of range" << std::endl;
        }
        if(result.position.y > result.position.w) {
            std::cout <<"y out of range" << std::endl;
        }
        if(result.position.z > result.position.w) {
            std::cout <<"z out of range" << std::endl;
        }
    }
}