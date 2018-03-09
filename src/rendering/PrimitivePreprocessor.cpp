//
// Created by Zaiyang Li on 26/02/2018.
//

#include "PrimitivePreprocessor.hpp"
namespace McRenderer {

    bool PrimitivePreprocessor::clipTriangle(const Frustum& frustum, Triangle &triangle, vector<Triangle> &result) {
        return false;
    }

    bool PrimitivePreprocessor::clipLine(const Frustum& frustom, Line &line) {
        return false;
    }

  void clipTriangle3D(const Frustum& frutsum, const Triangle& triangle, vector<Triangle>& result) {
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
        dist = glm::dot(clippedPolygon[i+delta], plane.normal) - plane.distance;

        if (dist < 0) { //ith element is not inside
          if (prevDist < 0) {
            prevPoint = clippedPolygon[i+delta];
            clippedPolygon.erase(clippedPolygon.begin() + i + delta); //remove outside point
            delta--;
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
            delta++;
          }
          else{
            prevPoint = clippedPolygon[i+delta];
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
        }
        else{
          //add intersection
          float s = prevDist / (prevDist - dist);

          vec4 fdp = {prevPoint.x + s*(clippedPolygon[0].x - prevPoint.x),
            prevPoint.y + s*(clippedPolygon[0].y - prevPoint.y),
            prevPoint.z + s*(clippedPolygon[0].z - prevPoint.z),
            1};

            clippedPolygon.erase(clippedPolygon.begin()); //remove outside point

            clippedPolygon.insert(clippedPolygon.begin(),
            fdp
          );

        }
      }
      else{ // 1st element is inside
        if (prevDist < 0) {
          //add intersection
          float s = prevDist / (prevDist - dist);

          vec4 fdp = {prevPoint.x + s*(clippedPolygon[0].x - prevPoint.x),
            prevPoint.y + s*(clippedPolygon[0].y - prevPoint.y),
            prevPoint.z + s*(clippedPolygon[0].z - prevPoint.z),
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
        clippedPolygon[i-1],
        clippedPolygon[i],
        triangle.normal
      };
      result.push_back(tmp);
    }


  }

}
