//
// Created by Zaiyang Li on 21/03/2018.
//

#include "Texture2D.hpp"
using namespace Magick;
using namespace std;

namespace McRenderer {
    glm::vec3 Texture2D::sample(float u, float v, FilteringMethod filter) {
        return glm::vec3(0.8f);
    }

    void Texture2D::loadImage(std::string path) {
        try {
            image.read(path);
        } catch(Exception& error) {
            cerr << "Error reading texture: " << path << endl;
        }
    }
}
