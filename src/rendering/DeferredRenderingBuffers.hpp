//
// Created by Zaiyang Li on 09/04/2018.
//

#ifndef RENDERER_GEOMETRYPASSBUFFERS_HPP
#define RENDERER_GEOMETRYPASSBUFFERS_HPP

#include <glm/glm.hpp>
#include <memory>

namespace McRenderer {
    class DeferredRenderingBuffers {
    private:
        void allocateMemory();
        std::unique_ptr<glm::vec4[]> diffuse{nullptr};
        std::unique_ptr<glm::vec4[]> specular{nullptr};
        std::unique_ptr<float[]> depth{nullptr};
        std::unique_ptr<glm::vec3[]> normal{nullptr};
        std::unique_ptr<glm::vec4[]> position{nullptr};
        std::unique_ptr<float[]> roughness{nullptr};
        std::unique_ptr<glm::vec3[]> lightAccumulation{nullptr};
        std::unique_ptr<float[]> ambientOcclusion{nullptr};
        std::unique_ptr<float[]> floatTempBuffer{nullptr};
        int width{0};
        int height{0};
    public:
        void resize(int newWdith, int newHeight);
        DeferredRenderingBuffers(int width, int height): width{width}, height{height} {
            allocateMemory();
        }
        DeferredRenderingBuffers(): DeferredRenderingBuffers(0,0) {

        }
        ~DeferredRenderingBuffers() = default;

        inline int getHeight() const { return height; }
        inline int getWidth() const { return width; }
        bool inRange(int x, int y) const {
            return x >= 0 && x < width && y >=0 && y < height;
        }
        float* getDepthBuffer() {
            return depth.get();
        }
        glm::vec4* getPositionBuffer() {
            return position.get();
        }
        inline float& depthAt(int x, int y) {
            return depth[y * width + x];
        }
        inline float& floatTempAt(int x, int y) {
            return floatTempBuffer[y * width + x];
        }
        inline glm::vec4& specularAt(int x, int y) {
            return specular[y * width + x];
        }
        inline glm::vec4& diffuseAt(int x, int y) {
            return diffuse[y * width + x];
        }
        inline glm::vec3& normalAt(int x, int y) {
            return normal[y * width + x];
        }

        inline glm::vec4& positionAt(int x, int y) {
            return position[y * width + x];
        }

        inline glm::vec3& lightAccumAt(int x, int y) {
            return lightAccumulation[y * width + x];
        }

        inline float& ambientOcclusionAt(int x, int y) {
            return ambientOcclusion[y * width + x];
        }
        inline float& roughnessAt(int x, int y) {
            return roughness[y * width + x];
        }
        inline void swapTempWithAmbientOcclusion() {
            ambientOcclusion.swap(floatTempBuffer);
        }
        inline void clearAll() {
            for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                    int index = i * width + j;
                    specular[index] =glm::vec4(0);
                    diffuse[index] = glm::vec4(0);
                    normal[index] = glm::vec3(0,0,1);
                    position[index] = glm::vec4(0,0,0,1);
                    depth[index] = 1.0f;
                    lightAccumulation[index] = glm::vec4(0);
                    ambientOcclusion[index] = 1.0f;
                }
            }
        }
        inline void clearDepth() {
            for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                    int index = i * width + j;
                    depth[index] = 1.0f;
                }
            }
        }

    };

}
#endif //RENDERER_GEOMETRYPASSBUFFERS_HPP
