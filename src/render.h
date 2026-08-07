#ifndef RENDER_H
#define RENDER_H

#include <GL/gl.h>

#include "types.h"

void drawCube(Cube cube);
void drawMap();
void renderCamera(Camera camera);
void render(HDC CLIENT_AREA_HANDLE, Game *game);
void setupGraphics(HDC CLIENT_AREA_HANDLE);

#endif