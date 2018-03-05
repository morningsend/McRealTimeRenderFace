//
// Created by Zaiyang Li on 31/01/2018.
//

#include "Triangle.hpp"
#include "Line.hpp"
namespace McRenderer {

    void computeTriangleNormal(Triangle& triangle) {
        vec4 e1 = triangle.vertices[1] - triangle.vertices[0];
        vec4 e2 = triangle.vertices[2] - triangle.vertices[0];

        triangle.normal = glm::normalize(vec4(glm::cross(vec3(e1), vec3(e2)), 0));
    }

    void clipTriangle3D(const Frustum frutsum, const Triangle& triangle, vector<Triangle>& result) {
      std::vector<vec4> clippedPolygon = {triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]};
      //
      // std::cout << "initial Triangle: " << clippedPolygon[0].x << ","<< clippedPolygon[0].y << ","<< clippedPolygon[0].z << " "
      //                                << clippedPolygon[i-1].x << ","<< clippedPolygon[i-1].y << ","<< clippedPolygon[i-1].z << " "
      //                                << clippedPolygon[i].x << ","<< clippedPolygon[i].y << ","<<clippedPolygon[i].z  << endl;


      float dist;
      float prevDist;
      vec4 prevPoint;

      for (size_t j = 0; j < 6; j++) {
        Plane plane = frutsum.sides[j];

        int delta = 0;

        dist = glm::dot(clippedPolygon[0], plane.normal) - plane.distance;
        prevPoint = clippedPolygon[0];
        if (dist < 0) { // first element is not inside
          clippedPolygon.erase(clippedPolygon.begin()); //remove first element;
          delta--;
        }

        for (size_t i = 1; delta + i < clippedPolygon.size(); i++) {
          prevDist = dist;
          dist = glm::dot(clippedPolygon[i], plane.normal) - plane.distance;

          if (dist < 0) { //ith element is not inside
            if (prevDist < 0) {
              delta--;
              prevPoint = clippedPolygon[i+delta];
            }
            else{
              //add intersection
              float s = prevDist / (prevDist - dist);

              vec4 fdp = {prevPoint.x + s*(clippedPolygon[i+delta].x - prevPoint.x),
                            prevPoint.y + s*(clippedPolygon[i+delta].y - prevPoint.y),
                            prevPoint.z + s*(clippedPolygon[i+delta].z - prevPoint.z),
                            1};

              prevPoint = clippedPolygon[i+delta];
              clippedPolygon.insert(clippedPolygon.begin() + delta + i,
                                      fdp
                                    );

            clippedPolygon.erase(clippedPolygon.begin() + i + delta+1); //remove outside point
            }
          }
          else{ // ith element is inside
            if (prevDist < 0) {
              delta++;
              //add intersection
              float s = prevDist / (prevDist - dist);

              vec4 fdp = {prevPoint.x + s*(clippedPolygon[i+delta].x - prevPoint.x),
                            prevPoint.y + s*(clippedPolygon[i+delta].y - prevPoint.y),
                            prevPoint.z + s*(clippedPolygon[i+delta].z - prevPoint.z),
                            1};

              prevPoint = clippedPolygon[i+delta];
              clippedPolygon.insert(clippedPolygon.begin() + delta + i,
                                      fdp
                                    );
            }
            else{
              prevPoint = clippedPolygon[i+delta];
            }
          }
        }

      }

      std::cout << clippedPolygon.size() << endl;

      for (size_t i = 2; i < clippedPolygon.size(); i++) {
        std::cout << "new triangle ("<<i<<"): " << clippedPolygon[0].x << ","<< clippedPolygon[0].y << ","<< clippedPolygon[0].z << " "
                                       << clippedPolygon[i-1].x << ","<< clippedPolygon[i-1].y << ","<< clippedPolygon[i-1].z << " "
                                       << clippedPolygon[i].x << ","<< clippedPolygon[i].y << ","<<clippedPolygon[i].z  << endl;
        Triangle tmp = {
                          clippedPolygon[0],
                          clippedPolygon[i-1],
                          clippedPolygon[i],
                          triangle.normal
                       };
        result.push_back(tmp);
      }


    }

}
