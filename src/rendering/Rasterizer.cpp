//
// Created by Zaiyang Li on 19/02/2018.
//

#include "Rasterizer.hpp"
#include "../SDLauxiliary.h"

void McRenderer::Rasterizer::renderToScreen(screen *screen) {
    const int width = screen->width;
    const int height = screen->height;
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            PutPixelSDL(screen, i, j, vec3(1.0f));
        }
    }
}
