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
    vec4 basecolour = vec4(material.basecolourSampler.sample(vertexOutput.textCoord), 1);
    vec3 normal = material.normalSampler.sample(vertexOutput.textCoord) * 2.0f - vec3(1);

    //float metalness = material.metalnessSampler.sample(vertexOutput.textCoord);
    float roughness = max(material.roughnessSampler.sample(vertexOutput.textCoord), 0.001f);

    //roughness = (1 - roughness) *(1 -roughness);
    vec4 diffuse = basecolour;
    vec4 specular = vec4(0.4f, 0.4f, 0.4f, 1.0f);
    output.specular = specular;
    output.normal = vec3(env.viewingMatrix * vec4((tangentToWorld * normal), 0));
    output.diffuse = basecolour;
    output.position = vertexOutput.viewPosition;
    output.roughness = roughness;
}
