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
                         const Material& material,
                         FragmentShaderOutput& output) override {
#ifdef GRAPHICS_DEBUG
            output.colour = vec4(material
                    .specularColourSampler
                    .sample(vec2(vertexOutput.textCoord.x, vertexOutput.textCoord.y)) , 1);
            cout << output.colour.x <<' ' << output.colour.y << endl;
            return;
#else
            // diffuse shading:
            // colour = materialColour * dot(lightDir, normal) * lightIntensity / attenuationFactor;
            vec3 lightDirection = vec3(env.light1.position) - vec3(vertexOutput.viewPosition);
            float distanceLight = glm::length(lightDirection);
            lightDirection /= distanceLight;
            float cosTheta = max(glm::dot(lightDirection, vec3(vertexOutput.normal)), 0.01f);
            float attenuationFactor = 1.0f / (distanceLight * distanceLight * 2 * F_PI);
            vec4 ambient = env.ambient * vertexOutput.colour;
            vec4 diffuse = (vec4(1) - env.ambient) * vertexOutput.colour * env.light1.colour * cosTheta * (attenuationFactor * env.light1.intensity);
            output.colour = ambient + diffuse;
            output.depth = vertexOutput.position.z;
#endif
        };

        ~BasicFragmentShader() = default;
    };
}

#endif //RENDERER_BASICFRAGMENTSHADER_HPP
