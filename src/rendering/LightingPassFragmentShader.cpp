//
// Created by Zaiyang Li on 02/04/2018.
//

#include "LightingPassFragmentShader.hpp"
#include "../shader/Microfacet.hpp"

namespace McRenderer {
    using namespace glm;
    using namespace std;

    inline float max(float a, float b) {
        return a > b ? a : b;
    }

    void LightingPassFragmentShader::run(const ShaderEnvironment &env,
                                         const LightingPassFragmentShaderParams &lightingParams,
                                         LightingPassFragmentShaderOutput &output) {
        float roughness = max(lightingParams.specularRoughness, 0.1f);
        vec3 diffuse = lightingParams.diffuseColour;
        vec3 specular = vec3(1);//lightingParams.specularColour;
        vec3 normal = lightingParams.normal;

        vec3 lightDirection = lightingParams.lightPosition - lightingParams.position;
        float lightDistance = length(lightDirection);
        vec3 viewDirection = lightingParams.viewDirection;
        //output.lightContribution = normalize(lightDirection);
        lightDirection /= lightDistance;
        lightDistance += 1;
        vec3 halfVector = normalize(lightDirection + viewDirection);
        float attenuationFactor = 1 / (lightDistance * lightDistance * 2 * F_PI);
        float nDotL = max(dot(normal, lightDirection), 0);
        float nDotV = max(dot(normal, viewDirection), 0);
        float lDotH = max(dot(halfVector, lightDirection), 0);
        float nDotH = dot(normal, halfVector);

        float fresnel = (shlickFresnel(lDotH, 0.04f));
        // evaluate specular BRDF;
        float specularBRDF =
                ggxDistribution(nDotH, roughness) *
                schlickGGXGeometricShadowMaskingFunc(nDotL, nDotV, roughness) * fresnel
                / max(0.001, (4 * nDotL * nDotV));
        specular = specular * lightingParams.lightColour * (specularBRDF * lightingParams.lightIntensity * attenuationFactor * nDotL);
        // evaluate diffuse BRDF;
        diffuse = lightingParams.diffuseColour * lightingParams.lightColour * (lightingParams.lightIntensity * nDotL * attenuationFactor) * (1- fresnel);
        output.lightContribution = diffuse + specular;
    }
}