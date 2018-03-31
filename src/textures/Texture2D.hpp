//
// Created by Zaiyang Li on 21/03/2018.
//

#ifndef RENDERER_TEXTURE_HPP
#define RENDERER_TEXTURE_HPP

#include <iostream>
#include <glm/glm.hpp>
#include <ImageMagick-7/Magick++.h>

namespace McRenderer {
    enum FilteringMethod {
        Nearest,
        Anisotropic,
        Trilinear,
        Bilinear,
    };
    class Texture2D {
    private:
        Magick::Image image;
        void loadImage(std::string path);
    public:
        Texture2D(std::string path,
                FilteringMethod filtering = FilteringMethod::Nearest,
                bool generateMipMaps = false){
            loadImage(path);
        }

        Texture2D(const Texture2D& other) {
            this->image = other.image;
        }
        ~Texture2D() { }
        glm::vec3 sample(float u, float v, FilteringMethod filter = FilteringMethod::Nearest);
    };
}


#endif //RENDERER_TEXTURE_HPP
