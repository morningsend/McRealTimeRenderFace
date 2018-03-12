//
// Created by Zaiyang Li on 26/02/2018.
//

#ifndef RENDERER_SHADERENVIRONMENT_HPP
#define RENDERER_SHADERENVIRONMENT_HPP

#include <glm/glm.hpp>

namespace McRenderer {
    struct ShaderEnvironment {
        glm::mat4 viewingMatrix;
        glm::mat4 projectionMatrix;
        glm::mat4 viewProjectionMatrix;
        glm::mat4 normalMatrix;
    };
}

#endif //RENDERER_SHADERENVIRONMENT_HPP
