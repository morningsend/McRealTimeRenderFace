//
// Created by Zaiyang Li on 31/03/2018.
//

#ifndef RENDERER_COLOURSAMPLER_HPP
#define RENDERER_COLOURSAMPLER_HPP
#include <glm/glm.hpp>
#include "../textures/Texture2D.hpp"

namespace McRenderer {


    template<typename ValueType> class Sampler2D {
    public:
        Sampler2D() {};

        virtual ValueType sample(glm::vec2 uvCoord) const { return ValueType{}; }
    };

    class ConstantColourSampler2D : public Sampler2D<glm::vec3> {
    private:
        glm::vec3 colour;
    public:
        ConstantColourSampler2D() : ConstantColourSampler2D(glm::vec3(1.0f)) {}
        ConstantColourSampler2D(glm::vec3 colourIn): colour{colourIn} {}
        glm::vec3 sample(glm::vec2 uvCoord) const override  {
            return colour;
        }
    };

    class TextureSampler2D : public Sampler2D<glm::vec3> {
    private:
        Texture2D texture;
    public:
        TextureSampler2D(Texture2D textureIn) : texture{textureIn} {

        }

        glm::vec3 sample(glm::vec2 uvCoord) const override {
            return glm::vec3(0);
        }
    };

    class GrayScaleTextureSampler2D : public Sampler2D<float> {
    private:
        Texture2D texture;
    public:
        GrayScaleTextureSampler2D(const Texture2D& textureIn) : texture{textureIn} {

        }

        float sample(glm::vec2 uvCoord) const override {
            return 1.0f;
        }
    };

    class ConstantValueSampler2D : public Sampler2D<float> {
    private:
        float value {0.0f};
    public:
        ConstantValueSampler2D(float valueIn) : value{valueIn} {};

        float sample(glm::vec2 uvCoord) const override {
            return value;
        }
    };
}


#endif //RENDERER_COLOURSAMPLER_HPP
