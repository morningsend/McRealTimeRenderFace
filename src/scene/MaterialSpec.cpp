//
// Created by Zaiyang Li on 31/01/2018.
//

#include "MaterialSpec.hpp"

namespace McRenderer {

    void buildMaterial(const McRenderer::MaterialSpec &spec, McRenderer::Material &material) {
        // if texture map is not available, fall back to default colour

        material.basecolourSampler = TextureSampler2D(
                Texture2D::load(spec.basecolourMap),
                spec.basecolour
        );
        material.roughnessSampler = GrayScaleTextureSampler2D(
                Texture2D::load(spec.roughnessMap),
                spec.roughness
        );

        material.specularColourSampler = TextureSampler2D(
                Texture2D::load(spec.specularMap),
                spec.specularColor
        );

        material.normalSampler = TextureSampler2D(
                Texture2D::load(spec.normalMap),
                vec3(.5f, .5f, 1.0f)
        );

        material.metalnessSampler = GrayScaleTextureSampler2D(
                Texture2D::load(spec.metalnessMap),
                spec.metalness
        );
    }
}
