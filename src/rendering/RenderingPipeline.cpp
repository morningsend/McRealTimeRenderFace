//
// Created by Zaiyang Li on 26/02/2018.
//

#include "RenderingPipeline.hpp"

namespace McRenderer {

    void RenderingPipeline::submitScene(Scene &scene) {
        scene.camera.initFrustumWorldSpace();
        initializeShaderEnvironment(scene, env);
        // this loop can be parallized.
        vector<Triangle> triClippingbuffer;
        triClippingbuffer.reserve(4);
        VertexShaderInputParams vertexInput[3];
        VertexShaderOutputParams vertexOutput[3];
        vector<vec4> vertexClippingBuffer;
        vertexClippingBuffer.reserve(6);

        frameBuffer->clear();
        int edgeClippingFlags = 0;
        for(auto& tri: scene.model) {
            edgeClippingFlags = 0;
            vertexClippingBuffer.clear();
            Triangle copyTri = tri;
            shadeTriangle(copyTri, vertexOutput);
            preprocessor.clipTriangleUnitAABB(
                    vertexOutput[0].position,
                    vertexOutput[1].position,
                    vertexOutput[2].position,
                    edgeClippingFlags,
                    vertexClippingBuffer
            );
            std::cout << vertexClippingBuffer.size() << endl;
            if(vertexClippingBuffer.size() < 3) {
                continue;
            }
            // store a list of triangles into result.
            for(int i = 1; i < vertexClippingBuffer.size() - 1; i++) {
                rasterizeTriangle(Triangle(vertexClippingBuffer[0], vertexClippingBuffer[i], vertexClippingBuffer[i + 1], vertexOutput[0].normal));
            }
            // render triangle by interpolating vertex shapder output.
        }
    }

    void RenderingPipeline::initializeShaderEnvironment(Scene &scene, ShaderEnvironment &env) {
        env.projectionMatrix = scene.camera.projectionMatrix();
        env.viewingMatrix = scene.camera.viewingMatrix();
        env.viewProjectionMatrix = env.projectionMatrix * env.viewingMatrix;
        env.normalMatrix = glm::transpose(glm::inverse(env.viewingMatrix));
    }

    void RenderingPipeline::shadeTriangle(Triangle &tri, VertexShaderOutputParams *vertexOutput) {
        VertexShaderInputParams vertexInput[3];
        for(int i = 0; i < 3; i++) {
            vertexInput[i].position = tri.vertices[i];
            vertexInput[i].normal = tri.normal;
            vertexShader->run(env, vertexInput[i], vertexOutput[i]);
        }
    }

    void RenderingPipeline::rasterizeTriangle(Triangle triangle) {
        // rasterize and interpolate
        cout<<"rasterize triangle" << endl;
        for(int i = 0; i < 3; i++) {
            float w = triangle.vertices[i].w;
            triangle.vertices[i] /= w;
            // map Z from [-1, 1] to [1, 0]
            triangle.vertices[i].z = (triangle.vertices[i].z * -.5f) + 0.5f;
        }
        vec4 last = triangle.vertices[2];
        vec4 current;
        for(int i = 0; i < 3; i++) {
            current = triangle.vertices[i];
            rasterizeLine(last, current);
            last = current;
        }
    }

    void RenderingPipeline::rasterizeTriangle(VertexShaderOutputParams *vertexOutput, const int size) {
        VertexShaderOutputParams interpolatedVertexParams;
        // rasterize and interpolate
        cout<<"rasterize triangle" << endl;
        for(int i = 0; i < size; i++) {
            float w = vertexOutput[i].position.w;
            vertexOutput[i].position /= w;
            // map Z from [-1, 1] to [1, 0]
            vertexOutput[i].position.z = (vertexOutput[i].position.z * -.5f) + 0.5f;
        }
        vec4 last = vertexOutput[size - 1].position;
        vec4 current;
        for(int i = 0; i < size; i++) {
            current = vertexOutput[i].position;
            rasterizeLine(last, current);
            last = current;
        }
    }
    void RenderingPipeline::rasterizeLine(vec4 p0, vec4 p1) {
        vec2 screen0 = convertToScreenCoordinate(p0);
        vec2 screen1 = convertToScreenCoordinate(p1);

        float deltaX = screen1.x - screen0.x;
        float deltaY = screen1.y - screen0.y;
        int x0 = (int) screen0.x;
        int x1 = (int) screen1.x;
        int y0 = (int) screen0.y;
        int y1 = (int) screen1.y;
        int xIncrement = x0 > x1 ? -1 : 1;
        int yIncrement = y0 > y1 ? -1 : 1;
        if(abs(deltaX) > abs(deltaY)) {
            deltaX = 1 / deltaX;
            for(int i = x0; i != x1; i+=xIncrement) {
                int y = static_cast<int>((i - x0) * deltaY * deltaX) + y0;
                frameBuffer->setColour(i, y, vec4(1));
            }
        } else {
            deltaY = 1/ deltaY;
            for(int y = y0; y != y1; y += yIncrement) {
                int x = static_cast<int>((y - y0)) * deltaX * deltaY + x0;
                frameBuffer->setColour(x, y, vec4(1));
            }
        }
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
