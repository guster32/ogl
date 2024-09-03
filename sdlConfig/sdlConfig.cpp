#include <stdio.h>
#include <SDL2/SDL.h>

void print_desired_sdl_opengl_config() {
    int value;

    SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &value);
    printf("Desired Red Size: %d\n", value);

    SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &value);
    printf("Desired Green Size: %d\n", value);

    SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &value);
    printf("Desired Blue Size: %d\n", value);

    SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &value);
    printf("Desired Alpha Size: %d\n", value);

    SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &value);
    printf("Desired Depth Size: %d\n", value);

    SDL_GL_GetAttribute(SDL_GL_STENCIL_SIZE, &value);
    printf("Desired Stencil Size: %d\n", value);

    SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &value);
    printf("Desired Sample Buffers: %d\n", value);

    SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &value);
    printf("Desired Samples: %d\n", value);

    SDL_GL_GetAttribute(SDL_GL_BUFFER_SIZE, &value);
    printf("Desired Buffer Size: %d\n", value);

    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
    printf("Desired GL Context Major Version: %d\n", value);

    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
    printf("Desired GL Context Minor Version: %d\n", value);
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }
    
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);

    // Set some OpenGL attributes before creating the window
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);  // No alpha channel
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 24);  // 8 bits each for R, G, B

    // Create a window with an OpenGL context
    SDL_Window* window = SDL_CreateWindow("SDL OpenGL Config",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          0, 0,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window) {
        fprintf(stderr, "Failed to create SDL window: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Attempt to create an OpenGL context associated with the window
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        fprintf(stderr, "Failed to create OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Context creation was successful, print the actual config
    print_desired_sdl_opengl_config();

    // Cleanup
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
