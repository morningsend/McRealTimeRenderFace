//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_MATERIAL_HPP
#define RENDERER_MATERIAL_HPP

#include "../common.h"
#include "TextureSampler2D.hpp"

namespace McRenderer {
    using namespace glm;
    struct MaterialSpec {
        vec3 basecolour{0.8f};
        std::string basecolourMap{};

        float metalness{0.05};
        std::string metalnessMap;

        vec3 specularColor{0.2f};
        std::string specularMap{};

        float roughness;
        std::string roughnessMap{};

        vec3 refraction{0};
        std::string refractionMap{};

        std::string normalMap{};
        std::string bumpMap{};
    };

    struct Material {
        TextureSampler2D basecolourSampler;
        GrayScaleTextureSampler2D roughnessSampler;
        GrayScaleTextureSampler2D metalnessSampler;
        TextureSampler2D specularColourSampler;
        TextureSampler2D normalSampler;
    };

    void buildMaterial(const MaterialSpec& spec, Material& material);
}


#endif //RENDERER_MATERIAL_HPP
