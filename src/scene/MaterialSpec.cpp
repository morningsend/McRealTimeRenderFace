//
// Created by Zaiyang Li on 31/01/2018.
//

#include "MaterialSpec.hpp"

namespace McRenderer {

    void buildMaterial(const McRenderer::MaterialSpec &spec, McRenderer::Material &material) {
        // if texture map is not available, fall back to default colour

        material.diffuseColourSampler = buildSampler(spec.diffuseMap, spec.diffuseColor);
        material.diffuseRoughnessSampler = buildSampler("", spec.diffuseRoughness);

        material.specularColourSampler = buildSampler(spec.specularMap, spec.specularColor);
        std::cout << "specular colour " << spec.specularColor.x << ' ' << spec.specularColor.y << ' ' << spec.specularColor.z << std::endl;
        material.specularRoughnessSampler = buildSampler("", spec.specularRoughness);

        //default normal value is the vector (0,0,1) in tangent space.
        // mapped to region [0, 1]^3
        // (0,0,1) * 0.5 + (0.5, 0.5, 0.5) = (0.5, 0.5, 1.0)
        material.normalSampler = buildSampler(spec.normalMap, vec3(.5f, .5f, 1.0f));
    }

    template<>
    Sampler2D<vec3> buildSampler<vec3>(const std::string path, vec3 defaultColour) {
        if(path.empty()) {
            return ConstantColourSampler2D(defaultColour);
        } else {
            Texture2D texture(path);
            return TextureSampler2D(texture);
        };
    }

    template<>
    Sampler2D<float> buildSampler<float>(const std::string path, float defaultValue) {
        if(path.empty()){
            return ConstantValueSampler2D(defaultValue);
        } else {
            Texture2D texture{path};
            return GrayScaleTextureSampler2D(texture);
        }
    }
}
