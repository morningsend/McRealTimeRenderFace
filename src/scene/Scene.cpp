//
// Created by Zaiyang Li on 31/01/2018.
//

#include "Scene.hpp"

void McRenderer::Scene::initialize() {
    Material* mat;
    for(MaterialSpec& spec : materialSpecs) {
        mat = new Material;
        buildMaterial(spec, *mat);
        materials.push_back(shared_ptr<Material>(mat));
    }
}
