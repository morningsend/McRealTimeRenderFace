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
                         const Material& material,
                         FragmentShaderOutput& output) override {
            mat3 tangentToWorld(vertexOutput.tangent, vertexOutput.bitangent, vertexOutput.normal);
#ifdef GRAPHICS_DEBUG
            switch(env.shaderPassDebugging) {
                case Diffuse:
                    output.diffuse = vec4(material.basecolourSampler.sample(vec2(vertexOutput.textCoord.x, vertexOutput.textCoord.y)) , 1);
                    break;
                case Specular:
                    output.diffuse = vec4(1);
                    break;
                case Normal:
                    output.diffuse = vec4(material.normalSampler.sample(vertexOutput.textCoord), 1);
                    break;
                case VertexNormal:
                    output.diffuse = vertexOutput.normal * 0.5f + vec4(0.5f);
                    break;
                case Tangent:
                    output.diffuse = vertexOutput.tangent * 0.5f + vec4(0.5f);
                    break;
                    break;
                case AmbientOcclusion:
                    output.diffuse = vec4(1);
                    break;
                case All:
#endif
                    vec4 diffuseTextureColour = vec4(material.basecolourSampler.sample(vec2(vertexOutput.textCoord.x, vertexOutput.textCoord.y)) , 1);
                    vec3 normal = material.normalSampler.sample(vertexOutput.textCoord) * 2.0f - vec3(1);
                    normal = normalize(tangentToWorld * normal);
                    vec3 lightDirection = vec3(env.light1.position) - vec3(vertexOutput.worldPosition);
                    float distanceLight = glm::length(lightDirection);

                    lightDirection /= distanceLight;
                    float cosTheta = max(glm::dot(lightDirection, normal), 0.0f);
                    float attenuationFactor = 1.0f / (distanceLight * distanceLight * 2 * F_PI);
                    vec4 diffuse = diffuseTextureColour * env.light1.colour * cosTheta * (attenuationFactor * env.light1.intensity);
                    output.diffuse = diffuse;
#ifdef GRAPHICS_DEBUG
                    break;
            }
#endif
        };

        ~BasicFragmentShader() = default;
    };
}

#endif //RENDERER_BASICFRAGMENTSHADER_HPP
