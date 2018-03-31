//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_SCENE_HPP
#define RENDERER_SCENE_HPP

#include <vector>
#include <memory>
#include "Light.hpp"
#include "Triangle.hpp"
#include "Camera.hpp"
#include "MaterialSpec.hpp"

namespace McRenderer {
    using namespace std;
    class Scene {
    public:
        vector <Light> lights{};
        vector <Triangle> model{};
        Camera camera{};
        vector <MaterialSpec> materialSpecs;
        vector <shared_ptr<Material>> materials;
        Scene() {}
        void initialize();
    };
}


#endif //RENDERER_SCENE_HPP
