//
// Created by Zaiyang Li on 09/04/2018.
//

#include "AntiAliasingPostProcessing.hpp"
namespace McRenderer {

    float AntiAliasingPostProcessing::luminance(vec3 &colour) {
        constexpr vec3 weights(0.299f, 0.587f, 0.114f);
        return glm::dot(colour, weights);
    }
}