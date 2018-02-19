//
// Created by Zaiyang Li on 19/02/2018.
//

#ifndef RENDERER_RASTERIZER_HPP
#define RENDERER_RASTERIZER_HPP

#include "Renderer.hpp"
#include "../scene/Scene.hpp"

namespace McRenderer {
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
}


#endif //RENDERER_RASTERIZER_HPP
