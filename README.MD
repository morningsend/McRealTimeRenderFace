# Computer Graphics Coursework Report

### Author: Zaiyang Li (zl14917)

## Rasterizer

Some facts about my rasterizer implementation:

* It uses horizontal scanline algorithm to quickly convert triangle to pixels. This seems to be faster than calculating barycentric coordinates to test if each pixel belongs to a triangle.

* Lighting calculations are performed in HDR linear colour space. HDR tone mapping is used to convert to LDR colour space (each pixel having intensity between 0 and 1). Final colour is written to the framebuffer in sRGB colour space using gamma correction with a value of 2.2.

* Linear workflow also implies that diffuse texture must be coverted from sRGB colour space to linear before it can be used. Normal and roughness map do not need to be converted. 

* Deferred rendering pipeline architecture: geometry pass -> SSAO (screen space ambient occlusion) pass -> Lighting pass -> post processing (gamma correction and HDR tone mapping)

* Physically based material using Cook Torrance microfacet BRDF, in particular, I used GGX Specular BRDF combined with Lambert diffuse BRDF.

### Summary of Extensions

* Simple back face culling.
* Clipping in homogeneous coordinate.
* Supports two types of light: point light and spot light.
* Perspective correct interpolation.
* Texture mapping.
* Normal mapping.
* Microfact BRDF, supports GGX and Beckmann distribution.
* Bilinear and nearest texture filtering.
* Post processing effects: HDR tone mapping (filmic), gamma correction.

## Ray Tracer

Implementation Details:

* Uses Monte Carlo path tracing algorithm.
* Lighting calculations done in linear colour space, the same as the rasterizer.
* Writes output in HDR (.hdr) format.
* Microfacet model, physically based.

Summary of extensions:
* Supports 4 types of material: diffuse, specular (glossy), refractive and reflective (mirror).
* Supports image based lighting.
* Glossy specular surface is rendered using Cook-Torrance microfacet BRDF model by sampling the half-vector.
*  GGX (a.k.a Trowbridge Reitz) normal distribution is used to model roughness in specular reflections.
* Stratified subpixel sampling to reduce variance.
* Supports reconstruction filters to further reduce noise: box filter, gaussian filter, Mitchell-Netravali cubic filter.
* Loading OBJ models.
* Easy to use C++ API.
