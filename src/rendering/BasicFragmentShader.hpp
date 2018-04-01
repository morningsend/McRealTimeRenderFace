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

            output.colour = vertexOutput.tangent * 0.5f + vec4(0.5f);
#else
            mat3 tangentToWorld(vertexOutput.tangent, vertexOutput.bitangent, vertexOutput.normal);

            // diffuse shading:
            // colour = materialColour * dot(lightDir, normal) * lightIntensity / attenuationFactor;
            vec4 diffuseTextureColour = vec4(
                    material.diffuseColourSampler.sample(vec2(vertexOutput.textCoord.x, vertexOutput.textCoord.y)) , 1);
            vec3 normal = normalize(material.normalSampler.sample(vertexOutput.textCoord) * 2.0f - vec3(1));
            normal = tangentToWorld * normal;
            vec3 lightDirection = vec3(env.light1.position) - vec3(vertexOutput.viewPosition);
            float distanceLight = glm::length(lightDirection);

            lightDirection /= distanceLight;
            float cosTheta = max(glm::dot(lightDirection, normal), 0.0f);
            float attenuationFactor = 1.0f / (distanceLight * distanceLight * 2 * F_PI);
            vec4 diffuse = diffuseTextureColour * env.light1.colour * cosTheta * (attenuationFactor * env.light1.intensity);
            output.colour = diffuse;
            output.depth = vertexOutput.position.z;
#endif
        };

        ~BasicFragmentShader() = default;
    };
}

#endif //RENDERER_BASICFRAGMENTSHADER_HPP
