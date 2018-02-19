//
// Created by Zaiyang Li on 19/02/2018.
//

#include "Rasterizer.hpp"
#include "../SDLauxiliary.h"

void McRenderer::Rasterizer::renderToScreen(screen *screen) {
    const int width = screen->width;
    const int height = screen->height;

    vec4 point(0, 0, -1, 1);
    mat4 viewProjectionMatrix = scene->camera.viewProjectionMatrix();
    vec4 transformedPoint = viewProjectionMatrix * point;
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {

            PutPixelSDL(screen, (int) transformedPoint.x, (int) transformedPoint.y, vec3(1.0f));
        }
    }
}
