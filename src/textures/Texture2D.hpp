//
// Created by Zaiyang Li on 21/03/2018.
//

#ifndef RENDERER_TEXTURE_HPP
#define RENDERER_TEXTURE_HPP

#include "../common.h"
#include <opencv2/opencv.hpp>

namespace McRenderer {
    enum FilteringMethod {
        Nearest,
        Anisotropic,
        Bilinear,
    };

    class Texture2D {
    private:
        bool imageLoaded { false };
        cv::Mat image;
        void loadImage(std::string path, bool gammaToLinear);
        int columns;
        int rows;
    public:
        Texture2D(std::string path, bool generateMipMaps = false, bool gammaToLinear = false){
            std::cout << "gamma to linear " << gammaToLinear << std::endl;
            if(!path.empty())
                loadImage(path, gammaToLinear);
        }

        bool isLoaded() const {
            return imageLoaded;
        }

        Texture2D(const Texture2D& other) {
            this->image = other.image;
        }

        ~Texture2D() { }
        glm::vec3 sample(glm::vec2 uvCoord, FilteringMethod filter = FilteringMethod::Nearest) const;
        inline glm::vec3 sampleBilinear(glm::vec2 uvCoord) const;
        static Texture2D* load(std::string path, bool gammaToLinear = false) {
            Texture2D* texture = new Texture2D(path, false, gammaToLinear);
            if(texture->isLoaded()) {
                return texture;
            } else {
                delete texture;
                return nullptr;
            }
        }
    };
}


#endif //RENDERER_TEXTURE_HPP
