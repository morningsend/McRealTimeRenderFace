//
// Created by Zaiyang Li on 11/04/2018.
//

#ifndef RENDERER_RASTERIZERCONFIG_HPP
#define RENDERER_RASTERIZERCONFIG_HPP

enum FaceRenderMode{
    Vertex, Shaded, Edge
};
struct RasterizerConfig {
    int viewportHeight{1};
    int viewportWidth{1};
    FaceRenderMode faceMode{};
};
#endif //RENDERER_RASTERIZERCONFIG_HPP
