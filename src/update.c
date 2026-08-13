#include <stdio.h>
#include <math.h>

#include "update.h"
#include "types.h"

void moveCameraXYZ(Game *game){
    if(game->key_down[KEY_W]){
        game->camera.coordinates.z -= game->camera.speed;
    }
    if(game->key_down[KEY_A]){
        game->camera.coordinates.x -= game->camera.speed;
    }
    if(game->key_down[KEY_S]){
        game->camera.coordinates.z += game->camera.speed;
    }
    if(game->key_down[KEY_D]){
        game->camera.coordinates.x += game->camera.speed;
    }
    if(game->key_down[KEY_UP]){
        game->camera.coordinates.y += game->camera.speed;
    }
    if(game->key_down[KEY_DOWN]){
        game->camera.coordinates.y -= game->camera.speed;
    }
}

void moveCameraPitchYaw(Game *game){
    //getting current mouse coords * sensitivity and converting the value to radians.
    game->camera.yaw = (game->mouseCoords.x * game->camera.sensitivity) * (3.14159265f / 180.0f);
    game->camera.pitch = (game->mouseCoords.y * game->camera.sensitivity) * (3.14159265f / 180.0f);

    //Assume hypotenuse = 1 
    //Looking down at XZ plane first, calculate X,Z directional vectors.               
    float directionX =  cosf(game->camera.yaw);
    float directionZ =  sinf(game->camera.yaw); 

    //Calculate Y directional vector
    float directionY =  sinf(game->camera.pitch);

    //Since including directional vector Y, the projection may get smaller or larger on X,Z plane.
    directionX *= cosf(game->camera.pitch);
    directionZ *= cosf(game->camera.pitch);

    game->camera.viewingDirection = (Coordinates3){.x = directionX, .y = directionY, .z = directionZ};
}

void update(Game *game){
    moveCameraXYZ(game);
    moveCameraPitchYaw(game);
}