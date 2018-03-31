//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_MATERIAL_HPP
#define RENDERER_MATERIAL_HPP
#include <string>
#include <glm/glm.hpp>
#include "TextureSampler2D.hpp"

namespace McRenderer {
    using namespace glm;
    struct MaterialSpec {
        vec3 diffuseColor{0.8f};
        std::string diffuseMap{};
        float diffuseRoughness;

        vec3 specularColor{0.2f};
        std::string specularMap{};
        float specularRoughness;

        vec3 refraction{0};
        std::string refractionMap{};

        std::string normalMap{};
        std::string bumpMap{};
    };

    struct Material {
        TextureSampler2D diffuseColourSampler;
        GrayScaleTextureSampler2D diffuseRoughnessSampler;
        TextureSampler2D specularColourSampler;
        GrayScaleTextureSampler2D specularRoughnessSampler;

        TextureSampler2D normalSampler;
    };

    void buildMaterial(const MaterialSpec& spec, Material& material);
}


#endif //RENDERER_MATERIAL_HPP
