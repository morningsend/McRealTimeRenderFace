//
// Created by Zaiyang Li on 26/02/2018.
//

#include "DeferredRenderingPipeline.hpp"

namespace McRenderer {

    void DeferredRenderingPipeline::submitScene(Scene &scene) {
        geometryPass(scene);
        lightingPass(scene);
        ambientOcclusionPass();
        compositionPass();
    }

    void DeferredRenderingPipeline::initializeShaderEnvironment(Scene &scene, ShaderEnvironment &env) {
        env.projectionMatrix = scene.camera.projectionMatrix();
        env.viewingMatrix = scene.camera.viewingMatrix();
        env.viewProjectionMatrix = env.projectionMatrix * env.viewingMatrix;
        env.normalMatrix = glm::inverse(glm::transpose(env.viewingMatrix));
        if(!scene.lights.empty()) {
            env.light1 = scene.lights[0];
            env.light1.position = env.viewingMatrix * env.light1.position;
        }
        env.cameraPosition = vec4(scene.camera.position, 1);
        env.shaderPassDebugging = debuggingPass;
    }

    void DeferredRenderingPipeline::shadeTriangle(Triangle &tri, VertexShaderOutputParams *vertexOutput) {
        VertexShaderInputParams vertexInput[3];
        for(int i = 0; i < 3; i++) {
            vertexInput[i].position = tri.vertices[i];
            vertexInput[i].normal = tri.normal;
            vertexInput[i].tangent = tri.tangent;
            vertexInput[i].bitangent = tri.bitangent;
            vertexInput[i].colour = tri.colour;
            vertexInput[i].textCoord = tri.uvCoords[i];
            vertexShader->run(env, vertexInput[i], vertexOutput[i]);
        }
    }

    void DeferredRenderingPipeline::rasterizeTriangleFan(vector<VertexShaderOutputParams> &vertexOutput) {
        // rasterize and interpolate
        auto size = static_cast<const int>(vertexOutput.size());
        vec4 last = vertexOutput[size - 1].position;
        vec4 current;
        switch(rasterizerConfig.faceMode) {
            case FaceRenderMode::Vertex:
                for(int i = 0; i < size; i++) {
                    rasterizePoint(vertexOutput[i].position);
                }
                break;
            case FaceRenderMode::Shaded:
                for(int i = 1; i < size - 1; i++) {
                    rasterizeTriangle(vertexOutput[0], vertexOutput[i], vertexOutput[i+1]);
                }
                break;
            case FaceRenderMode::Edge:
                for (int i = 0; i < size; i++) {
                    current = vertexOutput[i].position;
                    rasterizeLine(last, current);
                    last = current;
                }

                break;
        }
#if defined(GRAPHICS_DEBUG)
        /* visualize vertex normal vectors */
        for(int i = 0; i < size; i++) {
            rasterizePoint(vertexOutput[i].position);
            rasterizeLine(vertexOutput[i].position,
                          vertexOutput[i].position + vertexOutput[i].normal * 0.14f);
        }
#endif
    }
    void DeferredRenderingPipeline::rasterizeLine(vec4 p0, vec4 p1) {
        vec2 screen0 = convertToScreenCoordinate(p0);
        vec2 screen1 = convertToScreenCoordinate(p1);
        vec4 colour(0.97,0.2,0.3,1);
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
                outputFrameBuffer->setColour(i, y, colour);
            }
        } else {
            deltaY = 1/ deltaY;
            for(int y = y0; y != y1; y += yIncrement) {
                int x = static_cast<int>((y - y0)) * deltaX * deltaY + x0;
                outputFrameBuffer->setColour(x, y, colour);
            }
        }
    }
    vec2 DeferredRenderingPipeline::convertToScreenCoordinate(vec4 clippingCoordinate) {
        float width = rasterizerConfig.viewportWidth;
        float height = rasterizerConfig.viewportHeight;

        float x = (clippingCoordinate.x * 0.5f + 0.5f) * (width - 1.0f);
        float y = (clippingCoordinate.y * -0.5f + 0.5f) * (height - 1.0f);
        return vec2(x, y);
    }
    void DeferredRenderingPipeline::rasterizePoint(vec4 point) {
        vec2 screen = convertToScreenCoordinate(point);
        int x = static_cast<int>(lround(screen.x + 0.5f));
        int y = static_cast<int>(lround(screen.y + 0.5f));

        outputFrameBuffer->setColourAndDepthLessThan(x, y, vec4(1.0), point.z);
    }

    void DeferredRenderingPipeline::rasterizeHorizontalLine(VertexShaderOutputParams &v1,
                                                    VertexShaderOutputParams &v2) {
        vec2 screen1 = convertToScreenCoordinate(v1.position);
        vec2 screen2 = convertToScreenCoordinate(v2.position);
        VertexShaderOutputParams interpolatedAttributes;
        FragmentShaderOutput fragOutput;
        if(screen1.x < screen2.x) {
            float deltaX = screen2.x - screen1.x;
            int x = static_cast<int>(screen1.x);
            int y = static_cast<int>(screen1.y);
            for(int i = 0; i < static_cast<int>(deltaX); i++) {
                float t = (i) / deltaX;
                interpolate(v1, v2, t, interpolatedAttributes);
                float z = interpolatedAttributes.position.z * 0.5f + 0.5f;

                if(outputFrameBuffer->testDepthLessThan(x+i, y, z)) {
                    fragmentShader->run(
                            env,
                            interpolatedAttributes,
                            currentMaterial != nullptr ? *currentMaterial : defaultMaterial,
                            fragOutput
                    );
                    outputFrameBuffer->setColourAndDepth(x+i, y, fragOutput.colour, z);
                    geometryBuffers.diffuseAt(x + i, y) = fragOutput.diffuse;
                    geometryBuffers.specularAt(x + i, y) = fragOutput.specular;
                    geometryBuffers.depthAt(x + i, y)  = fragOutput.depth;
                    geometryBuffers.normalAt(x + i, y) = fragOutput.normal;
                    geometryBuffers.positionAt(x + i, y) = fragOutput.position;
                }
            }
        } else {
            float deltaX = screen1.x - screen2.x;
            int x = static_cast<int>(screen2.x);
            int y = static_cast<int>(screen2.y);
            for(int i = 0; i < static_cast<int>(deltaX); i++) {
                float t = (i) / deltaX;
                interpolate(v2, v1, t, interpolatedAttributes);
                float z = interpolatedAttributes.position.z * 0.5f + 0.5f;
                if(outputFrameBuffer->testDepthLessThan(x+i, y, z)) {
                    fragmentShader->run(env, interpolatedAttributes, *currentMaterial, fragOutput);
                    outputFrameBuffer->setColourAndDepth(x + i, y, fragOutput.colour, z);

                    geometryBuffers.diffuseAt(x + i, y) = fragOutput.diffuse;
                    geometryBuffers.specularAt(x + i, y) = fragOutput.specular;
                    geometryBuffers.depthAt(x + i, y)  = fragOutput.depth;
                    geometryBuffers.normalAt(x + i, y) = fragOutput.normal;
                    geometryBuffers.positionAt(x + i, y) = fragOutput.position;
                }
            }
        }
    }

    void DeferredRenderingPipeline::rasterizeTriangle(VertexShaderOutputParams& v1,
                                              VertexShaderOutputParams& v2,
                                              VertexShaderOutputParams& v3) {
        VertexShaderOutputParams* attributePointers[3] = {
                &v1,
                &v2,
                &v3,
        };
        VertexShaderOutputParams* temp;
        // sort vertices by y from large to small
        if (attributePointers[0]->position.y < attributePointers[1]->position.y) {
            temp = attributePointers[1];
            attributePointers[1] = attributePointers[0];
            attributePointers[0] = temp;
        }

        if(attributePointers[0]->position.y < attributePointers[2]->position.y) {
            temp = attributePointers[2];
            attributePointers[2] = attributePointers[1];
            attributePointers[1] = attributePointers[0];
            attributePointers[0] = temp;
        } else
        if(attributePointers[1]->position.y < attributePointers[2]->position.y) {
            temp = attributePointers[2];
            attributePointers[2] = attributePointers[1];
            attributePointers[1] = temp;
        }
        /*
        cout << "vertices by position.z"
            << attributePointers[0]->position.z << ' '
            << attributePointers[1]->position.z << ' '
            << attributePointers[2]->position.z
            << endl;
            */

        vec2 screenCoords[3];
        screenCoords[0] = convertToScreenCoordinate(attributePointers[0]->position);
        screenCoords[1] = convertToScreenCoordinate(attributePointers[1]->position);
        screenCoords[2] = convertToScreenCoordinate(attributePointers[2]->position);

        VertexShaderOutputParams leftAttributes;
        VertexShaderOutputParams rightAttributes;
        VertexShaderOutputParams leftDividerAttributes;

        float t = (screenCoords[1].y - screenCoords[0].y) / (screenCoords[2].y - screenCoords[0].y);
        interpolate(*attributePointers[0], *attributePointers[2], t, leftDividerAttributes);

        float dy = floor(screenCoords[1].y - screenCoords[0].y + 0.5f);
        for(int i = 0; i <= (int) dy; i++) {
            t = (i) / dy;
            interpolate(leftDividerAttributes, *attributePointers[0],  t, leftAttributes);
            interpolate(*attributePointers[1], *attributePointers[0],  t, rightAttributes);
            rasterizeHorizontalLine(leftAttributes, rightAttributes);
        }
        dy = floor(screenCoords[2].y - screenCoords[1].y + 0.5f);
        for(int i = 0; i < (int) dy; i++) {
            t = (i) / dy;
            interpolate(*attributePointers[2], leftDividerAttributes, t, leftAttributes);
            interpolate( *attributePointers[2], *attributePointers[1], t, rightAttributes);
            rasterizeHorizontalLine(leftAttributes, rightAttributes);
        }
    }

    void DeferredRenderingPipeline::ssaoPass(float *depthBuffer, vec4* colourBuffer) {
        const int width = outputFrameBuffer->getWidth();
        const int height = outputFrameBuffer->getHeight();
        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                int index = j + i * width;

            }
        }
    }

    void DeferredRenderingPipeline::geometryPass(Scene &scene) {
        scene.camera.initFrustumWorldSpace();
        initializeShaderEnvironment(scene, env);
        // this loop can be parallized.
        VertexShaderInputParams vertexInput[3];
        VertexShaderOutputParams vertexOutput[3];
        vector<VertexShaderOutputParams> vertexClippingBuffer;
        vertexClippingBuffer.reserve(6);

        outputFrameBuffer->clear();
        int edgeClippingFlags = 0;
        for(auto& tri: scene.model) {
            currentMaterial = scene.materials.empty() ? nullptr : scene.materials[0].get();
            float facing = glm::dot(scene.camera.position, vec3(tri.normal));
            float cullPoint = glm::dot(tri.normal, tri.vertices[0]);
            switch(vertexProcessingConfig.cullingMode) {
                case FaceCullingMode::BackFace:
                    if(facing <= cullPoint){
                        continue;
                    }
                    break;
                case FaceCullingMode::FrontFace:
                    if(facing > cullPoint) {
                        continue;
                    }
                    break;
                case FaceCullingMode::None:
                    break;
            }
            edgeClippingFlags = 0;
            vertexClippingBuffer.clear();
            Triangle copyTri = tri;
            shadeTriangle(copyTri, vertexOutput);
            preprocessor.clipTriangleHomogeneousCoords(
                    vertexOutput,
                    vertexClippingBuffer
            );
            if(vertexClippingBuffer.size() < 3) {
                continue;
            }
            for(int i = 0; i < vertexClippingBuffer.size(); i++) {
                float w = vertexClippingBuffer[i].position.w;
                vertexClippingBuffer[i].position /= w;
            }
            rasterizeTriangleFan(vertexClippingBuffer);
        }
#if defined(GRAPHICS_DEBUG)
        /* render position of light on screen as a dot */
        vec4 point = env.viewProjectionMatrix * scene.lights[0].position;
        point /= point.w;
        rasterizePoint(point);
#endif
    }

    void DeferredRenderingPipeline::lightingPass(Scene &scene) {
        for(Light& light: scene.lights) {

        }
    }

    void DeferredRenderingPipeline::compositionPass() {

    }

    void DeferredRenderingPipeline::ambientOcclusionPass() {

    }

    void DeferredRenderingPipeline::postProcessingAntiAliasing() {

    }

    void DeferredRenderingPipeline::postProcessingToneMapping() {

    }
}
