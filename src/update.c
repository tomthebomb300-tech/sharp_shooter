#include <stdio.h>

#include "update.h"
#include "types.h"

void moveCamera(Game *game){
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

}

void update(Game *game){
    moveCamera(game);
}