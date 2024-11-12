#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

// Player Structure
typedef struct {
    float x, y;  // Player position
    float angle; // Player angle
} Player;

// Global Player
extern Player player;

// Function Prototypes
void movePlayer(const Uint8* keystate);

#endif // PLAYER_H
