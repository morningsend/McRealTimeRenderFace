//
// Created by Zaiyang Li on 26/02/2018.
//

#ifndef RENDERER_PRIMITIVEPREPROCESSOR_HPP
#define RENDERER_PRIMITIVEPREPROCESSOR_HPP
#include "../scene/Triangle.hpp"
#include "../scene/Line.hpp"

#include "../scene/Plane.hpp"
#include "../scene/Camera.hpp"

#include <glm/glm.hpp>

namespace McRenderer {
    void clipTriangle3D(const Frustum& frutsum, const Triangle& triangle, vector<Triangle>& result);
    class PrimitivePreprocessor {
    public:
        bool clipTriangle(const Frustum& frustum, Triangle &triangle, vector<Triangle> &result);
        bool clipLine(const Frustum& frustom, Line &line);
    };
}


#endif //RENDERER_PRIMITIVEPREPROCESSOR_HPP
