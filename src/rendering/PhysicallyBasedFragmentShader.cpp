//
// Created by Zaiyang Li on 02/04/2018.
//

#include "PhysicallyBasedFragmentShader.hpp"
#include "../shader/Microfacet.hpp"

namespace McRenderer {
    using namespace glm;
    using namespace std;

    void PhysicallyBasedFragmentShader::run(const McRenderer::ShaderEnvironment &env,
                                            const McRenderer::VertexShaderOutputParams &vertexOutput,
                                            const McRenderer::Material &material,
                                            McRenderer::FragmentShaderOutput &output) {
        mat3 tangentToWorld(vertexOutput.tangent, vertexOutput.bitangent, vertexOutput.normal);
        float remappedDepth = vertexOutput.position.z * 0.5f + 0.5f;
        vec4 basecolour = vec4(material.basecolourSampler.sample(vertexOutput.textCoord), 1);
        vec3 normal = material.normalSampler.sample(vertexOutput.textCoord) * 2.0f - vec3(1);


        float metalness = material.metalnessSampler.sample(vertexOutput.textCoord);
        float roughness = max(material.roughnessSampler.sample(vertexOutput.textCoord), 0.001f);

        vec4 diffuse = basecolour * (1 - metalness);
        vec4 specular = basecolour * metalness;

        // cook-torrance specular BRDF
        // Fr(l, v, n) = F G D / 4 * (n.l)(n.v)
        // diffuse: Lambert
        // Fr(l, v, n) = n * l

        vec3 lightDirection = vec3(env.light1.position - vertexOutput.worldPosition);
        float lightDistance = length(lightDirection);
        vec3 viewDirection = normalize(env.cameraPosition - vertexOutput.worldPosition);
        lightDirection /= lightDistance;
        lightDistance += 1;
        normal = normalize(tangentToWorld * normal);
        vec3 halfVector = normalize(normal + viewDirection);
        float attenuationFactor = max(0.01, 1 / (lightDistance * lightDistance * 2 * F_PI));
        float nDotL = dot(normal, lightDirection);
        float nDotV = dot(normal, viewDirection);
        float lDotH = dot(halfVector, lightDirection);
        float nDotH = dot(normal, halfVector);

        // evaluate specular BRDF;
        float specularLight =
                ggxDistribution(nDotH, roughness) *
                schlickGGXGeometricShadowMaskingFunc(nDotL, nDotV, roughness) *
                (shlickFresnel(lDotH, 0.04))
                / (4 * nDotL * nDotV);

        specular *= vec4(1) * env.light1.colour * specularLight * env.light1.intensity * attenuationFactor;
        // evaluate diffuse BRDF;
        diffuse = env.light1.colour * diffuse * (env.light1.intensity * nDotL * attenuationFactor);

        output.depth = vertexOutput.position.z;
        switch (env.shaderPassDebugging) {
            case Diffuse:
                output.colour = diffuse;
                break;
            case Specular:
                output.colour = vec4(0.8f) * specularLight * env.light1.intensity * attenuationFactor;
                break;
            case Normal:
                output.colour = vec4(
                        tangentToWorld * material.normalSampler.sample(vertexOutput.textCoord) * 0.5f + vec3(0.5f), 1);
                break;
            case VertexNormal:
                output.colour = vertexOutput.normal * 0.5f + vec4(0.5f);
                break;
            case Tangent:
                output.colour = vertexOutput.tangent * 0.5f + vec4(0.5f);
                break;
            case AmbientOcclusion:
                output.colour = vec4(1);
                break;
            case Depth:
                output.colour = vec4(vec3(1) * remappedDepth, 1);
                break;
            case All:
                output.colour = specular + diffuse;



        }
        output.depth = vertexOutput.position.z;
    }

}