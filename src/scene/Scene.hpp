//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_SCENE_HPP
#define RENDERER_SCENE_HPP

#include <vector>
#include "Light.hpp"
#include "Triangle.hpp"
#include "Camera.hpp"

namespace McRenderer {
    using namespace std;
    class Scene {
        vector <Light> lights;
        vector <Triangle> model;
        Camera camera;
    };
}


#endif //RENDERER_SCENE_HPP
