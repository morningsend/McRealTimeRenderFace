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
    void clipPoint3D(const Frustum& frustum, const vec3 point);
    void clipLine(const Frustum& frustum, Line line);

    class PrimitivePreprocessor {
    public:
        void clipTriangle(const Frustum& frustum, Triangle &triangle, vector<Triangle> &result);
        void clipTriangleUnitAABB(vec4 v0, vec4 v1, vec4 v2, int& edgeClippingFlags, vector<vec4>& result);
        void clipLine(const Frustum& frustom, Line &line);
        void clipPolygon(const Plane &plane, const vector<vec4> &vertices, vector<vec4> &result, const int size);
    };
}


#endif //RENDERER_PRIMITIVEPREPROCESSOR_HPP
