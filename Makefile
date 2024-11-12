CC = gcc
CFLAGS = -Wall -Wextra -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lm
SRC = src/main.c src/game.c src/map.c src/player.c
INCLUDE = -Iinclude
OUT = raycasting

all:
	$(CC) $(CFLAGS) $(SRC) $(INCLUDE) -o $(OUT)

clean:
	rm -f $(OUT)
