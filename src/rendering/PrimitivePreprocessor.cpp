//
// Created by Zaiyang Li on 26/02/2018.
//

#include "PrimitivePreprocessor.hpp"

namespace McRenderer {

#define EPSILON 0.00001f
#define INSIDE 0
#define OUTSIDE 1

    void PrimitivePreprocessor::clipPolygon(const Plane &plane,
                                            const vector<vec4> &vertices,
                                            vector<vec4> &result,
                                            const int size) {

        // bit flag for vertices clipped status
        // bit 1 == vertex clipped
        // bit 0 == vertex not clipped
        char flags[size];
        Line edges[size]; // edges[i] = (vi, vi+1 % size)

        for (int i = 0; i < size; i++) {
            flags[i] = 0;
            const vec4 &v1 = vertices[i];
            const vec4 &v2 = vertices[(i + 1) % size];
            float distance1 = -glm::dot(v1, plane.normal) + plane.distance;
            float distance2 = -glm::dot(v2, plane.normal) + plane.distance;

            flags[i] |= distance1 > 0 ? 0 : 1;
            flags[i] |= distance2 > 0 ? 0 : 1 << 1;

            if (flags[i] == 0) {
                edges[i] = Line{v1, v2};
            } else if (flags[i] < 3) {
                // first verte/* code *//* code *//* code */ is outside, find intersection against plane.
                vec4 direction = v2 - v1;
                float t = (distance1) / (glm::dot(direction, plane.normal));
                vec4 vNew = v1 + direction * t;

                if (flags[i] == 1) {
                    edges[i] = Line {vNew, v2};
                } else {

                    edges[i] = Line{v1, vNew};
                }

            } else if (flags[i] == 3) {
                //reject
            }
        }
        for (int i = 0; i < size; i++) {

            if (flags[i] == 3) {
                continue;
            } else {
                char nextFlag = flags[(i + 1) % size];
                result.push_back(edges[i].ends[0]);
                if (flags[i] >> 1 == 1) {
                    result.push_back(edges[i].ends[1]);
                } else if ((nextFlag & 1) != (flags[i] >> 1)) {
                    result.push_back(edges[i].ends[1]);
                }
            }
        }
    }

    void PrimitivePreprocessor::clipTriangle(const Frustum &frustum, Triangle &triangle, vector<Triangle> &result) {
        // algorithm:
        // store list of vertices in an array in the anti-clockwise order.
        // for each plane:
        //      create a list of edges (vi, vi+1) and list of flags:(clipped_1, clipped_2)
        //      for each edge:
        //          clip edge against plane and write vertex clip flag to flags
        //      gather edge clipping results
        //

        std::vector<vec4> vertices;
        std::vector<vec4> verticesNext;

        vertices.reserve(6);
        verticesNext.reserve(6);
        vertices.push_back(triangle.vertices[0]);
        vertices.push_back(triangle.vertices[1]);
        vertices.push_back(triangle.vertices[2]);

        float dist = 0.0f;
        bool accept = false;
        bool clipped = false;
        // clip against all planes in turn.
        for (int i = 0; i < 6; i++) {
            const Plane &p = frustum.sides[i];
            verticesNext.clear();
            clipPolygon(p, vertices, verticesNext, static_cast<const int>(vertices.size()));
            vertices.swap(verticesNext);
            //cout<<"clipped size:" << vertices.size() << endl;
        }

        if (vertices.size() < 3) {
            return;
        }
        // store a list of triangles into result.
        for (int i = 1; i < vertices.size() - 1; i++) {
            result.push_back(Triangle(vertices[0], vertices[i], vertices[i + 1], triangle.normal));
        }
    }

    void PrimitivePreprocessor::clipLine(const Frustum &frustom, Line &line) {

    }

    void PrimitivePreprocessor::clipTriangleHomogeneousCoords(VertexShaderOutputParams triangleAttributes[3],
                                                              vector<VertexShaderOutputParams> &result) {
        // bit flag for vertices clipped status
        // bit 1 == vertex clipped
        // bit 0 == vertex not clipped

        int flags;
        verticesNext.clear();
        vertices.clear();
        vertices.push_back(triangleAttributes[0].position);
        vertices.push_back(triangleAttributes[1].position);
        vertices.push_back(triangleAttributes[2].position);

        vec4 vNew;
        float t = 0.0f;

        // x + w = 0
        for (size_t i = 0; i < vertices.size(); i++) {
            flags = 0;
            const vec4 &v1 = vertices[i];
            const vec4 &v2 = vertices[(i + 1) % vertices.size()];

            flags |= v1.x >= -v1.w ? 0 : 1;
            flags |= (v2.x >= -v2.w ? 0 : 1) << 1;

            switch (flags) {
                // if both vertices are inside, add the second vertex into output list.
                case 0:
                    verticesNext.push_back(v2);
                    break;
                    // find intersection if one of vertices are outside.
                case 1:
                case 2:

                    //vNew.y = v1.y + (v2.y - v1.y) / (v2.x - v1.x) * (-1 - v1.x);
                    //vNew.z = v1.z + (v2.z - v1.z) / (v2.x - v1.x) * (-1 - v1.x);
                    t = (v1.x + v1.w) / ((v1.x + v1.w) - (v2.x + v2.w));
                    vNew = v1 * (1 - t) + t * v2;
                    verticesNext.push_back(vNew);
                    if (flags == 1) {
                        verticesNext.push_back(v2);
                        // both are outside.
                    }
                case 3:
                    break;
                default:
                    break;
            }
        }

        vertices.swap(verticesNext);
        verticesNext.clear();
        // x - w = 0

        for (size_t i = 0; i < vertices.size(); i++) {
            flags = 0;
            const vec4 &v1 = vertices[i];
            const vec4 &v2 = vertices[(i + 1) % vertices.size()];

            flags |= v1.x <= v1.w ? 0 : 1;
            flags |= (v2.x <= v2.w ? 0 : 1) << 1;

            switch (flags) {
                // if both vertices are inside, add the second vertex into output list.
                case 0:
                    verticesNext.push_back(v2);
                    break;
                    // find intersection if one of vertices are outside.
                case 1:
                case 2:

                    //vNew.y = v1.y + (v2.y - v1.y) / (v2.x - v1.x) * (-1 - v1.x);
                    //vNew.z = v1.z + (v2.z - v1.z) / (v2.x - v1.x) * (-1 - v1.x);
                    t = (v1.w - v1.x) / ((v1.w - v1.x) - (v2.w - v2.x));
                    vNew = v1 * (1 - t) + t * v2;
                    verticesNext.push_back(vNew);
                    if (flags == 1) {
                        verticesNext.push_back(v2);
                        // both are outside.
                    }
                case 3:
                    break;
                default:
                    break;
            }
        }

        vertices.swap(verticesNext);
        verticesNext.clear();


        // y + w = 0
        for (size_t i = 0; i < vertices.size(); i++) {
            flags = 0;
            const vec4 &v1 = vertices[i];
            const vec4 &v2 = vertices[(i + 1) % vertices.size()];

            flags |= v1.y >= -v1.w ? 0 : 1;
            flags |= (v2.y >= -v2.w ? 0 : 1) << 1;

            switch (flags) {
                // if both vertices are inside, add the second vertex into output list.
                case 0:
                    verticesNext.push_back(v2);
                    break;
                    // find intersection if one of vertices are outside.
                case 1:
                case 2:

                    //vNew.y = v1.y + (v2.y - v1.y) / (v2.x - v1.x) * (-1 - v1.x);
                    //vNew.z = v1.z + (v2.z - v1.z) / (v2.x - v1.x) * (-1 - v1.x);
                    t = (v1.y + v1.w) / ((v1.y + v1.w) - (v2.y + v2.w));
                    vNew = v1 * (1 - t) + t * v2;
                    verticesNext.push_back(vNew);
                    if (flags == 1) {
                        verticesNext.push_back(v2);
                        // both are outside.
                    }
                case 3:
                    break;
                default:
                    break;
            }
        }

        vertices.swap(verticesNext);
        verticesNext.clear();
        // y - w = 0

        for (size_t i = 0; i < vertices.size(); i++) {
            flags = 0;
            const vec4 &v1 = vertices[i];
            const vec4 &v2 = vertices[(i + 1) % vertices.size()];

            flags |= v1.y <= v1.w ? 0 : 1;
            flags |= (v2.y <= v2.w ? 0 : 1) << 1;

            switch (flags) {
                // if both vertices are inside, add the second vertex into output list.
                case 0:
                    verticesNext.push_back(v2);
                    break;
                    // find intersection if one of vertices are outside.
                case 1:
                case 2:

                    //vNew.y = v1.y + (v2.y - v1.y) / (v2.x - v1.x) * (-1 - v1.x);
                    //vNew.z = v1.z + (v2.z - v1.z) / (v2.x - v1.x) * (-1 - v1.x);
                    t = (v1.w - v1.y) / ((v1.w - v1.y) - (v2.w - v2.y));
                    vNew = v1 * (1 - t) + t * v2;
                    verticesNext.push_back(vNew);
                    if (flags == 1) {
                        verticesNext.push_back(v2);
                        // both are outside.
                    }
                case 3:
                    break;
                default:
                    break;
            }
        }

        vertices.swap(verticesNext);
        verticesNext.clear();


        // y + w = 0
        for (size_t i = 0; i < vertices.size(); i++) {
            flags = 0;
            const vec4 &v1 = vertices[i];
            const vec4 &v2 = vertices[(i + 1) % vertices.size()];

            flags |= v1.z >= -v1.w ? 0 : 1;
            flags |= (v2.z >= -v2.w ? 0 : 1) << 1;

            switch (flags) {
                // if both vertices are inside, add the second vertex into output list.
                case 0:
                    verticesNext.push_back(v2);
                    break;
                    // find intersection if one of vertices are outside.
                case 1:
                case 2:

                    //vNew.y = v1.y + (v2.y - v1.y) / (v2.x - v1.x) * (-1 - v1.x);
                    //vNew.z = v1.z + (v2.z - v1.z) / (v2.x - v1.x) * (-1 - v1.x);
                    t = (v1.z + v1.w) / ((v1.z + v1.w) - (v2.z + v2.w));
                    vNew = v1 * (1 - t) + t * v2;
                    verticesNext.push_back(vNew);
                    if (flags == 1) {
                        verticesNext.push_back(v2);
                        // both are outside.
                    }
                case 3:
                    break;
                default:
                    break;
            }
        }

        vertices.swap(verticesNext);
        verticesNext.clear();

        // z - w = 0

        for (size_t i = 0; i < vertices.size(); i++) {
            flags = 0;
            const vec4 &v1 = vertices[i];
            const vec4 &v2 = vertices[(i + 1) % vertices.size()];

            flags |= v1.z <= v1.w ? 0 : 1;
            flags |= (v2.z <= v2.w ? 0 : 1) << 1;

            switch (flags) {
                // if both vertices are inside, add the second vertex into output list.
                case 0:
                    verticesNext.push_back(v2);
                    break;
                    // find intersection if one of vertices are outside.
                case 1:
                case 2:

                    //vNew.y = v1.y + (v2.y - v1.y) / (v2.x - v1.x) * (-1 - v1.x);
                    //vNew.z = v1.z + (v2.z - v1.z) / (v2.x - v1.x) * (-1 - v1.x);
                    t = (v1.w - v1.z) / ((v1.w - v1.z) - (v2.w - v2.z));
                    vNew = v1 * (1 - t) + t * v2;
                    verticesNext.push_back(vNew);
                    if (flags == 1) {
                        verticesNext.push_back(v2);
                        // both are outside.
                    }
                case 3:
                    break;
                default:
                    break;
            }
        }

        vertices.swap(verticesNext);
        verticesNext.clear();
        if (vertices.size() < 3) {
            return;
        }
        interpolateTriangleAttributes(triangleAttributes, vertices, result);
    }

    void PrimitivePreprocessor::interpolateTriangleAttributes(VertexShaderOutputParams *triangleAttributes,
                                                              vector<vec4> &vertices,
                                                              vector<VertexShaderOutputParams> &result) {
        // Barycentric coordinates.
        vec4 v0 = triangleAttributes[0].position;
        vec4 v1 = triangleAttributes[1].position;
        vec4 v2 = triangleAttributes[2].position;
        vec3 barycentric(0);
        VertexShaderOutputParams interpolatedValue;
        // interpolate the attributes.
        for (int i = 0; i < vertices.size(); i++) {
            Triangle::computeBarycentricCoord(v0, v1, v2, vertices[i], barycentric);
            //cout << barycentric[0] << ' ' << barycentric[1] <<  ' ' << barycentric[2] << endl;
            interpolateBarycentric(triangleAttributes, barycentric, interpolatedValue);
            result.push_back(interpolatedValue);
        }
    }

    void clipTriangle3D(const Frustum &frutsum, const Triangle &triangle, vector<Triangle> &result) {
        std::vector<vec4> clippedPolygon = {triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]};
        //
        // std::cout << "initial Triangle: " << clippedPolygon[0].x << ","<< clippedPolygon[0].y << ","<< clippedPolygon[0].z << " "
        //                                << clippedPolygon[i-1].x << ","<< clippedPolygon[i-1].y << ","<< clippedPolygon[i-1].z << " "
        //                                << clippedPolygon[i].x << ","<< clippedPolygon[i].y << ","<<clippedPolygon[i].z  << endl;
        float dist;
        float prevDist;
        float firstDist;
        vec4 prevPoint;

        for (size_t j = 0; j < 6; j++) {
            Plane plane = frutsum.sides[j];

            int delta = 0;

            dist = glm::dot(clippedPolygon[0], plane.normal) - plane.distance;
            prevPoint = clippedPolygon[0];

            firstDist = dist;
            for (size_t i = 1; delta + i < clippedPolygon.size(); i++) {
                prevDist = dist;
                dist = glm::dot(clippedPolygon[i + delta], plane.normal) - plane.distance;

                if (dist < 0) { //ith element is not inside
                    if (prevDist < 0) {
                        prevPoint = clippedPolygon[i + delta];
                        clippedPolygon.erase(clippedPolygon.begin() + i + delta); //remove outside point
                        delta--;
                    } else {
                        //add intersection
                        float s = prevDist / (prevDist - dist);

                        vec4 fdp = {prevPoint.x + s * (clippedPolygon[i + delta].x - prevPoint.x),
                                    prevPoint.y + s * (clippedPolygon[i + delta].y - prevPoint.y),
                                    prevPoint.z + s * (clippedPolygon[i + delta].z - prevPoint.z),
                                    1};

                        prevPoint = clippedPolygon[i + delta];
                        clippedPolygon.insert(clippedPolygon.begin() + delta + i,
                                              fdp
                        );

                        clippedPolygon.erase(clippedPolygon.begin() + i + delta + 1); //remove outside point
                    }
                } else { // ith element is inside
                    if (prevDist < 0) {
                        //add intersection
                        float s = prevDist / (prevDist - dist);

                        vec4 fdp = {prevPoint.x + s * (clippedPolygon[i + delta].x - prevPoint.x),
                                    prevPoint.y + s * (clippedPolygon[i + delta].y - prevPoint.y),
                                    prevPoint.z + s * (clippedPolygon[i + delta].z - prevPoint.z),
                                    1};

                        prevPoint = clippedPolygon[i + delta];
                        clippedPolygon.insert(clippedPolygon.begin() + delta + i,
                                              fdp
                        );
                        delta++;
                    } else {
                        prevPoint = clippedPolygon[i + delta];
                    }
                }
            }

            // at the end of the loop we have to complete the polygon between last and first points

            prevDist = dist;
            dist = firstDist;

            if (dist < 0) { //1st element is not inside
                if (prevDist < 0) {
                    clippedPolygon.erase(clippedPolygon.begin());
                    delta--;
                } else {
                    //add intersection
                    float s = prevDist / (prevDist - dist);

                    vec4 fdp = {prevPoint.x + s * (clippedPolygon[0].x - prevPoint.x),
                                prevPoint.y + s * (clippedPolygon[0].y - prevPoint.y),
                                prevPoint.z + s * (clippedPolygon[0].z - prevPoint.z),
                                1};

                    clippedPolygon.erase(clippedPolygon.begin()); //remove outside point

                    clippedPolygon.insert(clippedPolygon.begin(),
                                          fdp
                    );

                }
            } else { // 1st element is inside
                if (prevDist < 0) {
                    //add intersection
                    float s = prevDist / (prevDist - dist);

                    vec4 fdp = {prevPoint.x + s * (clippedPolygon[0].x - prevPoint.x),
                                prevPoint.y + s * (clippedPolygon[0].y - prevPoint.y),
                                prevPoint.z + s * (clippedPolygon[0].z - prevPoint.z),
                                1};

                    clippedPolygon.insert(clippedPolygon.begin(),
                                          fdp
                    );
                    delta++;
                }

            }


        }


        for (size_t i = 2; i < clippedPolygon.size(); i++) {
            Triangle tmp = {
                    clippedPolygon[0],
                    clippedPolygon[i - 1],
                    clippedPolygon[i],
                    triangle.normal
            };
            result.push_back(tmp);
        }


    }

    void clipPoint3D(const Frustum &frustum, const vec3 point) {

    }

    void clipLine(const Frustum &frustum, Line line) {

    }

}
