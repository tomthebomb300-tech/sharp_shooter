#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

#include "render.h"
#include "types.h"


void drawCube(Cube cube){
    Coordinates3 c = cube.coordinates;
    Dimensions d = cube.dimensions;
    Colour colour = cube.colour;

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
        .coordinates = (Coordinates3){0.0f, 0.0f, 0.0f},
        .dimensions = (Dimensions){0.25f, 0.5f, 0.25f},
        .colour = (Colour){1.0f, 0.0f, 0.0f}
    };    
    drawCube(cube);
}

void renderCamera(Camera camera){
    //Projection matrix mimics human vision.
    glMatrixMode(GL_PROJECTION);    //next commands modify projection matrix
    glLoadIdentity();               //Reset current matrix, undefined behaviour if not done
    gluPerspective(                 //Creating projection matrix
        camera.FOV,                 //FOV in degrees   
        camera.aspectRatio,         //Aspect ratio -> width/height
        camera.zNear,               //render no closer
        camera.zFar                 //render no further
    );

    //ModelView matric controls positioning of 3D models and camera.
    glMatrixMode(GL_MODELVIEW);         //Next commands modify ModelView matrix
    glLoadIdentity();                   //Reset current matrix

    glRotatef(camera.pitch, 1.0f, 0.0f, 0.0f);
    glRotatef(camera.yaw, 0.0f, 1.0f, 0.0f);

    Coordinates3 c = camera.coordinates;
    glTranslatef(-c.x,-c.y,-c.z);       
    // printf("x: %f, y: %f, z: %f  -- P: %f, Y: %f\n", c.x, c.y, c.z, camera.pitch, camera.yaw);
}

void render(HDC CLIENT_AREA_HANDLE, Game *game){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear colour buffer and depth buffer.
    
    renderCamera(game->camera);
    
    drawMap();
    
    SwapBuffers(CLIENT_AREA_HANDLE);
}

void setupGraphics(HDC CLIENT_AREA_HANDLE){
    PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32};
    int format = ChoosePixelFormat(CLIENT_AREA_HANDLE, &pfd);
    SetPixelFormat(CLIENT_AREA_HANDLE, format, &pfd);
    HGLRC glrc = wglCreateContext(CLIENT_AREA_HANDLE);
    wglMakeCurrent(CLIENT_AREA_HANDLE, glrc);
    
    glEnable(GL_DEPTH_TEST);                            //Keep track of every pixel distance from camera
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}