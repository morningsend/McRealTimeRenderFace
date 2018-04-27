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
        const vec3 randomVector = noise[rand() % 16];
        const vec3 normal = params.normal;
        const vec3 tangent = normalize(normal - randomVector);
        const vec3 bitangent = cross(tangent, normal);
        const mat3 tbn(tangent, bitangent, normal);
        float occlusion = 0.0f;
        const int size = kernels.size();

        //#pragma omp parallel for shared(kernels), reduction(+: occlusion)
        for(int i = 0; i < size; i++) {
            vec3 orientedKernel = tbn * kernels[i];
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
