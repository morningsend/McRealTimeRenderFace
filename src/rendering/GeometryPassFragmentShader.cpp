//
// Created by Zaiyang Li on 09/04/2018.
//

#include "GeometryPassFragmentShader.hpp"
#include "../shader/Microfacet.hpp"

using namespace glm;
using namespace std;

void McRenderer::GeometryPassFragmentShader::run(const McRenderer::ShaderEnvironment &env,
                                                 const McRenderer::VertexShaderOutputParams &vertexOutput,
                                                 const McRenderer::Material &material,
                                                 McRenderer::FragmentShaderOutput &output) {
    mat3 tangentToWorld(vertexOutput.tangent, vertexOutput.bitangent, vertexOutput.normal);
    float remappedDepth = vertexOutput.position.z * 0.5f + 0.5f;
    vec4 basecolour = vec4(material.basecolourSampler.sample(vertexOutput.textCoord), 1);
    vec3 normal = material.normalSampler.sample(vertexOutput.textCoord) * 2.0f - vec3(1);

    float metalness = material.metalnessSampler.sample(vertexOutput.textCoord);
    float roughness = max(material.roughnessSampler.sample(vertexOutput.textCoord), 0.001f);

    //roughness = (1 - roughness) *(1 -roughness);
    vec4 diffuse = basecolour;
    vec4 specular = vec4(0.4f, 0.4f, 0.4f, 1.0f);
    output.specular = specular;
    // cook-torrance specular BRDF
    // Fr(l, v, n) = F G D / 4 * (n.l)(n.v)
    // diffuse: Lambert
    // Fr(l, v, n) = n * l

    vec3 lightDirection = vec3(env.light1.position - vertexOutput.viewPosition);
    float lightDistance = length(lightDirection);
    vec3 viewDirection = normalize(- vertexOutput.viewPosition);
    lightDirection /= lightDistance;
    lightDistance += 1;
    normal = vec3(env.viewingMatrix * vec4(normalize(tangentToWorld * normal), 0.0f));
    vec3 halfVector = normalize(normal + viewDirection);
    float attenuationFactor = max(0.01, 1 / (lightDistance * lightDistance * 2 * F_PI));
    float nDotL = max(dot(normal, lightDirection), 0);
    float nDotV = max(dot(normal, viewDirection), 0);
    float lDotH = max(dot(halfVector, lightDirection), 0);
    float nDotH = max(dot(normal, halfVector), 0);

    float fresnel = (shlickFresnel(lDotH, 0.04f));
    // evaluate specular BRDF;
    float specularLight =
            ggxDistribution(nDotH, roughness) *
            schlickGGXGeometricShadowMaskingFunc(nDotL, nDotV, roughness) * fresnel
            / max(0.001, (4 * nDotL * nDotV));

    specular *= vec4(1) * env.light1.colour * specularLight * env.light1.intensity * attenuationFactor * nDotL;
    // evaluate diffuse BRDF;
    diffuse = env.light1.colour * diffuse * (env.light1.intensity * nDotL * attenuationFactor) * (1- fresnel);

    output.depth = vertexOutput.position.z;
    switch (env.shaderPassDebugging) {
        case Diffuse:
            output.colour = diffuse;
            break;
        case Specular:
            output.colour = specular;
            break;
        case Normal:
            output.colour = vec4(normal * 0.5f + vec3(0.5f), 1);
            break;
        case VertexNormal:
            output.colour = vertexOutput.normal;
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
    output.normal = normal;
    output.diffuse = basecolour;
    output.position = vertexOutput.viewPosition;
}
