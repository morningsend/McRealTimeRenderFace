//
// Created by Zaiyang Li on 11/04/2018.
//

#include "AOFragmentShader.hpp"
#include "../scene/TextureSampler2D.hpp"


namespace McRenderer {
    using namespace glm;
    void AOFragmentShader::run(const ShaderEnvironment &env,
                                const BufferSampler2D& positionSampler,
                                const AOShaderParams &params,
                                AOPassOutput &output) {
        vec3 randomVector = noise[rand() % 16];
        vec3 normal = params.normal;
        vec3 tangent = normalize(normal - randomVector);
        vec3 bitangent = cross(tangent, normal);
        mat3 tbn(tangent, bitangent, normal);
        float occlusion = 0.0f;
        
        for(const vec3& kernel : kernels) {
            vec3 orientedKernel = tbn * kernel;
            vec3 sample = params.position + orientedKernel * radius;
            vec4 position = env.projectionMatrix * vec4(sample, 1);
            position /= position.w;
            position = position * 0.5f + vec4(0.5f);
            vec2 uvCoord(position.x, position.y);
            float z = positionSampler.sample(uvCoord).z;
            float rangeCheck = smoothstep<float>(0, 1, radius / abs(params.position.z - z));

            occlusion += (z >= sample.z + bias ? 1 : 0) * rangeCheck;
        }
        output.occlusion = 1.0f - occlusion / kernels.size();
    }
}
