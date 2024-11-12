#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "map.h"
#include "player.h"

// Screen dimensions
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

// Ray casting constants
#define FOV 60.0f // Field of View in degrees
#define NUM_RAYS 240 // Increased number of rays for higher resolution
#define MAX_DEPTH 20.0f // Maximum depth the rays will travel

// Function prototypes
void initSDL(SDL_Window** window, SDL_Renderer** renderer);
void handleEvents(int* running);
void castRays(SDL_Renderer* renderer);
void drawMiniMap(SDL_Renderer* renderer);
void cleanup(SDL_Window* window, SDL_Renderer* renderer);
float normalizeAngle(float angle);

#endif // GAME_H
