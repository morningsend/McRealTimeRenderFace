//
// Created by Zaiyang Li on 19/02/2018.
//

#ifndef RENDERER_RASTERIZER_HPP
#define RENDERER_RASTERIZER_HPP

#include "Renderer.hpp"
#include "../scene/Scene.hpp"
#include "../scene/Line.hpp"
#include "../scene/Triangle.hpp"

#define INSIDEMASK 0
#define LEFTMASK 1 << 0
#define RIGHTMASK 1 << 1
#define TOPMASK 1 << 2
#define BOTTOMMASK 1 << 3
#define FRONTMASK 1 << 4
#define BACKMASK 1 << 5

namespace McRenderer {

    using namespace glm;
    class Rasterizer : public Renderer {
    private:
        Scene* scene;
        vec3* frameBuffer;
        float* depthBuffer;
    public:
        void fillTriangle(McRenderer::Triangle& triangle, screen* screen);
        Rasterizer(Scene* sceneIn, int wdith, int height): scene{sceneIn} {}
        void renderToScreen(screen* screen) override;
        ~Rasterizer() = default;
    };

}

vec4 lineAligndPlaneIntersection(Line line, vec3 plane);
void clipLine(Line *line);
void drawLine(screen *screen, int x1, int y1, int x2, int y2);
void bhm_line(screen *screen, int x1,int y1,int x2,int y2);
int computeOutcode3D(vec4 point, vec4 min, vec4 max);
#endif //RENDERER_RASTERIZER_HPP
