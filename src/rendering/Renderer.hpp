//
// Created by Zaiyang Li on 19/02/2018.
//

#ifndef RENDERER_RENDERER_HPP
#define RENDERER_RENDERER_HPP

#include "../SDLauxiliary.h"

namespace McRenderer {
    class Renderer {
    public:
        virtual ~Renderer() = default;
        virtual void renderToScreen(screen* screen) = 0;
    };
}


#endif //RENDERER_RENDERER_HPP
