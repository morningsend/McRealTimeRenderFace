//
// Created by Zaiyang Li on 09/04/2018.
//

#ifndef RENDERER_GEOMETRYPASSFRAGMENTSHADER_HPP
#define RENDERER_GEOMETRYPASSFRAGMENTSHADER_HPP


#include "FragmentShader.hpp"

namespace McRenderer {
    class GeometryPassFragmentShader : public FragmentShader {
    public:
        ~GeometryPassFragmentShader() = default;
        virtual void run(const ShaderEnvironment& env,
                         const VertexShaderOutputParams& vertexOutput,
                         const Material& material,
                         FragmentShaderOutput& output) override;
    };
}

#endif //RENDERER_GEOMETRYPASSFRAGMENTSHADER_HPP
