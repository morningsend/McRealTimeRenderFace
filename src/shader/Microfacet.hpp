//
// Created by Zaiyang Li on 03/04/2018.
//

#ifndef RENDERER_MICROFACET_HPP
#define RENDERER_MICROFACET_HPP
#include <cmath>

namespace McRenderer {
    const float MPI = 3.1415926f;
    inline float beckmannDistribution(float nDotH, float roughness) {
        float nDotH2 = nDotH * nDotH;
        float roughness2 = roughness * roughness;

        float a = ( MPI * roughness2 * (nDotH2*nDotH2));
        float b = exp((roughness2 - 1) / (roughness2 * nDotH2));
        return b / a;
    }
    inline float ggxDistribution(float nDotH, float roughness) {
        float roughness2 = roughness * roughness;
        float nDotH2 = nDotH * nDotH;
        float tanNDotH2 = (1 - nDotH2) / nDotH2;
        float denom = nDotH2 * (roughness2 + tanNDotH2);
        denom *= denom * denom * MPI;
        float sign = nDotH > 0 ? 1 : 0;
        return sign * roughness2 / denom;

    }

    inline float blinnPhongDistribution(float nDotH, float shininess) {
        return (shininess + 2.0f) / (2 * MPI) * pow(nDotH, shininess);
    }
    inline float schlickGeometricShadowMaskingFunc(float nDotL, float nDotV, float roughness) {
        float roughness2 = roughness * roughness;
        float smith1 = nDotL / (nDotL * (1-roughness2 ) + roughness2);
        float smith2 = nDotV / (nDotV * (1-roughness2 ) + roughness2);
        return smith1 * smith2;
    }
    inline float schlickGGXGeometricShadowMaskingFunc(float nDotL, float nDotV, float roughness) {
        float m = roughness / 2;
        float smith1 = nDotL / (nDotL * (1-m ) + m);
        float smith2 = nDotV / (nDotV * (1-m ) + m);
        return smith1 * smith2;
    }
    inline float schlickBeckmannGeometricShadowMaskingFunc(float nDotL, float nDotV, float roughness) {
        float roughness2 = roughness * roughness;
        //0.7978845608 = sqrt (2/pi)
        float k = roughness2 * 0.7978845608f;

        float smith1L = nDotL/(nDotL * (1-k) + k);
        float smith1V = nDotV/(nDotV * (1-k) + k);
        return smith1L * smith1V;
    }
    inline float shlickFresnel(float lDotH, float f0) {
        return f0 + (1-f0) * pow(1.0f - lDotH, 5.0f);
    }
    inline float f0(float ior1, float ior2) {
        float k = (ior1 - ior2) /(ior1 + ior2);
        return k * k;
    }
}
#endif //RENDERER_MICROFACET_HPP
