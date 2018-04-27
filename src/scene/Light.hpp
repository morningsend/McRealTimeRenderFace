//
// Created by Zaiyang Li on 30/01/2018.
//

#ifndef RENDERER_LIGHTSOURCE_HPP
#define RENDERER_LIGHTSOURCE_HPP

#include "../common.h"

namespace McRenderer {
    using namespace glm;

    enum LightType {
        PointLight,
        SpotLight,

    };
    struct Light {
        float intensity{1};
        vec4 colour{1};
        vec4 position{1};
        bool castShadow {false};
        LightType type{LightType::PointLight};
        float range{10.0f};
    };

    struct SpotLight : public Light {
        float fallOffAngle{45};
        float cosineFallOff{.5f};
        vec4 direction{0,-1,0,0};

        SpotLight() {
            type = LightType::SpotLight;
        }
        void computeCosineFallOff() {
            cosineFallOff = std::cos(glm::radians(fallOffAngle));
        }
    };
    struct PointLight: public Light {

        PointLight(){
            type = LightType::PointLight;
        }
    };

}


#endif //RENDERER_LIGHTSOURCE_HPP
