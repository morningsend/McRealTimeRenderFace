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
