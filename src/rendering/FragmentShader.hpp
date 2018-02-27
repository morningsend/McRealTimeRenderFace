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

    /**
     * Abastract class where a concrete shader class should extend.
     * Must override the run method.
     */
    class FragmentShader {
    public:
        virtual void run(const ShaderEnvironment& env,
                         const VertexShaderOutputParams& vertexOutput,
                         FragmentShaderOutput& output) {};
        virtual ~FragmentShader() = default;
    };
}

#endif //RENDERER_FRAGMENTSHADER_HPP
