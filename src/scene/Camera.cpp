//
// Created by Zaiyang Li on 29/01/2018.
//

#include "Camera.hpp"

namespace  McRenderer {


    void Camera::move(vec3 delta) {
        position += delta;
    }

    mat4 Camera::viewingMatrix(){
        return glm::mat4(1);
    }


}
