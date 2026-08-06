#include <stdio.h>

#include "update.h"
#include "types.h"

void moveCamera(Game *game){
    if(game->key_down[KEY_W]){
        printf("Forward\n");
    }
    if(game->key_down[KEY_A]){
        printf("Left\n");
        game->camera.coordinates.x -= game->camera.speed;
    }
    if(game->key_down[KEY_S]){
        printf("Back\n");
    }
    if(game->key_down[KEY_D]){
        printf("Right\n");
        game->camera.coordinates.x += game->camera.speed;
    }

}

void update(Game *game){
    moveCamera(game);
}