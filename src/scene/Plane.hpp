//
// Created by Zaiyang Li on 25/01/2018.
//

#ifndef RENDERER_PLANE_HPP
#define RENDERER_PLANE_HPP

#include <glm/glm.hpp>

using namespace glm;

struct Plane {
  vec4 normal;
  float distance;

  Plane(vec4 _normal, float _distance): normal{_normal}, distance{_distance} {}
  Plane(vec3 _normal, float _distance): normal{_normal[0], _normal[1], _normal[2], 0}, distance{_distance} {}
  Plane() {}

    void normalize() {

        float magnitude = glm::length(normal);
        normal /= magnitude;
        distance /= distance;
    }

};


#endif //RENDERER_PLANE_HPP
