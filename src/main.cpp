#define GRAPHICS_DEBUG

#include "common.h"
#include <SDL2/SDL.h>
#include "SDLauxiliary.h"
#include "scene/TestModelH.h"
#include "scene/Light.hpp"
#include "rendering/DeferredRenderingPipeline.hpp"
#include "rendering/BasicVertexShader.hpp"
#include "rendering/GeometryPassFragmentShader.hpp"

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
void Update(DeferredRenderingPipeline& pipeline);

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
    light.intensity = 10.0f;
    light.colour = vec4(.5,.5,1,1);
    light.position = vec4(-0.4, 0.9, 0, 1);
    scene.lights.push_back(light);

    light.intensity = 10.0f;
    light.colour = vec4(1, .5, .5, 1);
    light.position = vec4(0.4, 0.9, 0, 1);
    scene.lights.push_back(light);

    light.colour = vec4(.5, 1.0f, .5, 1);
    light.position = vec4(0, 0.9, .8, 1);
    //scene.lights.push_back(light);

    MaterialSpec materialSpec;

    materialSpec.basecolourMap = "textures/New_Graph_basecolor.png";
    materialSpec.metalness = 0.f;
    materialSpec.normalMap = "textures/New_Graph_normal.png";
    materialSpec.roughnessMap = "textures/New_Graph_roughness.png";
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
    unique_ptr<DeferredRenderingPipeline> pipeline = builder.singlethreaded()
            .useFragmentShader(new GeometryPassFragmentShader())
            .useVertexShader(new BasicVertexShader())
            .configureRasterizer(config)
            .writeOutputTo(new FrameBuffer(SCREEN_WIDTH, SCREEN_HEIGHT))
            .build();
    while( NoQuitMessageSDL() )
    {
        Update(scene.camera);
        Update(scene.lights[0]);
        Update(*pipeline);
        pipeline->submitScene(scene);
        pipeline->getOutputFrameBuffer().copyToScreen(screen);
        SDL_Renderframe(screen);
    }

    SDL_SaveImage( screen, "screenshot.bmp" );

    KillSDL(screen);
    return 0;
}

void Update(DeferredRenderingPipeline& pipeline) {
    uint8* keystate = const_cast<uint8 *>(SDL_GetKeyboardState(0));

#ifdef  GRAPHICS_DEBUG
    if(keystate[SDL_SCANCODE_1]) {
        pipeline.setDebuggingPass(ShaderPass::Diffuse);
    }
    if(keystate[SDL_SCANCODE_2]) {
        pipeline.setDebuggingPass(ShaderPass::Specular);
    }
    if(keystate[SDL_SCANCODE_3]) {
        pipeline.setDebuggingPass(ShaderPass::Normal);
    }
    if(keystate[SDL_SCANCODE_4]) {
        pipeline.setDebuggingPass(ShaderPass::Lighting);
    }
    if(keystate[SDL_SCANCODE_5]) {
        pipeline.setDebuggingPass(ShaderPass::Tangent);
    }
    if(keystate[SDL_SCANCODE_6]) {
        pipeline.setDebuggingPass(ShaderPass::Depth);
    }
    if(keystate[SDL_SCANCODE_7]) {
        pipeline.setDebuggingPass(ShaderPass::AmbientOcclusion);
    }
    if(keystate[SDL_SCANCODE_0]) {
        pipeline.setDebuggingPass(ShaderPass::All);
    }
#endif
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
        camera.up.x= camera.up.x * cos(0.01f) - camera.up.y*sin(0.01f);
        camera.up.y= camera.up.y*cos(0.01f) + sin(0.01f) * camera.up.x;
    }
    if(keystate[SDL_SCANCODE_N]) {
        camera.forward = vec3(glm::rotate(0.1f, vec3(0,1,0)) * vec4(camera.forward, 0));
        camera.right = vec3(glm::rotate(0.1f, vec3(0,1,0)) * vec4(camera.right, 0));
    }
    if(keystate[SDL_SCANCODE_M]) {
        camera.forward = vec3(glm::rotate(-0.1f, vec3(0,1,0)) * vec4(camera.forward, 0));
        camera.forward = vec3(glm::rotate(-0.1f, vec3(0,1,0)) * vec4(camera.right, 0));
    }
    static int t = SDL_GetTicks();
    /* Compute frame time */
    int t2 = SDL_GetTicks();
    float dt = float(t2-t);
    t = t2;
    /*Good idea to remove this*/
    std::cout << "Render time: " << dt << " ms." << std::endl;
    /* Update variables*/
}
