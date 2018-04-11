//
// Created by Zaiyang Li on 31/03/2018.
//

#ifndef RENDERER_COLOURSAMPLER_HPP
#define RENDERER_COLOURSAMPLER_HPP

#include "../common.h"

#include "../textures/Texture2D.hpp"

namespace McRenderer {


    template<typename ValueType> class Sampler2D {
    public:
        Sampler2D() {};

        virtual ValueType sample(glm::vec2 uvCoord) const { return ValueType{}; }
        virtual ~Sampler2D(){}
    };
    template <typename ValueType> class Sampler3D {
    public:
        Sampler3D() {};

        virtual ValueType sample(glm::vec3 coord) const {
            return ValueType{};
        }
        virtual ~Sampler3D(){}
    };
    class BufferSampler2D : public Sampler2D<glm::vec3> {
    private:
        glm::vec4* buffer;
        int width;
        int height;
    public:
        BufferSampler2D(int width, int height, glm::vec4* bufferIn): width{width}, height{height}, buffer{bufferIn} {}
        virtual ~BufferSampler2D() = default;

        inline glm::vec3 sample(glm::vec2 uvCoord) const override {
            uvCoord = clamp(uvCoord, glm::vec2(0), glm::vec2(1));
            int x = (int) (uvCoord.x * (width-1) + 0.5f);
            int y = (int) ((1 - uvCoord.y) * (height - 1) + 0.5f);
            return glm::vec3(buffer[y * width + x]);
        }
    };
    class TextureSampler2D : public Sampler2D<glm::vec3> {
    private:
        std::unique_ptr<Texture2D> texture;
        glm::vec3 defaultColour;
    public:
        TextureSampler2D(Texture2D* textureIn, glm::vec3 colour = glm::vec3(0))
                : texture{textureIn}, defaultColour{colour} {

        }

        TextureSampler2D(): texture{nullptr}, defaultColour(glm::vec3(0.0)) {

        }
        glm::vec3 sample(glm::vec2 uvCoord) const override {
            if(texture) {
                return texture->sample(uvCoord, FilteringMethod::Bilinear);
            }
            return defaultColour;
        }
    };

    class GrayScaleTextureSampler2D : public Sampler2D<float> {
    private:
        std::unique_ptr<Texture2D> texture;
        float defaultValue;
    public:
        GrayScaleTextureSampler2D(Texture2D* textureIn, float value)
                : texture{textureIn}, defaultValue{value} { }

        GrayScaleTextureSampler2D()
                : texture{nullptr}, defaultValue{0.0f} {

        }
        float sample(glm::vec2 uvCoord) const override {
            if(texture){
                return (texture->sample(uvCoord)).x;
            }
            return defaultValue;
        }
    };

}


#endif //RENDERER_COLOURSAMPLER_HPP
