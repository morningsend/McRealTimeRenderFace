//
// Created by Zaiyang Li on 19/02/2018.
//

#include "Rasterizer.hpp"
#include "../SDLauxiliary.h"

#include "../scene/Line.hpp"
namespace McRenderer {
    void Rasterizer::renderToScreen(screen *screen) {

        const int width = screen->width;
        const int height = screen->height;
        memset(screen->buffer, 0, sizeof(uint32_t) * width * height);
        // vec4 point(.5, 0, 1, 1);
        // vec4 point2(-.5, 0, 1, 1);
        //
        // mat4 projMat = scene->camera.projectionMatrix();
        // std::cout << projMat[0][0] << ' ' << projMat[0][1] << ' ' << projMat[0][2] << ' ' << projMat[0][3] << ' '<<'\n'
        //           << projMat[1][0] << ' ' << projMat[1][1] << ' ' << projMat[1][2] << ' ' << projMat[1][3] << ' '<<'\n'
        //           << projMat[2][0] << ' ' << projMat[2][1] << ' ' << projMat[2][2] << ' ' << projMat[2][3] << ' '<<'\n'
        //           << projMat[3][0] << ' ' << projMat[3][1] << ' ' << projMat[3][2] << ' ' << projMat[3][3] << ' '<<'\n'<<endl;

        // mat4 viewProjectionMatrix = scene->camera.viewProjectionMatrix();
        // vec4 transformedPoint = viewProjectionMatrix * point;
        // vec4 transformedPoint2 = viewProjectionMatrix * point2;
        // cout << transformedPoint.x << ' ' << transformedPoint.y << ' ' << transformedPoint.z << ' ' << transformedPoint.w <<endl;
        // int x = (int) (transformedPoint.x/transformedPoint.w * width / 2 + width / 2);
        // int y = (int) (transformedPoint.y/transformedPoint.w * height / 2 + height / 2);
        // int x2 = (int) (transformedPoint2.x/transformedPoint2.w * width / 2 + width / 2);
        // int y2 = (int) (transformedPoint2.y/transformedPoint2.w * height / 2 + height / 2);
        // cout << x << ' ' << y << endl;
        //
        // if(x >= 0 && x < width && y >= 0 && y < height && transformedPoint.z >= 0) {
        //     PutPixelSDL(screen, x, y, vec3(1.0f));
        // }
        // if(x2 >= 0 && x2 < width && y2 >= 0 && y2 < height && transformedPoint.z >= 0) {
        //     PutPixelSDL(screen, x2, y2, vec3(1.0f));
        // }

        Line line = Line({.5, 0.2, 1, 1}, {-.5, 0, 1, 1});
        // vec4 point(-.5, .2, -1, 1);

        mat4 viewProjectionMatrix = scene->camera.viewProjectionMatrix();
        ProjectedLine projLine = line.projectLine(viewProjectionMatrix);

        int x1 = (int) (projLine.ends[0].x / projLine.ends[0].w * width / 2 + width / 2);
        int y1 = (int) (projLine.ends[0].y / projLine.ends[0].w * height / 2 + height / 2);
        int x2 = (int) (projLine.ends[1].x / projLine.ends[1].w * width / 2 + width / 2);
        int y2 = (int) (projLine.ends[1].y / projLine.ends[1].w * height / 2 + height / 2);


        std::cout << x1 << ' ' << y1 << ' ' << '\n';
        std::cout << x2 << ' ' << y2 << ' ' << '\n';


        // if (projLine.ends[0].z > 0 && projLine.ends[1].z > 0) {
        drawLine(screen, x1, y1, x2, y2);
        // }

        // if(x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) {
        //     PutPixelSDL(screen, x1, y1, vec3(1.0f));
        // }
        //
        // if(x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) {
        //     PutPixelSDL(screen, x2, y2, vec3(1.0f));
        // }


    }


    void clipLine(ProjectedLine line) {

    }


/**
 * Bresenham's line algorithm
 * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 */
    void drawLine(screen *screen, int x1, int y1, int x2, int y2) {

        int dx = x2 - x1;
        int dy = y2 - y1;

        // in the commentaries next, i'll assume that the (0,0) point of the screen
        // is at the top left. Horizontal axis x aims to the right.
        // Vertical axis y aims to the bottom.
        // if reality is not like this the code will work perfectly good (100% reversible).
        // it's just to describe what each block does.

        if (dy < 0) {
            int tmp = x2;
            x2 = x1;
            x1 = tmp;
            tmp = y2;
            y2 = x1;
            y1 = tmp;
            dx = x2 - x1;
            dy = y2 - y1;
        }

        // now dy >= 0 => every line is going down


        if (dx < 0) {
            if (dy > 0) {
                if (-dx >= dy) {
                    // line to the bottom left, close of horizontal
                    int e = dx;
                    dx *= 2;
                    dy *= 2;
                    for (x1; x1 >= x2; x1--) {
                        PutPixelSDL(screen, x1, y1, vec3(1.0f));
                        e += dy;
                        if (e >= 0) {
                            y1++;
                            e += dx;
                        }
                    }

                } else {
                    // line to the bottom left, close of vertical
                    int e = dy;
                    dx *= 2;
                    dy *= 2;
                    for (y1; y1 <= y2; y1++) {
                        PutPixelSDL(screen, x1, y1, vec3(1.0f));
                        e += dx;
                        if (e <= 0) {
                            x1--;
                            e += dy;
                        }
                    }
                }
            } else if (dy == 0) {
                //horizontal line
                for (x1; x1 >= x2; x1--) {
                    PutPixelSDL(screen, x1, y1, vec3(1.0f));
                }
            }
        } else if (dx > 0) {
            if (dy > 0) {
                if (dx >= dy) {
                    // line to the bottom right, close of horizontal
                    int e = dx;
                    dx *= 2;
                    dy *= 2;
                    for (x1; x1 <= x2; x1++) {
                        PutPixelSDL(screen, x1, y1, vec3(1.0f));
                        e = e - dy;
                        if (e < 0) {
                            y1++;
                            e += dx;
                        }
                    }
                } else {
                    // line to the bottom right, close of vertical
                    int e = dy;
                    dx *= 2;
                    dy *= 2;
                    for (y1; y1 <= y2; y1++) {
                        PutPixelSDL(screen, x1, y1, vec3(1.0f));
                        e = e - dx;
                        if (e < 0) {
                            x1++;
                            e += dy;
                        }
                    }
                }
            } else if (dy == 0) {
                // horizontal line
                for (x1; x1 <= x2; x1++) {
                    PutPixelSDL(screen, x1, y1, vec3(1.0f));
                }
            }
        } else if (dx == 0) {
            // vertical line
            for (y1; y1 <= y2; y1++) {
                PutPixelSDL(screen, x1, y1, vec3(1.0f));
            }
        }
    }

    void clipLine3D(const Line &line, Line &result) {

        int outcode1 = computeOutcode3D(line.ends[0], vec4(-1,-1,-1,1), vec4(1,1,1,1));
        int outcode2 = computeOutcode3D(line.ends[1], vec4(-1,-1,-1,1), vec4(1,1,1,1));

        while(true){
            // both end points are inside the region.
            if((outcode1 | outcode2) == INSIDEMASK) {
                break;
            }
        }
    }

    int computeOutcode3D(vec4 point, vec4 min, vec4 max) {
        int outcode = INSIDEMASK;

        if(point.x < min.x) {
            outcode |= LEFTMASK;
        } else if(point.x > max.x) {
            outcode |= RIGHTMASK;
        }

        if(point.y < min.y) {
            outcode |= BOTTOMMASK;
        } else if(point.y > max.y) {
            outcode |= TOPMASK;
        }

        if(point.z < min.z) {
            outcode |= FRONTMASK;
        } else if(point.z > max.z) {
            outcode |= BACKMASK;
        }

        return outcode;
    }
}
