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
        frameBuffer->clear();
        for(auto& tri: scene.model) {
            triClippingbuffer.clear();
            Triangle copyTri = tri;
            for(int i = 0; i < 3; i++) {
                copyTri.vertices[i] = env.viewingMatrix * copyTri.vertices[i];
                copyTri.normal = env.viewingMatrix * copyTri.normal;
            }
            preprocessor.clipTriangle(scene.camera.frustum, copyTri, triClippingbuffer);
            for(auto& clipppedTri: triClippingbuffer) {
                shadeTriangle(clipppedTri, vertexOutput);
                rasterizeTriangle(vertexOutput);
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
    void RenderingPipeline::rasterizeTriangle(VertexShaderOutputParams *vertexOutput, const int size) {
        VertexShaderOutputParams interpolatedVertexParams;
        // rasterize and interpolate
        cout<<"rasterize triangle" << endl;
        //rasterizer->drawTriangle();
        for(int i = 0; i < size; i++) {
            float w = vertexOutput[i].position.w;
            vertexOutput[i].position /= w;
            // map Z from [-1, 1] to [1, 0]
            vertexOutput[i].position.z = (vertexOutput[i].position.z * -.5f) + 0.5f;
            rasterizePoint(vertexOutput[i].position);
        }
    }
    void RenderingPipeline::rasterizeLine(Line &line) {

    }
    vec2 RenderingPipeline::convertToScreenCoordinate(vec4 clippingCoordinate) {
        float width = rasterizerConfig.viewportWidth;
        float height = rasterizerConfig.viewportHeight;

        float x = (clippingCoordinate.x * 0.5f + 0.5f) * (width - 1.0f);
        float y = (clippingCoordinate.y * -0.5f + 0.5f) * (height - 1.0f);
        return vec2(x, y);
    }
    void RenderingPipeline::rasterizePoint(vec4 point) {
        vec2 screen = convertToScreenCoordinate(point);
        int x = static_cast<int>(lround(screen.x + 0.5f));
        int y = static_cast<int>(lround(screen.y + 0.5f));

        frameBuffer->setColourAndDepthLessThan(x, y, vec4(1.0), point.z);
    }
}