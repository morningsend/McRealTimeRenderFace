//
// Created by Zaiyang Li on 19/02/2018.
//

#ifndef RENDERER_RASTERIZER_HPP
#define RENDERER_RASTERIZER_HPP
#include "../SDLauxiliary.h"
#include "Renderer.hpp"
#include "../scene/Scene.hpp"
#include "../scene/Line.hpp"
#include "../scene/Triangle.hpp"
#include "FrameBuffer.hpp"

#include "PrimitivePreprocessor.hpp"

namespace McRenderer {

    using namespace glm;
    enum class FaceRenderMode {
        FrontOnly,
        DoubleSide,
        Edge,
    };

    struct RasterizerConfig {
        FaceRenderMode faceMode { FaceRenderMode::DoubleSide };
        int viewportWidth{1};
        int viewportHeight{1};
    };
    class Rasterizer : public Renderer {
    private:
        int width{1};
        int height{1};
        vec4* frameBuffer {nullptr};
        float* depthBuffer {nullptr};
        RasterizerConfig config {};
    public:
        void fillTriangle(Triangle& triangle, screen* screen);

        void drawPoint(vec4 v0, float radius = 1.0f);
        void drawLine(vec4 v0, vec4 v1, float thickness);

        void drawHorizontalLine(screen* screen, vec3 colour, int x1, int x2, int y);
        void drawHorizontalLine(vec4* colourBuffer, vec3 colour, int x1, int x2, int y);
        Rasterizer(int width, int height): width{width}, height{height} {}
        Rasterizer(RasterizerConfig config) {}
        void renderToScreen(screen* screen, Scene& scene) override;
        ~Rasterizer() = default;
    };

}

#endif //RENDERER_RASTERIZER_HPP
