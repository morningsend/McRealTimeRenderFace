//
// Created by Zaiyang Li on 11/04/2018.
//

#ifndef RENDERER_AOFRAGMENTSHADER_HPP
#define RENDERER_AOFRAGMENTSHADER_HPP
#include "../common.h"
#include "ShaderEnvironment.hpp"
#include "../scene/TextureSampler2D.hpp"

namespace McRenderer {
    struct AOShaderParams {
        glm::vec3 position;
        glm::vec3 normal;
    };
    struct AOPassOutput {
        float occlusion;
    };
    class AOFragmentShader {
    private:
        float radius;
        float bias;
        std::vector<glm::vec3> kernels;
        std::vector<glm::vec3> noise;
        int kernelSize{16};

    public:
        void generateKernelAndNoise() {
            const int size = 32;
            kernels.reserve(size);
            std::uniform_real_distribution<float> dist(0, 1);
            std::default_random_engine engine{};
            float scale;
            for(int i = 0; i < size; i++) {
                // genereate points on a hemisphere.
                vec3 kernel(
                        dist(engine) * 2 - 1, dist(engine) * 2 - 1, dist(engine)
                );
                kernel = normalize(kernel);
                //scale the kernel to be inside the hemisphere.
                kernel *= dist(engine);
                scale = (float) i / size;
                kernel *= scale * scale + 0.1f * (1 - scale * scale);
                kernels.push_back(kernel);
            }

            noise.reserve(16);
            for(int i = 0; i < 16; i++) {
                vec3 rot(dist(engine) * 2 -1, dist(engine) * 2 - 1, 0);
                noise.push_back(rot);
            }
        }
        AOFragmentShader(float radius, float bias, int kernelSize) : radius{radius}, bias{bias}, kernelSize{kernelSize} {}
        void run(const ShaderEnvironment &env,
                 const BufferSampler2D& positionTexture,
                 const AOShaderParams &params,
                 AOPassOutput &output);
    };
}


#endif //RENDERER_AOFRAGMENTSHADER_HPP
