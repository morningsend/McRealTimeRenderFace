//
// Created by Zaiyang Li on 26/02/2018.
//

#ifndef RENDERER_PIPELINE_HPP
#define RENDERER_PIPELINE_HPP

#include <memory>
#include "FragmentShader.hpp"
#include "VertexShader.hpp"
#include "Rasterizer.hpp"
#include "PrimitivePreprocessor.hpp"
#include "FrameBuffer.hpp"

namespace McRenderer {
    class RenderingPipeline;

    struct RenderingPipelineConfig {
        int threadCount {1};
    };

    class RenderingPipeline {
    private:
        std::unique_ptr<FragmentShader> fragmentShader;
        std::unique_ptr<VertexShader> vertexShader;
        std::unique_ptr<FrameBuffer> frameBuffer;
        std::unique_ptr<Rasterizer> rasterizer;
        PrimitivePreprocessor preprocessor;
        RenderingPipelineConfig pipelineConfig;


        // variables used in shader computations;
        // should be treated as a constant inside a shader.
        ShaderEnvironment env;

        void shadeTriangle(Triangle &tri, VertexShaderOutputParams *vertexOutput);
        void rasterizeTriangle(VertexShaderOutputParams *vertexOutput);
        void draw(Line& line);
        void draw(vec4 point);
        /**
         * In initialize, we can allocate memory or create threads.
         */
        void initialize() {

        };
        // helper methods.
        void initializeShaderEnvironment(Scene &scene, ShaderEnvironment &env);
    public:
        RenderingPipeline(std::unique_ptr<VertexShader>& vertexShader,
                          std::unique_ptr<FragmentShader>& fragmentShader,
                          std::unique_ptr<FrameBuffer>& frameBuffer,
                          RenderingPipelineConfig pipelineConfig,
                          RasterizerConfig rasterizerConfig)
                : vertexShader(std::move(vertexShader)),
                  fragmentShader(std::move(fragmentShader)),
                  frameBuffer(std::move(frameBuffer)),
                  pipelineConfig{pipelineConfig},
                  rasterizer(new Rasterizer(rasterizerConfig))
        {
            initialize();
        }

        ~RenderingPipeline() = default;


        /**
         * Submit scene will invoke the pipeline to render one frame of the scene.
         * @param scene
         */
        void submitScene(Scene& scene);

        FrameBuffer& getFrameBuffer() const {
            return *frameBuffer;
        }

    };

    class PipelineBuilder {
    private:
        std::unique_ptr<FragmentShader> fragmentShader;
        std::unique_ptr<VertexShader> vertexShader;
        std::unique_ptr<FrameBuffer> frameBuffer;
        RasterizerConfig rasterizerConfig {};
        RenderingPipelineConfig pipelineConfig;
    public:

        PipelineBuilder() {}
        PipelineBuilder& singlethreaded() {
            pipelineConfig.threadCount = 1;
            return *this;
        }
        PipelineBuilder& multithreaded(int n) {
            n = n < 1 ? 1 : n;
            n = n > 8 ? 8 : n;
            pipelineConfig.threadCount = n;
            return *this;
        }
        PipelineBuilder& useVertexShader(VertexShader* shader) {
            vertexShader.reset(shader);
            return *this;
        }

        PipelineBuilder& useFragmentShader(FragmentShader* shader) {
            fragmentShader.reset(shader);
            return *this;
        }
        PipelineBuilder& configureRasterizer(RasterizerConfig config) {
            rasterizerConfig = config;
            return *this;
        }

        PipelineBuilder& writeOutputTo(FrameBuffer* target) {
            frameBuffer.reset(target);
            return *this;
        }

        std::unique_ptr<RenderingPipeline> build(){
            return std::move(std::unique_ptr<RenderingPipeline>(new RenderingPipeline(
                    vertexShader,
                    fragmentShader,
                    frameBuffer,
                    pipelineConfig,
                    RasterizerConfig{}
            )));
        }
    };
}


#endif //RENDERER_PIPELINE_HPP
