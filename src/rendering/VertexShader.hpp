//
// Created by Zaiyang Li on 26/02/2018.
//

#ifndef RENDERER_VERTEXSHADER_HPP
#define RENDERER_VERTEXSHADER_HPP

#include "ShaderEnvironment.hpp"

namespace McRenderer {
    struct VertexShaderInputParams {

    };
    struct VertexShaderOutputParams {

    };

    class VertexShader {
    public:
        virtual void run(ShaderEnvironment& env,
                         VertexShaderInputParams& input,
                         VertexShaderOutputParams& output) {};
        virtual ~VertexShader() = default;
    };
}
#endif //RENDERER_VERTEXSHADER_HPP
