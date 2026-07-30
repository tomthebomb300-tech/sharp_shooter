#include <GL/gl.h>

#include "render.h"
#include "types.h"


void drawCube(Cube cube){
    Coordinates c = cube.coordinates;
    Dimensions d = cube.dimensions;
    Colour colour = cube.colour;

    glRotatef(0.005f, 1,1,0);

    //Front Face
    glBegin(GL_POLYGON);
    glColor3f(colour.red, colour.green, colour.blue);
    glVertex3f(c.x,         c.y,            c.z);   //LBF
    glVertex3f(c.x+d.width, c.y,            c.z);   //RBF
    glVertex3f(c.x+d.width, c.y+d.height,   c.z);   //RTF
    glVertex3f(c.x,         c.y+d.height,   c.z);   //LTF
    glEnd();
    
    //Back Face
    glBegin(GL_POLYGON);
    glColor3f(colour.red, colour.green, colour.blue);
    glVertex3f(c.x,         c.y,            c.z-d.depth);   //LBB
    glVertex3f(c.x+d.width, c.y,            c.z-d.depth);   //RBB
    glVertex3f(c.x+d.width, c.y+d.height,   c.z-d.depth);   //RTB
    glVertex3f(c.x,         c.y+d.height,   c.z-d.depth);   //LTB
    glEnd();

    //Right Face
    glBegin(GL_POLYGON);
    glColor3f(colour.red, colour.green, colour.blue);
    glVertex3f(c.x+d.width,     c.y,            c.z);           //RBF
    glVertex3f(c.x+d.width,     c.y,            c.z-d.depth);   //RBB
    glVertex3f(c.x+d.width,     c.y+d.height,   c.z-d.depth);   //RTB
    glVertex3f(c.x+d.width,     c.y+d.height,   c.z);           //RTF
    glEnd();

    //Left Face
    glBegin(GL_POLYGON);
    glColor3f(colour.red, colour.green, colour.blue);
    glVertex3f(c.x,     c.y,            c.z);           //LBF
    glVertex3f(c.x,     c.y,            c.z-d.depth);   //LBB
    glVertex3f(c.x,     c.y+d.height,   c.z-d.depth);   //LTB
    glVertex3f(c.x,     c.y+d.height,   c.z);           //LTF
    glEnd();

    //Top Face
    glBegin(GL_POLYGON);
    glColor3f(colour.red, colour.green, colour.blue);
    glVertex3f(c.x,             c.y+d.height,   c.z);           //LTF
    glVertex3f(c.x+d.width,     c.y+d.height,   c.z);           //RTF
    glVertex3f(c.x+d.width,     c.y+d.height,   c.z-d.depth);   //RTB
    glVertex3f(c.x,             c.y+d.height,   c.z-d.depth);   //LTB
    glEnd();

    //Bottom Face
    glBegin(GL_POLYGON);
    glColor3f(colour.red, colour.green, colour.blue);
    glVertex3f(c.x,             c.y,   c.z);           //LBF
    glVertex3f(c.x+d.width,     c.y,   c.z);           //RBF
    glVertex3f(c.x+d.width,     c.y,   c.z-d.depth);   //RBB
    glVertex3f(c.x,             c.y,   c.z-d.depth);   //LBB
    glEnd();
}

void drawMap(){
    Cube cube = {
        .coordinates = (Coordinates){0.0f, 0.0f, 0.0f},
        .dimensions = (Dimensions){0.25f, 0.25f, 0.25f},
        .colour = (Colour){1.0f, 0.0f, 0.0f}
    };    
    drawCube(cube);
}

void render(HDC CLIENT_AREA_HANDLE){
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();

    drawMap();

    SwapBuffers(CLIENT_AREA_HANDLE);
}

void setupGraphics(HDC CLIENT_AREA_HANDLE){
    PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32};
    int format = ChoosePixelFormat(CLIENT_AREA_HANDLE, &pfd);
    SetPixelFormat(CLIENT_AREA_HANDLE, format, &pfd);
    HGLRC glrc = wglCreateContext(CLIENT_AREA_HANDLE);
    wglMakeCurrent(CLIENT_AREA_HANDLE, glrc);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}