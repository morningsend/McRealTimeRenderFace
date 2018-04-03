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
            output.position = env.viewProjectionMatrix * input.position;
            output.worldPosition = input.position;
            output.normal = normalize(input.normal);
            output.tangent = normalize(input.tangent);
            output.bitangent = vec4(normalize(cross(vec3(input.normal), vec3(input.tangent))), 0);
            output.colour = input.colour;
            output.textCoord = input.textCoord;
            //output.colour = (output.viewPosition * 0.5f) + vec4(0.5f);
        };

        ~BasicVertexShader() = default;
    };
}

#endif //RENDERER_BASICVERTEXSHADER_HPP
