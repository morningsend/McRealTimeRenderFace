//
// Created by Zaiyang Li on 26/02/2018.
//

#ifndef RENDERER_PRIMITIVEPREPROCESSOR_HPP
#define RENDERER_PRIMITIVEPREPROCESSOR_HPP
#include "../common.h"
#include "../scene/Triangle.hpp"
#include "../scene/Line.hpp"

#include "../scene/Plane.hpp"
#include "../scene/Camera.hpp"
#include "VertexShader.hpp"


namespace McRenderer {
    void clipTriangle3D(const Frustum& frutsum, const Triangle& triangle, vector<Triangle>& result);
    void clipPoint3D(const Frustum& frustum, const vec3 point);
    void clipLine(const Frustum& frustum, Line line);

    class PrimitivePreprocessor {
        std::vector<vec4> vertices;
        std::vector<vec4> verticesNext;
    public:
        PrimitivePreprocessor(): vertices{}, verticesNext{} {
            vertices.reserve(6);
            verticesNext.reserve(6);
        }
        void clipTriangle(const Frustum& frustum, Triangle &triangle, vector<Triangle> &result);

        // expect triangle attributes to be an array of three elements.
        void clipTriangleHomogeneousCoords(VertexShaderOutputParams triangleAttributes[3],
                                           vector<VertexShaderOutputParams>& result);
        void clipLine(const Frustum& frustom, Line &line);
        void clipPolygon(const Plane &plane, const vector<vec4> &vertices, vector<vec4> &result, const int size);

        static void interpolateTriangleAttributes(VertexShaderOutputParams triangleAttributes[3],
                                                  vector<vec4>& vertices,
                                                  vector<VertexShaderOutputParams>& result);
    };
}


#endif //RENDERER_PRIMITIVEPREPROCESSOR_HPP
