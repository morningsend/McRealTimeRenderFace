//
// Created by Zaiyang Li on 26/02/2018.
//

#include "RenderingPipeline.hpp"

namespace McRenderer {

    void RenderingPipeline::submitScene(Scene &scene) {
        initializeShaderEnvironment(scene, env);
        // this loop can be parallized.
        vector<Triangle> triClippingbuffer(4);
        VertexShaderInputParams vertexInput[3];
        VertexShaderOutputParams vertexOutput[3];
        for(auto& tri: scene.model) {
            triClippingbuffer.clear();
            Triangle copyTri = tri;
            for(int i = 0; i < 3; i++) {
                copyTri.vertices[i] = env.viewingMatrix * copyTri.vertices[i];
                copyTri.normal = env.viewingMatrix * copyTri.normal;
            }
            preprocessor.clipTriangle(scene.camera.frustum,copyTri, triClippingbuffer);
            for(auto& clipppedTri: triClippingbuffer) {
                shadeTriangle(clipppedTri, vertexOutput);
            }


        }
    }

    void RenderingPipeline::initializeShaderEnvironment(Scene &scene, ShaderEnvironment &env) {
        env.projectionMatrix = scene.camera.projectionMatrix();
        env.viewingMatrix = scene.camera.viewingMatrix();
    }

    void RenderingPipeline::shadeTriangle(Triangle &tri, VertexShaderOutputParams *vertexOutput) {
        VertexShaderInputParams vertexInput[3];
        for(int i = 0; i < 3; i++) {
            vertexInput[i].position = tri.vertices[i];
            vertexInput[i].normal = tri.normal;
            vertexShader->run(env, vertexInput[i], vertexOutput[i]);
        }
    }
    void RenderingPipeline::rasterizeTriangle(VertexShaderOutputParams *vertexOutput) {
        VertexShaderOutputParams interpolatedVertexParams;
        // rasterize and interpolate

        //rasterizer->drawTriangle();

    }
    void RenderingPipeline::draw(Line& line) {

    }

    void RenderingPipeline::draw(vec4 point) {

    }


}