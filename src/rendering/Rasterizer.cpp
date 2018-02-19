//
// Created by Zaiyang Li on 19/02/2018.
//

#include "Rasterizer.hpp"
#include "../SDLauxiliary.h"

void McRenderer::Rasterizer::renderToScreen(screen *screen) {

    const int width = screen->width;
    const int height = screen->height;
    memset(screen->buffer, 0, sizeof(uint32_t) * width * height);
    vec4 point(0, 0, -1, 1);
    mat4 viewProjectionMatrix = scene->camera.viewProjectionMatrix();
    vec4 transformedPoint = viewProjectionMatrix * point;
    cout << transformedPoint.x << ' ' << transformedPoint.y << ' ' << transformedPoint.z << ' ' << transformedPoint.w <<endl;
    int x = (int) (transformedPoint.x * width / 2 + width / 2);
    int y = (int) (transformedPoint.y * height / 2 + height / 2);
    cout << x << ' ' << y << endl;

    if(x >= 0 && x < width && y >= 0 && y < height) {
        PutPixelSDL(screen, x, y, vec3(1.0f));
    }
}
