//
// Created by Zaiyang Li on 19/02/2018.
//

#include "Rasterizer.hpp"
#include "../SDLauxiliary.h"

#include "../scene/Line.hpp"

void McRenderer::Rasterizer::renderToScreen(screen *screen) {

    const int width = screen->width;
    const int height = screen->height;
    memset(screen->buffer, 0, sizeof(uint32_t) * width * height);
    vec4 point(.5, 0, 1, 1);
    vec4 point2(-.5, 0, 1, 1);

    mat4 projMat = scene->camera.projectionMatrix();
    std::cout << projMat[0][0] << ' ' << projMat[0][1] << ' ' << projMat[0][2] << ' ' << projMat[0][3] << ' '<<'\n'
              << projMat[1][0] << ' ' << projMat[1][1] << ' ' << projMat[1][2] << ' ' << projMat[1][3] << ' '<<'\n'
              << projMat[2][0] << ' ' << projMat[2][1] << ' ' << projMat[2][2] << ' ' << projMat[2][3] << ' '<<'\n'
              << projMat[3][0] << ' ' << projMat[3][1] << ' ' << projMat[3][2] << ' ' << projMat[3][3] << ' '<<'\n'<<endl;

    mat4 viewProjectionMatrix = scene->camera.viewProjectionMatrix();
    vec4 transformedPoint = viewProjectionMatrix * point;
    vec4 transformedPoint2 = viewProjectionMatrix * point2;
    cout << transformedPoint.x << ' ' << transformedPoint.y << ' ' << transformedPoint.z << ' ' << transformedPoint.w <<endl;
    int x = (int) (transformedPoint.x/transformedPoint.w * width / 2 + width / 2);
    int y = (int) (transformedPoint.y/transformedPoint.w * height / 2 + height / 2);
    int x2 = (int) (transformedPoint2.x/transformedPoint2.w * width / 2 + width / 2);
    int y2 = (int) (transformedPoint2.y/transformedPoint2.w * height / 2 + height / 2);
    cout << x << ' ' << y << endl;

    if(x >= 0 && x < width && y >= 0 && y < height && transformedPoint.z >= 0) {
        PutPixelSDL(screen, x, y, vec3(1.0f));
    }
    if(x2 >= 0 && x2 < width && y2 >= 0 && y2 < height && transformedPoint.z >= 0) {
        PutPixelSDL(screen, x2, y2, vec3(1.0f));
    }
/*
    Line line = Line({-.5, .2, 1, 0}, {.5, -.1, 1, 0});
    // vec4 point(-.5, .2, -1, 1);

    mat4 viewProjectionMatrix = scene->camera.viewProjectionMatrix();
    ProjectedLine projLine = line.projectLine(viewProjectionMatrix);

    int x1 = (int) (projLine.ends[0].x/projLine.ends[0].w * width / 2 + width / 2);
    int y1 = (int) (projLine.ends[0].y/projLine.ends[0].w * height / 2 + height / 2);
    int x2 = (int) (projLine.ends[1].x/projLine.ends[1].w * width / 2 + width / 2);
    int y2 = (int) (projLine.ends[1].y/projLine.ends[1].w * height / 2 + height / 2);


    std::cout << x1 << ' '<< y1 <<' '<<'\n';
    std::cout << x2 << ' '<< y2 <<' '<<'\n';

    if(x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) {
        PutPixelSDL(screen, x1, y1, vec3(1.0f));
    }

    if(x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) {
        PutPixelSDL(screen, x2, y2, vec3(1.0f));
    }

*/
}
