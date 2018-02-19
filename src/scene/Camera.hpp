//
// Created by Zaiyang Li on 29/01/2018.
//

#ifndef RENDERER_CAMERA_HPP
#define RENDERER_CAMERA_HPP

#include <glm/glm.hpp>
namespace McRenderer {
    using namespace glm;
    struct Camera {
        vec3 position;
        vec3 direction;
        vec3 up;

        float aspectRatio;
        float nearClippingDistance;
        float farClippingDistance;

        mat4 viewingMatrix();

        explicit Camera(const vec4& positionIn, const vec4& directionIn, const vec4& up);

        void move(vec3 delta);

    };

}



#endif //RENDERER_CAMERA_HPP
