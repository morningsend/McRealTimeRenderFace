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
        vec4 colour;
        vec4 textCoord;
    };
    struct VertexShaderOutputParams {
        vec4 position;
        vec4 normal;
        vec4 colour;
        vec4 textCoord;
    };

    /**
     * result = v1 * t + v2 * (1-t)
     * @param v1
     * @param v2
     * @param t
     * @param result
     */
    void Interpolate(const VertexShaderOutputParams& v1,
                     const VertexShaderOutputParams& v2,
                     float t,
                     VertexShaderOutputParams& result);

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
