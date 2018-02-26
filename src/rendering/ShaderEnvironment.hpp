//
// Created by Zaiyang Li on 26/02/2018.
//

#ifndef RENDERER_SHADERENVIRONMENT_HPP
#define RENDERER_SHADERENVIRONMENT_HPP

#include <glm/glm.hpp>

struct ShaderEnvironment {
    glm::mat4 viewingMatrix;
    glm::mat4 projectionMatrix;
    glm::vec4 cameraPosition;
    glm::vec4 cameraDirection;
};

#endif //RENDERER_SHADERENVIRONMENT_HPP
