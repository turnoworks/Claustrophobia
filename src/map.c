#include "map.h"
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time()
#include <SDL2/SDL.h>

// Directions for movement: right, left, down, up
int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int map[MAP_WIDTH][MAP_HEIGHT];

// Function to shuffle the directions array to introduce randomness
void shuffleDirections() {
    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        int tempX = directions[i][0];
        int tempY = directions[i][1];
        directions[i][0] = directions[j][0];
        directions[i][1] = directions[j][1];
        directions[j][0] = tempX;
        directions[j][1] = tempY;
    }
}

// Recursive function to generate the maze using Depth-First Search
void generateMaze(int x, int y) {
    map[x][y] = 0; // Mark the current cell as a path

    // Shuffle the directions to randomize the maze
    shuffleDirections();

    // Try to move in each direction
    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0] * 2;
        int newY = y + directions[i][1] * 2;

        // Check if the new cell is within bounds and has not been visited
        if (newX > 0 && newX < MAP_WIDTH - 1 && newY > 0 && newY < MAP_HEIGHT - 1 && map[newX][newY] == 1) {
            // Carve a path between the current cell and the new cell
            map[x + directions[i][0]][y + directions[i][1]] = 0;
            generateMaze(newX, newY); // Recursively generate the maze from the new cell
        }
    }
}

// Function to create additional connections in the maze to prevent dead ends
void addExtraConnections() {
    for (int y = 1; y < MAP_HEIGHT - 1; y += 2) {
        for (int x = 1; x < MAP_WIDTH - 1; x += 2) {
            if (map[x][y] == 0) { // If the current cell is a path
                // Randomly break one wall around this cell to create more connections
                int direction = rand() % 4;
                int newX = x + directions[direction][0];
                int newY = y + directions[direction][1];
                if (newX > 0 && newX < MAP_WIDTH - 1 && newY > 0 && newY < MAP_HEIGHT - 1) {
                    map[newX][newY] = 0; // Break the wall to create a connection
                }
            }
        }
    }
}

// Function to create the labyrinth
void createLabyrinth() {
    // Initialize the map with walls
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map[x][y] = 1; // Fill the entire map with walls
        }
    }

    srand(time(NULL)); // Seed the random number generator

    // Start maze generation from (1, 1)
    generateMaze(1, 1);

    // Add extra connections to ensure there are no isolated areas
    addExtraConnections();

    // Ensure entry and exit points are open
    map[1][1] = 0; // Entry point
    map[MAP_WIDTH - 2][MAP_HEIGHT - 2] = 0; // Exit point

    // Additional check: Make sure the player's starting position is open
    map[1][1] = 0; // Ensure the starting position is open
}

// Function to draw the mini-map with continuous, solid wall lines
void drawMap(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Wall color (black)

    // Loop through the map and draw the walls as solid rectangles
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[x][y] == 1) { // If the cell is a wall
                SDL_Rect rect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
                SDL_RenderFillRect(renderer, &rect); // Fill the rectangle to make it solid
            }
        }
    }
}
