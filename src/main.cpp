//#define GRAPHICS_DEBUG

#include <iostream>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <stdint.h>
#include <cmath>

#include "SDLauxiliary.h"
#include "scene/TestModelH.h"
#include "scene/Light.hpp"
#include "rendering/Rasterizer.hpp"
#include "rendering/RenderingPipeline.hpp"
#include "rendering/BasicFragmentShader.hpp"
#include "rendering/BasicVertexShader.hpp"

using namespace std;
using namespace McRenderer;

using glm::vec3;
using glm::mat3;
using glm::vec4;
using glm::mat4;

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define FULLSCREEN_MODE false

/* ----------------------------------------------------------------------------*/
/* FUNCTIONS                                                                   */

void Update(Camera& camera);
void Update(Light& light);
void Draw(screen* screen);

void setupScene(Scene& scene) {
    vector<::Triangle> triangles;
    LoadTestModel(triangles);
    scene.camera.position = vec3(0, 0, -2);
    scene.camera.forward = vec3(0, 0, 1);
    scene.camera.up = vec3(0,1,0);
    scene.camera.aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
    scene.camera.fieldOfView = 70;
    scene.camera.farClippingDistance = 1000.0f;
    scene.camera.nearClippingDistance = 0.4f;
    for(::Triangle& tri: triangles) {
        McRenderer::Triangle triangle(
                tri.v0, tri.v1, tri.v2, tri.normal, vec4(tri.color, 1)
        );
        computeTangentBasis(triangle);
        scene.model.push_back(triangle);
    }
    /*
    scene.model.push_back(McRenderer::Triangle(
            vec4(-1,-1,-1,1), vec4(-1,-1,1,1), vec4(-1, 1, -1, 1),
            vec4(1, 0, 0, 0),
            vec4(1)
    ));
    scene.model.push_back(McRenderer::Triangle(
            vec4(-1, 1,-1,1), vec4(-1,-1,1,1), vec4(-1, 1, 1, 1),
            vec4(1, 0, 0, 0),
            vec4(1)
    ));*/

    PointLightSource light;
    light.intensity = 5.0f;
    light.colour = vec4(1.0f);
    light.position = vec4(0, 0.9, -.4, 1);
    scene.lights.push_back(light);

    MaterialSpec materialSpec;
    materialSpec.diffuseMap = "textures/redbricks2b.png";
    materialSpec.specularColor = vec3(0.7f);
    materialSpec.normalMap = "textures/redbricks2b-normal.png";

    scene.materialSpecs.push_back(materialSpec);

    scene.initialize();
}
int main( int argc, char* argv[] )
{
    screen *screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN_MODE );
    Scene scene;
    setupScene(scene);
    RasterizerConfig config;
    config.viewportWidth = SCREEN_WIDTH;
    config.viewportHeight = SCREEN_HEIGHT;
    config.faceMode = FaceRenderMode::Shaded;
    PipelineBuilder builder;
    unique_ptr<RenderingPipeline> pipeline = builder.singlethreaded()
            .useFragmentShader(new BasicFragmentShader())
            .useVertexShader(new BasicVertexShader())
            .configureRasterizer(config)
            .writeOutputTo(new FrameBuffer(SCREEN_WIDTH, SCREEN_HEIGHT))
            .build();
    while( NoQuitMessageSDL() )
    {
        Update(scene.camera);
        Update(scene.lights[0]);
        pipeline->submitScene(scene);
        pipeline->getFrameBuffer().copyToScreen(screen);
        SDL_Renderframe(screen);
    }

    SDL_SaveImage( screen, "screenshot.bmp" );

    KillSDL(screen);
    return 0;
}

/*Place your drawing here*/
void Draw(screen* screen)
{
    /* Clear buffer */
    memset(screen->buffer, 0, screen->height*screen->width*sizeof(uint32_t));

    vec3 colour(1.0,0.0,0.0);
    for(int i=0; i<1000; i++)
    {
        uint32_t x = rand() % screen->width;
        uint32_t y = rand() % screen->height;
        PutPixelSDL(screen, x, y, colour);
    }
}

void Update(Light& light) {
    uint8* keystate = const_cast<uint8 *>(SDL_GetKeyboardState(0));

    if(keystate[SDL_SCANCODE_W]) {
        light.position += vec4(0,1,0,0) * 0.051f;
    }
    if(keystate[SDL_SCANCODE_S]) {
        light.position -= vec4(0,1,0,0) * 0.051f;
    }

    if(keystate[SDL_SCANCODE_A]) {
        light.position += vec4(1,0,0,0) * 0.051f;
    }
    if(keystate[SDL_SCANCODE_D]) {
        light.position -= vec4(1,0,0,0) * 0.051f;
    }

}
/*Place updates of parameters here*/
void Update(Camera& camera)
{
    uint8* keystate = const_cast<uint8 *>(SDL_GetKeyboardState(0));

    if(keystate[SDL_SCANCODE_UP]) {
        camera.position += camera.forward * 0.051f;
    }
    if(keystate[SDL_SCANCODE_DOWN]) {
        camera.position -= camera.forward * 0.051f;
    }
    if(keystate[SDL_SCANCODE_LEFT]) {
        camera.position += camera.right * 0.051f;
    }
    if(keystate[SDL_SCANCODE_RIGHT]) {
        camera.position -= camera.right * 0.051f;
    }
    if(keystate[SDL_SCANCODE_R]) {
        camera.up.x= camera.up.x * cos(0.01) - camera.up.y*sin(0.01);
        camera.up.y= camera.up.y*cos(0.01) + sin(0.01) * camera.up.x;
    }
    static int t = SDL_GetTicks();
    /* Compute frame time */
    int t2 = SDL_GetTicks();
    float dt = float(t2-t);
    t = t2;
    /*Good idea to remove this*/
    std::cout << "Render time: " << dt << " ms." << std::endl;
    std::cout << "Camera position:"
              << camera.position.x << ' '
              << camera.position.y << ' '
              << camera.position.z << endl;
    std::cout << "Camera forward" << ' '
              << camera.forward.x << ' '
              << camera.forward.y << ' '
              << camera.forward.z << ' '<<endl;
    /* Update variables*/
}
