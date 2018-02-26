#include <iostream>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include "scene/TestModelH.h"
#include "rendering/Rasterizer.hpp"
#include <stdint.h>

using namespace std;
using namespace McRenderer;
using glm::vec3;
using glm::mat3;
using glm::vec4;
using glm::mat4;


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 256
#define FULLSCREEN_MODE false

/* ----------------------------------------------------------------------------*/
/* FUNCTIONS                                                                   */

void Update(Camera& camera);
void Draw(screen* screen);

void setupScene(Scene& scene) {
    scene.camera.position = vec3(0, 0, 0);
    scene.camera.forward = vec3(0,0,-1);
    scene.camera.up = vec3(0,1,0);
    scene.camera.aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
    //scene.model
}
int main( int argc, char* argv[] )
{

    screen *screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN_MODE );
    Scene scene;
    setupScene(scene);
    Rasterizer rasterizer{&scene, SCREEN_WIDTH, SCREEN_HEIGHT};
    while( NoQuitMessageSDL() )
    {
        Update(scene.camera);
        rasterizer.renderToScreen(screen);
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

/*Place updates of parameters here*/
void Update(Camera& camera)
{
    uint8* keystate = const_cast<uint8 *>(SDL_GetKeyboardState(0));

    if(keystate[SDL_SCANCODE_UP]) {
        camera.position += camera.forward * 0.1f;
    }
    if(keystate[SDL_SCANCODE_DOWN]) {
        camera.position -= camera.forward * 0.1f;
    }
    if(keystate[SDL_SCANCODE_LEFT]) {
        camera.position += camera.right * 0.1f;
    }
    if(keystate[SDL_SCANCODE_RIGHT]) {
        camera.position -= camera.right * 0.1f;
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
