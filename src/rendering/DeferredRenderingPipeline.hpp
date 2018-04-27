//
// Created by Zaiyang Li on 26/02/2018.
//

#ifndef RENDERER_PIPELINE_HPP
#define RENDERER_PIPELINE_HPP

#include "../common.h"
#include "FragmentShader.hpp"
#include "VertexShader.hpp"
#include "PrimitivePreprocessor.hpp"
#include "FrameBuffer.hpp"
#include "DeferredRenderingBuffers.hpp"
#include "RasterizerConfig.hpp"
#include "../scene/Scene.hpp"
#include "AOFragmentShader.hpp"
#include "LightingPassFragmentShader.hpp"
#include "AntiAliasingPostProcessing.hpp"

namespace McRenderer {
    class DeferredRenderingPipeline;
    enum class FaceCullingMode {
        None,
        BackFace,
        FrontFace,
    };
    struct RenderingPipelineConfig {
        int threadCount {1};
    };
    struct VertexProcessingConfig {
        FaceCullingMode cullingMode {FaceCullingMode::None};

    };

    class DeferredRenderingPipeline {
    private:
        std::unique_ptr<FragmentShader> fragmentShader;
        std::unique_ptr<VertexShader> vertexShader;
        std::unique_ptr<FrameBuffer> outputFrameBuffer;
        PrimitivePreprocessor preprocessor;
        RenderingPipelineConfig pipelineConfig;
        RasterizerConfig rasterizerConfig;
        VertexProcessingConfig vertexProcessingConfig;
        // variables used in shader computations;
        // should be treated as a constant inside a shader.
        ShaderEnvironment env;
        Material* currentMaterial;
        Material defaultMaterial;
        ShaderPass debuggingPass{ShaderPass::All};
        DeferredRenderingBuffers geometryBuffers{0,0};
        AOFragmentShader aoShader{.5f, 0.01f, 16};
        AntiAliasingPostProcessing fxaaPostProcessing;
        void shadeTriangle(Triangle &tri, VertexShaderOutputParams *vertexOutput);
        void rasterizeTriangleFan(vector<VertexShaderOutputParams> &clippedVertices);
        void rasterizeLine(vec4 p0, vec4 p1);
        void rasterizeHorizontalLine(VertexShaderOutputParams& v1,
                                     VertexShaderOutputParams& v2);
        void rasterizeTriangle(VertexShaderOutputParams& v1,
                               VertexShaderOutputParams& v2,
                               VertexShaderOutputParams& v3);
        void rasterizePoint(vec4 point);

        // converts a vec4:(x,y,z,1) after perspective division to screen coordinate
        // where x: (0, width) and y(0, height)
        vec2 convertToScreenCoordinate(vec4 clippingCoordinate);

        /**
         * In initialize, we can allocate memory or create threads.
         */
        void initialize() {
            geometryBuffers
                    .resize(
                            rasterizerConfig.viewportWidth,
                            rasterizerConfig.viewportHeight
                    );
            aoShader.generateKernelAndNoise();
        };
        // helper methods.
        void initializeShaderEnvironment(Scene &scene, ShaderEnvironment &env);
        void ssaoPass(float *depthBuffer, vec4* colourBuffer);
        void lightingPass(Scene& scene);
        void geometryPass(Scene& scene);
        void ambientOcclusionPass();
        void postProcessingPass();
        void postProcessingAntiAliasing();
        void ambientOcclusionApplyBoxBlur();
        static inline vec3 hdrFilmicToneMap(vec3 colour, float whitePoint);
    public:
        DeferredRenderingPipeline(std::unique_ptr<VertexShader>& vertexShader,
                          std::unique_ptr<FragmentShader>& fragmentShader,
                          std::unique_ptr<FrameBuffer>& frameBuffer,
                          RenderingPipelineConfig pipelineConfig,
                          RasterizerConfig rasterizerConfig)
                : vertexShader(std::move(vertexShader)),
                  fragmentShader(std::move(fragmentShader)),
                  outputFrameBuffer(std::move(frameBuffer)),
                  pipelineConfig{pipelineConfig},
                  rasterizerConfig{rasterizerConfig}
        {
            initialize();
        }

        ~DeferredRenderingPipeline() = default;

        /**
         * Submit scene will invoke the pipeline to render one frame of the scene.
         * @param scene
         */
        void submitScene(Scene& scene);
        FrameBuffer& getOutputFrameBuffer() const {
            return *outputFrameBuffer;
        }
        void setDebuggingPass(ShaderPass pass) {
            debuggingPass = pass;
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

        std::unique_ptr<DeferredRenderingPipeline> build(){
            return std::move(std::unique_ptr<DeferredRenderingPipeline>(new DeferredRenderingPipeline(
                    vertexShader,
                    fragmentShader,
                    frameBuffer,
                    pipelineConfig,
                    rasterizerConfig
            )));
        }
    };
}


#endif //RENDERER_PIPELINE_HPP
