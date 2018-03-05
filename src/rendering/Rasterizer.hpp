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

namespace McRenderer {

    using namespace glm;
    enum class FaceRenderMode {
        FrontOnly,
        DoubleSide
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
        void drawHorizontalLine(screen* screen, vec3 colour, int x1, int x2, int y);
        void drawHorizontalLine(vec4* colourBuffer, vec3 colour, int x1, int x2, int y);
        Rasterizer(int width, int height): width{width}, height{height} {}
        Rasterizer(RasterizerConfig config) {}
        void renderToScreen(screen* screen, Scene& scene) override;
        ~Rasterizer() = default;
    };

}

vec4 lineAligndPlaneIntersection(Line line, vec3 plane);
void clipLine(Line *line);
void drawLine(screen *screen, int x1, int y1, int x2, int y2);
void bhm_line(screen *screen, int x1,int y1,int x2,int y2);

#endif //RENDERER_RASTERIZER_HPP
