#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// VectorWar game logic headers
#include "vectorwar.h"
#include "ggpo_perfmon.h"

void HandleEvent(SDL_Event *event, bool &running) {
    switch (event->type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_p) {
                ggpoutil_perfmon_toggle();
            } else if (event->key.keysym.sym == SDLK_ESCAPE) {
                VectorWar_Exit();
                running = false;
            } else if (event->key.keysym.sym >= SDLK_F1 && event->key.keysym.sym <= SDLK_F12) {
                VectorWar_DisconnectPlayer(event->key.keysym.sym - SDLK_F1);
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
        exit(EXIT_FAILURE);
    }
    return window;
}

void RunMainLoop(SDL_Window *window) {
    bool running = true;
    SDL_Event event;

    Uint32 next_frame = SDL_GetTicks();
    const Uint32 frame_delay = 1000 / 60; // Target 60 FPS

    while (running) {
        // Poll events
        while (SDL_PollEvent(&event)) {
            HandleEvent(&event, running);
        }

        // Run game logic and render
        VectorWar_Idle(0);
        Uint32 now = SDL_GetTicks();
        if (now >= next_frame) {
            VectorWar_RunFrame(window);
            next_frame = now + frame_delay;
        }

        // Delay to maintain frame rate
        SDL_Delay(frame_delay / 2);
    }
}

void Syntax() {
    fprintf(stderr, "Syntax: vectorwar <local port> <num players> ('local' | <remote ip>:<remote port>)*\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        Syntax();
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window = CreateMainWindow("Vector War", 640, 480);

    int offset = 1, local_player = 0;
    unsigned short local_port = (unsigned short)atoi(argv[offset++]);
    int num_players = atoi(argv[offset++]);
    if (num_players <= 0 || argc < offset + num_players) {
        Syntax();
    }

    if (strcmp(argv[offset], "spectate") == 0) {
        char host_ip[128];
        unsigned short host_port;
        if (sscanf(argv[offset + 1], "%[^:]:%hu", host_ip, &host_port) != 2) {
            Syntax();
        }
        VectorWar_InitSpectator(window, local_port, num_players, host_ip, host_port);
    } else {
        GGPOPlayer players[GGPO_MAX_SPECTATORS + GGPO_MAX_PLAYERS];

        for (int i = 0; i < num_players; ++i) {
            const char *arg = argv[offset++];

            players[i].size = sizeof(players[i]);
            players[i].player_num = i + 1;
            if (strcmp(arg, "local") == 0) {
                players[i].type = GGPO_PLAYERTYPE_LOCAL;
                local_player = i;
                continue;
            }

            players[i].type = GGPO_PLAYERTYPE_REMOTE;
            if (sscanf(arg, "%[^:]:%hu", players[i].u.remote.ip_address, &players[i].u.remote.port) != 2) {
                Syntax();
            }
        }

        // Remaining are spectators
        int num_spectators = 0;
        while (offset < argc) {
            players[num_players + num_spectators].type = GGPO_PLAYERTYPE_SPECTATOR;
            if (sscanf(argv[offset++], "%[^:]:%hu",
                       players[num_players + num_spectators].u.remote.ip_address,
                       &players[num_players + num_spectators].u.remote.port) != 2) {
                Syntax();
            }
            num_spectators++;
        }

        VectorWar_Init(window, local_port, num_players, players, num_spectators);
    }

    RunMainLoop(window);
    VectorWar_Exit();

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
