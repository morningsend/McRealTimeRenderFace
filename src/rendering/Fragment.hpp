//
// Created by Zaiyang Li on 07/03/2018.
//

#ifndef RENDERER_FRAGMENT_HPP
#define RENDERER_FRAGMENT_HPP

#include <glm/glm.hpp>
namespace McRenderer {
    struct Fragment {
        glm::vec4 screenPosition;
        int pixelPositionX;
        int pixelPositionY;
    };
}

#endif //RENDERER_FRAGMENT_HPP
