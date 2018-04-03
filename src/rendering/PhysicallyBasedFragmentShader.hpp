//
// Created by Zaiyang Li on 02/04/2018.
//

#ifndef RENDERER_PHYSICALLYBASEDSHADER_HPP
#define RENDERER_PHYSICALLYBASEDSHADER_HPP
#include "FragmentShader.hpp"

namespace McRenderer {
    class PhysicallyBasedFragmentShader : public FragmentShader {
    public:
        ~PhysicallyBasedFragmentShader() = default;
        virtual void run(const ShaderEnvironment& env,
                         const VertexShaderOutputParams& vertexOutput,
                         const Material& material,
                         FragmentShaderOutput& output) override;
    };
}


#endif //RENDERER_PHYSICALLYBASEDSHADER_HPP
