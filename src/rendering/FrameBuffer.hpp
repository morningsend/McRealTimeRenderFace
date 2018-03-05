//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_RENDERTARGET_HPP
#define RENDERER_RENDERTARGET_HPP

#include <glm/vec3.hpp>
#include "../SDLauxiliary.h"

namespace McRenderer {
    using namespace glm;
    class FrameBuffer {
    private:
        int width;
        int height;

        vec4* colourBuffer {nullptr};
        vec4 clearColour{0};
        float* depthBuffer {nullptr};
        float clearDepth {0};

    public:
        FrameBuffer(int width, int height, vec4 clearColour = vec4(0), float clearDepth = 1.0f);
        void setClearDepth(float );
        void setClearColour(vec4 colour);
        void copyToScreen(screen* screen);
        void clear();
        void clearColourBuffer();
        void clearDepthBuffer();
        ~FrameBuffer();
    };
}


#endif //RENDERER_RENDERTARGET_HPP
