//
// Created by Zaiyang Li on 29/01/2018.
//

#include "Camera.hpp"

namespace  McRenderer {



    void Camera::move(vec3 delta) {
        position += delta;
    }

    mat4 Camera::viewingMatrix(){
      return  glm::lookAt(position, position-forward, up);
    }

    mat4 Camera::projectionMatrix(){
      return glm::perspective(
                                glm::radians(fieldOfView),
                                aspectRatio,
                                nearClippingDistance,
                                farClippingDistance
                              );
    }

    mat4 Camera::viewProjectionMatrix() {
        return projectionMatrix() * viewingMatrix();
    }

    void Camera::initFrustum(){
      float fovH = -atan(tan(radians(fieldOfView))*aspectRatio)/2; //horizontal field of view
      float fovV = radians(fieldOfView)/2;
      float sh = sin(fovH);
      float ch = cos(fovH);
      float sv = sin(fovV);
      float cv = cos(fovV);

      // bottom
      frustum.sides[0].normal.x=0;
      frustum.sides[0].normal.y=-cv;
      frustum.sides[0].normal.z=sv;
      frustum.sides[0].distance = 0;
      // top
      frustum.sides[1].normal.x=0;
      frustum.sides[1].normal.y=cv;
      frustum.sides[1].normal.z=sv;
      frustum.sides[1].distance = 0;
      // left
      frustum.sides[2].normal.x=-ch;
      frustum.sides[2].normal.y=0;
      frustum.sides[2].normal.z=sh;
      frustum.sides[2].distance = 0;
      // right
      frustum.sides[3].normal.x=ch;
      frustum.sides[3].normal.y=0;
      frustum.sides[3].normal.z=sh;
      frustum.sides[3].distance = 0;
      // near
      frustum.sides[4].normal.x=0;
      frustum.sides[4].normal.y=0;
      frustum.sides[4].normal.z=1;
      frustum.sides[4].distance = nearClippingDistance;
      // far
      frustum.sides[5].normal.x=0;
      frustum.sides[5].normal.y=0;
      frustum.sides[5].normal.z=1;
      frustum.sides[5].distance = -farClippingDistance; // hack to invert the normal but the rest of the code still works

    }


}
