#include "game.h"

int main(int argc, char* argv[]) {
    (void)argc; // Suppress unused parameter warning
    (void)argv; // Suppress unused parameter warning

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    int running = 1;

    initSDL(&window, &renderer);

    createLabyrinth(); // Generate the labyrinth before starting the game loop

    while (running) {
        handleEvents(&running);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the 3D scene
        castRays(renderer);

        // Draw the mini-map
        drawMiniMap(renderer);

        SDL_RenderPresent(renderer);
    }

    cleanup(window, renderer);
    return 0;
}
