//
// Created by Zaiyang Li on 26/02/2018.
//

#ifndef RENDERER_FRAGMENTSHADER_HPP
#define RENDERER_FRAGMENTSHADER_HPP
#include <glm/glm.hpp>
#include "VertexShader.hpp"
#include "../scene/MaterialSpec.hpp"
#define F_PI 3.1415926f

namespace McRenderer {

    struct FragmentShaderOutput {
        glm::vec4 colour;
        glm::vec4 diffuse;
        glm::vec4 specular;
        glm::vec3 normal;
        float depth;
        glm::vec4 position;
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

        inline float max(float a, float b) {
            return a > b ? a : b;
        }
        inline float min(float a, float b) {
            return a < b ? a : b;
        }
    };
}

#endif //RENDERER_FRAGMENTSHADER_HPP
