//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_MATERIAL_HPP
#define RENDERER_MATERIAL_HPP
#include <string>
#include <glm/glm.hpp>
#include "TextureSampler2D.hpp"
#include "ColourSampler.hpp"

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
        Sampler2D<vec3> diffuseColourSampler;
        Sampler2D<float> diffuseRoughnessSampler;
        Sampler2D<vec3> specularColourSampler;
        Sampler2D<float> specularRoughnessSampler;
        Sampler2D<vec3> normalSampler;
    };

    void buildMaterial(const MaterialSpec& spec, Material& material);

    template<class T> Sampler2D<T> buildSampler(const std::string path, T defaultValue) {
        return Sampler2D<T>{};
    }

    template<>
    Sampler2D<vec3> buildSampler<vec3>(const std::string path, vec3 defaultColour);

    template<>
    Sampler2D<float> buildSampler<float>(const std::string path, float defaultValue);
}


#endif //RENDERER_MATERIAL_HPP
