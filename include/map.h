#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>


// Constants for the labyrinth
#define MAP_WIDTH 128
#define MAP_HEIGHT 128
#define CELL_SIZE 2 // Reduced cell size to make the mini-map smaller

// Map Data (declare as extern to share across files)
extern int map[MAP_WIDTH][MAP_HEIGHT];

// Function Prototypes
void createLabyrinth();
void drawMap(SDL_Renderer* renderer);

#endif // MAP_H
