//
// Created by Zaiyang Li on 26/02/2018.
//

#ifndef RENDERER_FRAGMENTSHADER_HPP
#define RENDERER_FRAGMENTSHADER_HPP
#include <glm/glm.hpp>
#include "VertexShader.hpp"
#include "../scene/MaterialSpec.hpp"
namespace McRenderer {

    struct FragmentShaderOutput {
        glm::vec4 colour;
        float depth;
    };

    /**
     * Abastract class where a concrete shader class should extend.
     * Must override the run method.
     */
    class FragmentShader {
    public:
        virtual void run(const ShaderEnvironment& env,
                         const VertexShaderOutputParams& vertexOutput,
                         const Material& material,
                         FragmentShaderOutput& output) {};
        virtual ~FragmentShader() = default;
    };
}

#endif //RENDERER_FRAGMENTSHADER_HPP
