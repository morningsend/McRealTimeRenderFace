//
// Created by Zaiyang Li on 19/02/2018.
//

#ifndef RENDERER_RASTERIZER_HPP
#define RENDERER_RASTERIZER_HPP

#include "Renderer.hpp"
#include "../scene/Scene.hpp"
#include "../scene/Line.hpp"

namespace McRenderer {
    #define INSIDEMASK 0
    #define LEFTMASK 1 << 0
    #define RIGHTMASK 1 << 1
    #define TOPMASK 1 << 2
    #define BOTTOMMASK 1 << 3
    #define FRONTMASK 1 << 4
    #define BACKMASK 1 << 5
    using namespace glm;
    class Rasterizer : public Renderer {
    private:
        Scene* scene;
        vec3* frameBuffer;
        float* depthBuffer;
    public:
        Rasterizer(Scene* sceneIn, int wdith, int height): scene{sceneIn} {}
        void renderToScreen(screen* screen) override;
        ~Rasterizer() = default;
    };

    /**
     * Clip a transformed triangle against a 3D canonical view volumn
     * where -1 <= x <= 1, -1 <= y <= 1, -1 <= z <= 1
     * @param triangle
     * @param result
     */
    void clipLine3D(const Line& line, Line& result);
    void clipTriangle3D(const Triangle &triangle, vector<Triangle> &result);
    void clipTriangleFrustum(const Triangle& triangle, vector<Triangle>& result);
    void drawLine(screen *screen, int x1, int y1, int x2, int y2);
    int computeOutcode3D(vec4 point);
}



#endif //RENDERER_RASTERIZER_HPP
