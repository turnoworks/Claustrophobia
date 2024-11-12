#include "player.h"
#include "map.h" // Include map to check for collisions
#include <math.h>

Player player = {1.5f, 1.5f, 0.0f}; // Initial player position in the open area


void movePlayer(const Uint8* keystate) {
    const float moveSpeed = 0.01f;  // Adjusted movement speed
    const float rotateSpeed = 0.1f; // Adjusted rotation speed

    float newX = player.x;
    float newY = player.y;

    if (keystate[SDL_SCANCODE_UP]) {
        newX += cos(player.angle * M_PI / 180.0f) * moveSpeed;
        newY += sin(player.angle * M_PI / 180.0f) * moveSpeed;
    }
    if (keystate[SDL_SCANCODE_DOWN]) {
        newX -= cos(player.angle * M_PI / 180.0f) * moveSpeed;
        newY -= sin(player.angle * M_PI / 180.0f) * moveSpeed;
    }

    // Collision detection
    if (newX >= 0 && newX < MAP_WIDTH && map[(int)newX][(int)player.y] == 0) {
        player.x = newX;
    }
    if (newY >= 0 && newY < MAP_HEIGHT && map[(int)player.x][(int)newY] == 0) {
        player.y = newY;
    }

    if (keystate[SDL_SCANCODE_LEFT]) {
        player.angle -= rotateSpeed;
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
        player.angle += rotateSpeed;
    }

    if (player.angle < 0) {
        player.angle += 360;
    } else if (player.angle >= 360) {
        player.angle -= 360;
    }
}



