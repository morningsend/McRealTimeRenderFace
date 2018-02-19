//
// Created by Zaiyang Li on 30/01/2018.
//

#ifndef RENDERER_LIGHTSOURCE_HPP
#define RENDERER_LIGHTSOURCE_HPP

#include <glm/glm.hpp>

// si
namespace McRenderer {
    using namespace glm;

    enum class AttenuationType {
        InverseSquare,
        Linear,
        InverseExponential
    };

    struct Light {
        float intensity;
        vec3 color;
        AttenuationType type;
        vec4 position;

    };

    struct AmbientLight : Light {

    };
    struct AreaLightSource : public Light{
        float fallOffAngle;
        float width;
        float height;
        vec4 direction;
    };

    struct PointLightSource: public Light {

    };

    struct SpotLight : public Light {
        float fallOffAngle;
        vec4 direction;
    };


}


#endif //RENDERER_LIGHTSOURCE_HPP
