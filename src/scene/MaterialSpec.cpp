//
// Created by Zaiyang Li on 31/01/2018.
//

#include "MaterialSpec.hpp"

namespace McRenderer {

    void buildMaterial(const McRenderer::MaterialSpec &spec, McRenderer::Material &material) {
        // if texture map is not available, fall back to default colour

        material.diffuseColourSampler = TextureSampler2D(
                Texture2D::load(spec.diffuseMap),
                spec.diffuseColor
        );
        material.diffuseRoughnessSampler = GrayScaleTextureSampler2D(
                nullptr,
                spec.diffuseRoughness
        );

        material.specularColourSampler = TextureSampler2D(
                Texture2D::load(spec.specularMap),
                spec.specularColor
        );

        material.specularRoughnessSampler = GrayScaleTextureSampler2D(
                nullptr,
                spec.specularRoughness
        );
        material.normalSampler = TextureSampler2D(
                Texture2D::load(spec.normalMap),
                vec3(.5f, .5f, 1.0f)
        );
    }
}
