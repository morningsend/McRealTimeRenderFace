//
// Created by Zaiyang Li on 03/04/2018.
//

#ifndef RENDERER_SPHERICALMAPSAMPLER_HPP
#define RENDERER_SPHERICALMAPSAMPLER_HPP
#include <memory>
#include <glm/glm.hpp>
#include "TextureSampler2D.hpp"

namespace McRenderer {
    using namespace glm;

    class CubeMapSampler : public Sampler3D<glm::vec3>, public Sampler2D<glm::vec3> {
    private:
        std::unique_ptr<Texture2D> texture;
    public:
        CubeMapSampler(Texture2D* textureIn): texture{textureIn} {}

        inline vec2 cartesianToSphericalPolar(vec3 vector) const;
        inline vec2 normalizedCartesianToSphericalPolar(vec3 vector) const;
        inline vec3 sample(vec3 normal) const override;
    };
}


#endif //RENDERER_SPHERICALMAPSAMPLER_HPP
