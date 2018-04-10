//
// Created by Zaiyang Li on 02/04/2018.
//

#ifndef RENDERER_PHYSICALLYBASEDSHADER_HPP
#define RENDERER_PHYSICALLYBASEDSHADER_HPP
#include "FragmentShader.hpp"

namespace McRenderer {

    struct LightingPassFragmentShaderParams {
        vec3 position;
        vec3 viewDirection;
        vec3 normal;
        vec3 diffuseColour;
        vec3 specularColour;

        vec3 lightPosition;
        float lightIntensity;
        vec3 lightColour;
    };

    struct LightingPassFragmentShaderOutput {
        glm::vec4 lightContribution;
    };
    class LightingPassFragmentShader {
    public:
        ~LightingPassFragmentShader() = default;
        void run(const ShaderEnvironment& env,
                 const LightingPassFragmentShaderParams& lightingParams,
                 LightingPassFragmentShaderOutput& output);
    };
}


#endif //RENDERER_PHYSICALLYBASEDSHADER_HPP
