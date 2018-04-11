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
        float radius;
    };
    struct AOPassOutput {
        float occlusion;
    };
    class AOFragmentShader {
    public:
        void run(const ShaderEnvironment &env,
                 const std::vector<vec3> &kernels,
                 TextureSampler2D positionTexture,
                 const AOShaderParams &params, AOPassOutput &output);
    };
}


#endif //RENDERER_AOFRAGMENTSHADER_HPP
