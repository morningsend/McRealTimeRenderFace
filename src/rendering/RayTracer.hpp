//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_RAYTRACER_HPP
#define RENDERER_RAYTRACER_HPP


#include "../scene/Scene.hpp"
#include "RenderTarget.hpp"

namespace McRenderer {
    class RayTracer {
    private:
        int threads;

    public:
        void render(const Scene& scene, RenderTarget& target);
    };
}


#endif //RENDERER_RAYTRACER_HPP
