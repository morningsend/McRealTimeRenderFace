#include "Texture2D.hpp"
#
using namespace std;
using namespace glm;
using namespace cv;

namespace McRenderer {
    glm::vec3 Texture2D::sample(glm::vec2 uvCoord, FilteringMethod filter) const {
        uvCoord = clamp(uvCoord, vec2(0), vec2(1));
        switch(filter) {
            case FilteringMethod::Nearest:
            case FilteringMethod::Anisotropic:
            case FilteringMethod::Bilinear:
                int x = static_cast<int>(columns * uvCoord.x);
                int y = static_cast<int>(rows * uvCoord.y);
                Vec3b pixel = image.at<Vec3b>(y, x);
                float b = pixel[0] / 255.0f, g = pixel[1]/255.0f, r = pixel[2]/255.0f;
                return glm::vec3(r,g,b);
        }

    }

    void Texture2D::loadImage(std::string path) {
        cout<<"loading texture imagee: " << path << endl;
        image = cv::imread(path);
        if(image.data == nullptr) {
            imageLoaded = false;
        } else {
            imageLoaded = true;
            rows = image.rows;
            columns = image.cols;
        }
    }
}
