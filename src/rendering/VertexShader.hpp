//
// Created by Zaiyang Li on 26/02/2018.
//

#ifndef RENDERER_VERTEXSHADER_HPP
#define RENDERER_VERTEXSHADER_HPP
#include <glm/glm.hpp>
#include "ShaderEnvironment.hpp"

namespace McRenderer {
    using namespace glm;
    struct VertexShaderInputParams {
        vec4 position;
        vec4 normal;
        vec4 tangent;
        vec4 bitangent;
        vec4 colour;
        vec2 textCoord;
    };
    struct VertexShaderOutputParams {
        vec4 position;
        vec4 worldPosition;
        vec4 normal;
        vec4 tangent;
        vec4 bitangent;
        vec4 colour;
        vec2 textCoord;
    };

    /**
     * result = v1 * (1 - t) + v2 * (t)
     * @param v1
     * @param v2
     * @param t
     * @param result
     */
    void interpolate(const VertexShaderOutputParams &v1,
                     const VertexShaderOutputParams &v2,
                     float t,
                     VertexShaderOutputParams &result);

    /**
     * result = v1 * t1 + v2 * t2
     * @param v1
     * @param v2
     * @param t1
     * @param t2
     * @param result
     */
    void Interpolate(const VertexShaderOutputParams& v1,
                     const VertexShaderOutputParams& v2,
                     float t1, float t2,
                     VertexShaderOutputParams& result);

    void interpolateBarycentric(const VertexShaderOutputParams *triangle,
                                vec3 barycentricCoords,
                                VertexShaderOutputParams &result);

    /**
     * Perspective correct interpolation:
     * C = Z [C0/Z0*(1-t) + C1/Z1*t]
     * @param v1
     * @param v2
     * @param t
     * @param result
     */
    void perspectiveInterpolate(const VertexShaderOutputParams& v1,
                     const VertexShaderOutputParams& v2,
                     float t,
                     VertexShaderOutputParams& result);
    /**
     * Perspective correct barycentric interpolation of a point on triangle.
     * Barycentric coordinates a1, a2, a3 and attribute f1, f2, f3
     * the non-perspective interpolation is simply f = f1*a1 + f2 * a2 + f3 * a3
     * To avoid perspective distortion we take into account the depth value.
     * f = a1 * f1 / z1 + a2 * f2 / z2 + a3 * f3 / z3 / (a1 / z1 + a2 / z2 + a3 / z3)
     * @param triangle
     * @param barycentricCoords
     * @param result
     */
    void perspectiveInterpolateBarycentric(const VertexShaderOutputParams *triangle,
                     vec3 barycentricCoords,
                     VertexShaderOutputParams &result);

    /**
     * Abstract class of a vertex shader.
     * Class to provide concrete vertex shader implementation
     * should override the run method.
     */
    class VertexShader {
    public:
        virtual void run(const ShaderEnvironment& env,
                         const VertexShaderInputParams& input,
                         VertexShaderOutputParams& output) {};
        virtual ~VertexShader() = default;
    };
}
#endif //RENDERER_VERTEXSHADER_HPP
