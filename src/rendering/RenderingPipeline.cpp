//
// Created by Zaiyang Li on 26/02/2018.
//

#include "RenderingPipeline.hpp"

namespace McRenderer {

    void RenderingPipeline::submitScene(Scene &scene) {
        initializeShaderEnvironment(scene, env);
        VertexShaderInputParams vertexInput;
        VertexShaderOutputParams vertexOutput;
        FragmentShaderOutput fragmentOutput;
        // this loop can be parallized.
        for(auto& tri: scene.model) {
            draw(tri);
        }
    }

    void RenderingPipeline::initializeShaderEnvironment(Scene &scene, ShaderEnvironment &env) {
        env.projectionMatrix = scene.camera.projectionMatrix();
        env.viewingMatrix = scene.camera.viewingMatrix();
    }

    void RenderingPipeline::draw(Triangle& tri) {

    }

    void RenderingPipeline::draw(Line& line) {

    }

    void RenderingPipeline::draw(vec4 point) {

    }
}