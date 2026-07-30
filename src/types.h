#ifndef TYPES_H
#define TYPES_H

typedef enum GAMESTATE{
    GAME_STATE_PLAYING,
    GAME_STATE_PAUSED,
    GAME_STATE_OVER
} GAMESTATE;

typedef struct Coordinates{
    float x;
    float y;
    float z;
} Coordinates;

typedef struct Dimensions{
    float width;
    float height;
    float depth;
} Dimensions;

typedef struct Colour{
    float red;
    float green;
    float blue;
} Colour;

typedef struct Cube{
    Coordinates coordinates;
    Dimensions dimensions;
    Colour colour;
} Cube;

typedef struct Game{
    GAMESTATE gameState;
}Game;

#endif