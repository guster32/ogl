// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#define GLEW_EGL
// Include GLEW
// #include <GL/glew.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
// Include SDL2
#include <SDL2/SDL.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;


void HandleEvent(SDL_Event *event, bool &running) {
    switch (event->type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_p) {
                //ggpoutil_perfmon_toggle();
            } else if (event->key.keysym.sym == SDLK_ESCAPE) {
                //VectorWar_Exit();
                running = false;
            } else if (event->key.keysym.sym >= SDLK_F1 && event->key.keysym.sym <= SDLK_F12) {
                //VectorWar_DisconnectPlayer(event->key.keysym.sym - SDLK_F1);
            }
            break;
    }
}

SDL_Window* CreateMainWindow(const char *title, int width, int height) {
    SDL_Window *window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );
    if (!window) {
        fprintf(stderr, "Failed to create SDL window: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return window;
}


//tinywl  -s "SDL_VIDEODRIVER=wayland 00_sdl2"
int main(void)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);  // No alpha channel
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 24);  // 8 bits each for R, G, B

    // Create an SDL window
    SDL_Window* window = SDL_CreateWindow("Vector War", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Failed to create SDL window: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Create an OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        fprintf(stderr, "Failed to create OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Make the context current
    if (SDL_GL_MakeCurrent(window, glContext) != 0) {
        fprintf(stderr, "Failed to make the OpenGL context current: %s\n", SDL_GetError());
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // // Initialize GLEW
    // GLenum err = glewInit();
    // if (err != GLEW_OK) {
    //     fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
    //     SDL_GL_DeleteContext(glContext);
    //     SDL_DestroyWindow(window);
    //     SDL_Quit();
    //     return -1;
    // }

    // Enable V-Sync
    if (SDL_GL_SetSwapInterval(1) < 0) {
        fprintf(stderr, "Failed to set V-Sync: %s\n", SDL_GetError());
    }

    // Dark blue background
    glClearColor(0.7f, 0.2f, 0.4f, 0.0f);

    bool running = true;
    SDL_Event event;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }
        }

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}