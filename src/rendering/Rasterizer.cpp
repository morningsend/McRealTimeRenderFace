//
// Created by Zaiyang Li on 19/02/2018.
//

#include "Rasterizer.hpp"
#include "VertexShader.hpp"

using namespace glm;


void McRenderer::Rasterizer::renderToScreen(screen *screen, Scene& scene) {

    const int width = screen->width;
    const int height = screen->height;
    memset(screen->buffer, 0, sizeof(uint32_t) * width * height);


    Triangle triangle(vec4(-0.2f,0,-1,1), vec4(0,.2f,-1,1), vec4(0.2f,0,-1,1), vec4(0,0,1,0));

    mat4 projectionMatrix = scene.camera.projectionMatrix();
    mat4 viewingMatrix = scene.camera.viewingMatrix();

    for (size_t i = 0; i < 3; i++) {
      triangle.vertices[i] = viewingMatrix * triangle.vertices[i];
    }
    triangle.normal = viewingMatrix * triangle.normal;

    std::vector<Triangle> triangles;
    clipTriangle3D(scene.camera.frustum, triangle, triangles);

    for (size_t j = 0; j < triangles.size(); j++) {

    for(int i = 0; i < 3; i++) {
        triangles[j].vertices[i] = projectionMatrix * triangles[j].vertices[i];
        float w = triangles[j].vertices[i].w;
        triangles[j].vertices[i] /= w;
    }
    triangles[j].normal = projectionMatrix * triangles[j].normal;
    fillTriangle(triangles[j], screen);
  }
}



/**
 * Render a triangle using horizontal scan line algorithm
 * will discard back facing triangles if face render mode is FaceRenderMode::FrontOnly
 * @param triangle
 * @param screen
 */
void McRenderer::Rasterizer::fillTriangle(McRenderer::Triangle &triangle, screen *screen) {

    vec4* vertices = triangle.vertices;
    vec4 temp;
    // sort vertices by y from large to small
    if (vertices[0].y < vertices[1].y) {
        temp = vertices[1];
        vertices[1] = vertices[0];
        vertices[0] = temp;
    }

    if(vertices[0].y < vertices[2].y) {
        temp = vertices[2];
        vertices[2] = vertices[1];
        vertices[1] = vertices[0];
        vertices[0] = temp;
    } else
    if(vertices[1].y < vertices[2].y) {
        temp = vertices[2];
        vertices[2] = vertices[1];
        vertices[1] = temp;
    }

    vec2 screenCoords[3];
    screenCoords[0] = vec2((vertices[0].x + 1) * width * .5f  , (1 - vertices[0].y) * height * .5f);
    screenCoords[1] = vec2((vertices[1].x + 1) * width * .5f  , (1 - vertices[1].y) * height * .5f);
    screenCoords[2] = vec2((vertices[2].x + 1) * width * .5f  , (1 - vertices[2].y) * height * .5f);

    vec2 left = screenCoords[0];
    vec2 right = screenCoords[0];
    float t = (screenCoords[1].y - screenCoords[0].y) / (screenCoords[2].y - screenCoords[0].y);
    vec2 leftDivider = screenCoords[0] + (screenCoords[2] - screenCoords[0]) * t;

    float x1;
    float x2;
    float dx1 = leftDivider.x - left.x;
    float dx2 = screenCoords[1].x - right.x;
    float dy = screenCoords[1].y - screenCoords[0].y;
    float ystart = screenCoords[0].y;
    for(int i = (int) screenCoords[0].y; i <= (int) screenCoords[1].y; i++) {
        t = (i - ystart) / dy;
        x1 = left.x +  t * dx1;
        x2 = right.x + t * dx2;
        drawHorizontalLine(screen, vec3(1), (int) x1, (int) x2, i);
    }
    left = leftDivider;
    right = screenCoords[1];
    dx1 = screenCoords[2].x - left.x;
    dx2 = screenCoords[2].x - right.x;
    dy = (screenCoords[2].y - screenCoords[1].y);
    ystart = screenCoords[1].y;
    for(int i = (int) screenCoords[1].y; i < (int) screenCoords[2].y; i++) {
        t = (i - ystart) / dy;
        x1 = left.x +  t * dx1;
        x2 = right.x + t * dx2;
        drawHorizontalLine(screen, vec3(1), (int) x1, (int) x2, i);
    }
}


void McRenderer::Rasterizer::drawHorizontalLine(screen* screen, vec3 colour, int x1, int x2, int y) {
    int temp1 = x1 < x2 ? x1 : x2;
    int temp2 = x1 < x2 ? x2 : x1;
    x1 = temp1;
    x2 = temp2;

    int xmin = x1 < 0 ? 0 : x1;
    int xmax = x2 > width -1 ? width -1 : x2;

    if(y < 0 || y > height) {
        return;
    }

    for(int i = xmin; i <= xmax; i++) {
        PutPixelSDL(screen, i, y, colour);
    }
}
