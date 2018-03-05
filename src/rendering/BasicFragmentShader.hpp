//
// Created by Zaiyang Li on 05/03/2018.
//

#ifndef RENDERER_BASICFRAGMENTSHADER_HPP
#define RENDERER_BASICFRAGMENTSHADER_HPP
#include <glm/glm.hpp>
#include "FragmentShader.hpp"

namespace McRenderer {
    class BasicFragmentShader : public FragmentShader{
    public:
        virtual void run(const ShaderEnvironment& env,
                         const VertexShaderOutputParams& vertexOutput,
                         FragmentShaderOutput& output) override {
            output.colour = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
        } ;

        ~BasicFragmentShader() = default;
    };
}

#endif //RENDERER_BASICFRAGMENTSHADER_HPP
