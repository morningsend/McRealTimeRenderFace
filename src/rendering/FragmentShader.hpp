//
// Created by Zaiyang Li on 26/02/2018.
//

#ifndef RENDERER_FRAGMENTSHADER_HPP
#define RENDERER_FRAGMENTSHADER_HPP

#include "VertexShader.hpp"
#include <glm/glm.hpp>
namespace McRenderer {

    struct FragmentShaderOutput {
        glm::vec3 colour;
    };

    class FragmentShader {
    public:
        virtual void run(ShaderEnvironment& env, VertexShaderOutputParams& vertexOutput, FragmentShaderOutput& output) = 0;
        virtual ~FragmentShader() = default;
    };
}

#endif //RENDERER_FRAGMENTSHADER_HPP
