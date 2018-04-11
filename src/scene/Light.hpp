//
// Created by Zaiyang Li on 30/01/2018.
//

#ifndef RENDERER_LIGHTSOURCE_HPP
#define RENDERER_LIGHTSOURCE_HPP

#include "../common.h"

// si
namespace McRenderer {
    using namespace glm;

    struct Light {
        float intensity{1};
        vec4 colour{1};
        vec4 position{1};
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
