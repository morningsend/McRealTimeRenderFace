//
// Created by Zaiyang Li on 05/03/2018.
//

#ifndef RENDERER_BASICVERTEXSHADER_HPP
#define RENDERER_BASICVERTEXSHADER_HPP


#include "VertexShader.hpp"

namespace McRenderer {
    class BasicVertexShader : public VertexShader {
    public:
        virtual void run(const ShaderEnvironment& env,
                         const VertexShaderInputParams& input,
                         VertexShaderOutputParams& output) override {
            output.position = env.projectionMatrix * env.viewingMatrix * input.position;
            output.normal = env.viewingMatrix * input.normal;
            output.normal.w = 0;
        };

        ~BasicVertexShader() = default;
    };
}

#endif //RENDERER_BASICVERTEXSHADER_HPP
