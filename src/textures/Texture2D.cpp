#include "Texture2D.hpp"
#
using namespace std;
using namespace glm;
using namespace cv;

namespace McRenderer {
    glm::vec3 Texture2D::sample(glm::vec2 uvCoord, FilteringMethod filter) const {
        uvCoord = clamp(uvCoord, vec2(0), vec2(1));
        uvCoord.y = 1 - uvCoord.y;
        float b = 0, g = 0, r = 0;
        int x = static_cast<int>(columns * uvCoord.x);
        int y = static_cast<int>(rows * (1 - uvCoord.y));
        Vec3b pixel;
        switch(filter) {
            case Bilinear:
                return sampleBilinear(uvCoord);
            case Nearest:
                pixel = image.at<Vec3b>(y, x);
                b = pixel[0] / 255.0f, g = pixel[1]/255.0f, r = pixel[2]/255.0f;
                break;
            case Anisotropic:
                break;
            default:
                pixel = image.at<Vec3b>(y, x);
                b = pixel[0] / 255.0f, g = pixel[1]/255.0f, r = pixel[2]/255.0f;
                break;
        }
        return glm::vec3(r,g,b);
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
            // adding 1 pixel a border to the original image to speed up sampling calculations.
            copyMakeBorder(image, image, 1,1,1,1, BORDER_REPLICATE);
        }
    }

    glm::vec3 Texture2D::sampleBilinear(glm::vec2 uvCoord) const {
        constexpr float uCharToFloat = 1.0f/255.0f;

        uvCoord.x *= columns + 0.5f;
        uvCoord.y *= rows + 0.5f;

        i32vec2 lowerLeft = i32vec2(floor(uvCoord));
        vec2 t = uvCoord - vec2(lowerLeft.x, lowerLeft.y);
        vec2 oneMinusT = vec2(1) - t;

        Vec3f result = Vec3f(image.at<Vec3b>(lowerLeft.x, lowerLeft.y)) * oneMinusT.x;
        result += Vec3f(image.at<Vec3b>(lowerLeft.x + 1, lowerLeft.y)) * t.x;
        result *= oneMinusT.y;

        Vec3f result2 = Vec3f(image.at<Vec3b>(lowerLeft.x,lowerLeft.y+1)) * oneMinusT.x;
        result2 += Vec3f(image.at<Vec3b>(lowerLeft.x + 1, lowerLeft.y + 1)) * t.x;
        result2 *= t.y;

        result += result2;
        result *= uCharToFloat;

        return glm::vec3(result[2], result[1], result[0]);
    }
}
