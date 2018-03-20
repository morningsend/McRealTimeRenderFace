//
// Created by Zaiyang Li on 05/03/2018.
//

#ifndef RENDERER_BASICFRAGMENTSHADER_HPP
#define RENDERER_BASICFRAGMENTSHADER_HPP
#include <glm/glm.hpp>
#include "FragmentShader.hpp"

#define F_PI 3.1415926f
namespace McRenderer {
    class BasicFragmentShader : public FragmentShader{
    public:
        inline float max(float a, float b) {
            return a > b ? a : b;
        }
        inline float min(float a, float b) {
            return a < b ? a : b;
        }
        virtual void run(const ShaderEnvironment& env,
                         const VertexShaderOutputParams& vertexOutput,
                         FragmentShaderOutput& output) override {

            // diffuse shading:
            // colour = materialColour * dot(lightDir, normal) * lightIntensity / attenuationFactor;
            vec3 lightDirection = vec3(env.light1.position) - vec3(vertexOutput.viewPosition);
            float distanceLight = glm::length(lightDirection);
            lightDirection /= distanceLight;
            float cosTheta = max(glm::dot(lightDirection, vec3(vertexOutput.normal)), 0.01f);
            float attenuationFactor = 1.0f / (distanceLight * distanceLight * 2 * F_PI);
            output.colour = vertexOutput.colour * env.light1.colour * cosTheta * (attenuationFactor * env.light1.intensity) + env.ambient;
            output.depth = vertexOutput.position.z;
        };

        ~BasicFragmentShader() = default;
    };
}

#endif //RENDERER_BASICFRAGMENTSHADER_HPP
