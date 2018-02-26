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

        vec3* colourBuffer {nullptr};
        vec3 clearColour{0};
        float* depthBuffer {nullptr};
        float clearDepth {0};

    public:
        FrameBuffer(int width, int height, vec3 clearColour = vec3(0), float clearDepth = 1.0f);

        // prevent copying.
        FrameBuffer(const FrameBuffer& other) = delete;
        FrameBuffer(const FrameBuffer&& other) = delete;

        void setClearDepth(float );
        void setClearColour(vec3 colour);
        void copyToScreen(screen* screen);
        void clear();
        void clearColourBuffer();
        void clearDepthBuffer();
        ~FrameBuffer();
    };
}


#endif //RENDERER_RENDERTARGET_HPP
