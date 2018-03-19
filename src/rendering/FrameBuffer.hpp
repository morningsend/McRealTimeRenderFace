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
        float clearDepth {1};

    public:
        FrameBuffer(int width, int height, vec4 clearColour = vec4(0), float clearDepth = 1.0f);
        void setClearDepth(float );
        void setClearColour(vec4 colour);
        void copyToScreen(screen* screen);
        void clear();
        void clearColourBuffer();
        void clearDepthBuffer();
        void setColour(int x, int y, vec4 colour);
        void setColourAndDepthLessThan(int x, int y, vec4 colour, float d);
        void setColourAndDepth(int x, int y, vec4 colour, float d);
        void setDepthLessThan(int x, int y, float d);
        bool testDepthLessThan(int x, int y, float d);
        ~FrameBuffer();
    };
}


#endif //RENDERER_RENDERTARGET_HPP
