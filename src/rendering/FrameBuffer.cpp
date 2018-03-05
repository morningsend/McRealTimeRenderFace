//
// Created by Zaiyang Li on 31/01/2018.
//

#include "FrameBuffer.hpp"
#include "../SDLauxiliary.h"

namespace McRenderer {

    FrameBuffer::~FrameBuffer() {
        delete[] colourBuffer;
        delete[] depthBuffer;
    }

    FrameBuffer::FrameBuffer(int width, int height, vec4 clearColour, float clearDepth)
            : width{width}, height{height}, clearColour{clearColour}, clearDepth{clearDepth} {

        if (width < 1 || height < 1) {
            throw 1;
        }
        colourBuffer = new vec4[width * height];
        depthBuffer = new float[width * height];
    }

    void FrameBuffer::copyToScreen(screen *screen) {
        const int minWidth = screen->width < width ? screen->width : width;
        const int minHeight = screen->height < height ? screen->height : height;
        std::cout << minWidth << ' ' << minHeight << ' ' << width << ' ' << height << std::endl;
        for(int i = 0; i < minHeight; i++) {
            for(int j = 0; j < minWidth; j++) {
                PutPixelSDL(screen, j, i, vec3(colourBuffer[i * width + j]));
            }
        }
    }

    void FrameBuffer::setClearDepth(float depth) {
        clearDepth = depth;
    }

    void FrameBuffer::setClearColour(vec4 colour) {
        clearColour = colour;
    }

    void FrameBuffer::clear() {
        for(int i = 0; i < width; i++) {
            for(int j = 0; j < height; i++) {
                colourBuffer[i * width + j] = clearColour;
                depthBuffer[i * width + j] = clearDepth;
            }
        }
    }
    void FrameBuffer::clearColourBuffer() {
        for(int i = 0; i < width; i++) {
            for(int j = 0; j < height; i++) {
                colourBuffer[i * width + j] = clearColour;
            }
        }
    }
    void FrameBuffer::clearDepthBuffer() {
        for(int i = 0; i < width; i++) {
            for(int j = 0; j < height; i++) {
                depthBuffer[i * width + j] = clearDepth;
            }
        }
    }
}