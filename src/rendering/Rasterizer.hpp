//
// Created by Zaiyang Li on 19/02/2018.
//

#ifndef RENDERER_RASTERIZER_HPP
#define RENDERER_RASTERIZER_HPP

#include "Renderer.hpp"

namespace McRenderer {
    using namespace glm;
    class Rasterizer : public Renderer {
    public:
        void renderToScreen(screen* screen) override;
        ~Rasterizer() = default;
    };
}


#endif //RENDERER_RASTERIZER_HPP
