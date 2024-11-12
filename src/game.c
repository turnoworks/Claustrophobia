#include "game.h"
#include "map.h" // Include map.h to access CELL_SIZE and other constants
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Normalize angle to keep it between 0 and 360 degrees
float normalizeAngle(float angle) {
    angle = fmod(angle, 360.0f);
    if (angle < 0) {
        angle += 360.0f;
    }
    return angle;
}

void initSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Initialization Error: %s\n", SDL_GetError());
        exit(1);
    }

    *window = SDL_CreateWindow("Ray Casting Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!*window) {
        printf("Window Creation Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        printf("Renderer Creation Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        exit(1);
    }
}

void handleEvents(int* running) {
    SDL_Event event;
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *running = 0;
        }
    }

    movePlayer(keystate);
}


void castRays(SDL_Renderer* renderer) {
    float angleStep = FOV / NUM_RAYS; // Angle increment per ray
    float startAngle = player.angle - (FOV / 2); // Starting angle for the first ray

    for (int i = 0; i < NUM_RAYS; i++) {
        float rayAngle = startAngle + i * angleStep;
        rayAngle = normalizeAngle(rayAngle); // Keep angle within 0-360 degrees

        // Calculate ray direction
        float rayX = cos(rayAngle * M_PI / 180.0f);
        float rayY = sin(rayAngle * M_PI / 180.0f);

        float distance = 0.0f;
        int hit = 0;

        while (distance < MAX_DEPTH && !hit) {
            distance += 0.1f; // Increase distance in small steps

            int mapX = (int)(player.x + rayX * distance);
            int mapY = (int)(player.y + rayY * distance);

            if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT) {
                if (map[mapX][mapY] == 1) {
                    hit = 1; // We hit a wall
                }
            }
        }

        // Perspective correction to reduce fish-eye effect
        float correctedDistance = distance * cos((rayAngle - player.angle) * M_PI / 180.0f);

        // Calculate the height of the wall slice
        int wallHeight = (int)(SCREEN_HEIGHT / correctedDistance);
        if (wallHeight > SCREEN_HEIGHT) wallHeight = SCREEN_HEIGHT; // Cap the wall height

        // Calculate the position of the top of the wall slice
        int wallTop = SCREEN_HEIGHT / 2 - wallHeight / 2;

        // Adjust the width of each wall slice to ensure they overlap slightly
        int wallSliceWidth = (int)(SCREEN_WIDTH / NUM_RAYS) + 1; // Add 1 to ensure overlap

        // Set the wall color and draw the filled rectangle
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Wall color
        SDL_Rect wallRect = {i * wallSliceWidth, wallTop, wallSliceWidth, wallHeight};
        SDL_RenderFillRect(renderer, &wallRect); // Draw the filled wall rectangle
    }
}


void drawMiniMap(SDL_Renderer* renderer) {
    // Set the background color of the mini-map
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Mini-map border/background color
    SDL_Rect borderRect = {0, 0, MAP_WIDTH * CELL_SIZE, MAP_HEIGHT * CELL_SIZE};
    SDL_RenderFillRect(renderer, &borderRect); // Draw the border/background

    // Draw the walls of the mini-map using the updated drawMap function
    drawMap(renderer);

    // Draw the player on the mini-map
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Player color (green)
    SDL_Rect playerRect = {
        (int)(player.x * CELL_SIZE) - 2, // Scale player x position
        (int)(player.y * CELL_SIZE) - 2, // Scale player y position
        4, 4 // Player size on the mini-map
    };
    SDL_RenderFillRect(renderer, &playerRect); // Draw the player
}


void cleanup(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
