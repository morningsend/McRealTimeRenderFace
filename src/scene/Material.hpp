//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_MATERIAL_HPP
#define RENDERER_MATERIAL_HPP

#include <glm/glm.hpp>
#include "TextureSampler2D.hpp"

namespace McRenderer {
    using namespace glm;
    struct Material {
        vec3 diffuseColor;
        vec3 specularColor;
        vec3 reflectionColor;
        vec3 refraction;

    };
}


#endif //RENDERER_MATERIAL_HPP
