//
// Created by Zaiyang Li on 29/01/2018.
//

#ifndef RENDERER_CAMERA_HPP
#define RENDERER_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace McRenderer {
    using namespace glm;
    struct Camera {
        vec3 position{0,0,0};
        vec3 right{-1, 0, 0};
        vec3 up{0,1,0};
        vec3 forward{0,0,1};

        float aspectRatio{1};
        float nearClippingDistance{.1};
        float farClippingDistance{1000};
        float fieldOfView{45};

        mat4 viewingMatrix();
        mat4 projectionMatrix();
        mat4 viewProjectionMatrix();

        Camera(vec3 positionIn, vec3 directionIn, vec3 upIn): position{positionIn}, forward{directionIn}, up{upIn} {}
        Camera() {}
        void move(vec3 delta);

    };

}



#endif //RENDERER_CAMERA_HPP
