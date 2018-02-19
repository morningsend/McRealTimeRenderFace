//
// Created by Zaiyang Li on 29/01/2018.
//

#include "Camera.hpp"

namespace  McRenderer {


    void Camera::move(vec3 delta) {
        position += delta;
    }

    Camera::Camera(const vec4 &positionIn, const vec4 &directionIn, const vec4 &upIn)
            : position(positionIn), direction(directionIn), up(upIn){

    }
}