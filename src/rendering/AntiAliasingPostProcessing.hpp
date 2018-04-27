//
// Created by Zaiyang Li on 09/04/2018.
//

#ifndef RENDERER_ANTIALIASINGFRAGMENTSHADER_HPP
#define RENDERER_ANTIALIASINGFRAGMENTSHADER_HPP

#include "FrameBuffer.hpp"

namespace McRenderer {
    class AntiAliasingPostProcessing {
    public:
        static inline float luminance(vec3& colour);
    };

}


#endif //RENDERER_ANTIALIASINGFRAGMENTSHADER_HPP
