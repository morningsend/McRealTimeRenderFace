//
// Created by Zaiyang Li on 26/02/2018.
//

#ifndef RENDERER_PRIMITIVEPREPROCESSOR_HPP
#define RENDERER_PRIMITIVEPREPROCESSOR_HPP
#include "../scene/Triangle.hpp"
#include "../scene/Line.hpp"

namespace McRenderer {
    class PrimitivePreprocessor {
    public:
        bool clipTriangle(Triangle& triangle, vector<Triangle>& result);
        bool clipLine(Line& line);
    };
}


#endif //RENDERER_PRIMITIVEPREPROCESSOR_HPP
