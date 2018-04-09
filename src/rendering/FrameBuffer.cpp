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
        clear();
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
        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                colourBuffer[i * width + j] = clearColour;
                depthBuffer[i * width + j] = clearDepth;
            }
        }
    }
    void FrameBuffer::clearColourBuffer() {
        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                colourBuffer[i * width + j] = clearColour;
            }
        }
    }
    void FrameBuffer::clearDepthBuffer() {
        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                depthBuffer[i * width + j] = clearDepth;
            }
        }
    }

    void FrameBuffer::setColour(int x, int y, vec4 colour) {
        if(x < 0 || x >= width || y < 0 || y >= height) {
            std::cout<<"framebuffer set diffuse out side range" << std::endl;
            return;
        }
        colourBuffer[x + y * width] = colour;
    }

    void FrameBuffer::setColourAndDepthLessThan(int x, int y, vec4 colour, float d) {
        if(x < 0 || x >= width || y < 0 || y >= height) {
            std::cout<<"framebuffer set diffuse out side range" << std::endl;
            return;
        }
        float& originalDepth = depthBuffer[x + y * width];
        vec4& originColour = colourBuffer[x + y * width];
        if(originalDepth > d) {
            originalDepth = d;
            originColour = colour;
        }
    }

    void FrameBuffer::setDepthLessThan(int x, int y, float d) {
        if(d <= depthBuffer[x + y * width]) {
            depthBuffer[x + y * width] = d;
        }
    }

    bool FrameBuffer::testDepthLessThan(int x, int y, float d) {
        return d <= depthBuffer[x + y * width];
    }

    void FrameBuffer::setColourAndDepth(int x, int y, vec4 colour, float d) {
        if(x < 0 || x >= width || y < 0 || y >= height) {
            std::cout<<"framebuffer set diffuse out side range" << std::endl;
            return;
        }
        depthBuffer[x + y * width] = d;
        colourBuffer[x + y * width] = colour;
    }
}