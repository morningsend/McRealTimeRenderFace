//
// Created by Zaiyang Li on 26/02/2018.
//

#ifndef RENDERER_SHADERENVIRONMENT_HPP
#define RENDERER_SHADERENVIRONMENT_HPP

#include <glm/glm.hpp>
#include "../scene/Light.hpp"

namespace McRenderer {
    enum ShaderPass {
        All,
        Diffuse,
        Specular,
        Normal,
        VertexNormal,
        Tangent,
        Depth,
        AmbientOcclusion,
    };

    struct ShaderEnvironment {
        glm::mat4 viewingMatrix;
        glm::mat4 projectionMatrix;
        glm::mat4 viewProjectionMatrix;
        glm::mat4 normalMatrix;
        Light light1;
        Light light2;
        glm::vec4 cameraPosition;
        ShaderPass shaderPassDebugging;
    };
}

#endif //RENDERER_SHADERENVIRONMENT_HPP
