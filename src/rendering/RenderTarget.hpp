//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_RENDERTARGET_HPP
#define RENDERER_RENDERTARGET_HPP

#include <glm/vec3.hpp>
#include "../Exception.hpp"

namespace McRenderer {
    using namespace glm;
    class RenderTarget {
    private:
        int width;
        int height;
        float* frameBuffer;
    public:
        RenderTarget(int widthIn = 256, int heightIn = 256);
        ~RenderTarget();
        void setColor(int x, int y, vec3 colour);
    };
}


#endif //RENDERER_RENDERTARGET_HPP
