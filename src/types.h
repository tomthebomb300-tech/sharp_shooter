#ifndef TYPES_H
#define TYPES_H

typedef enum GAMESTATE{
    GAME_STATE_PLAYING,
    GAME_STATE_PAUSED,
    GAME_STATE_OVER
} GAMESTATE;

typedef enum key{
    KEY_W,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_UP,
    KEY_DOWN,
    KEY_ESC,
    KEY_LEFTCLICK
} KEY;

typedef struct Coordinates3{
    float x;
    float y;
    float z;
} Coordinates3;

typedef struct Coordinates2{
    float x;
    float y;
} Coordinates2;

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
    Coordinates3 coordinates;
    Dimensions dimensions;
    Colour colour;
} Cube;

typedef struct Camera{
    Coordinates3 coordinates;
    Coordinates3 viewingDirection;
    float yaw;
    float pitch;
    float FOV;
    float aspectRatio;
    float zNear;
    float zFar;
    float speed;
    float sensitivity;
} Camera;

typedef struct Game{
    GAMESTATE gameState;
    Camera camera;
    int key_down[8];
    Coordinates2 mouseCoords;
}Game;

#endif