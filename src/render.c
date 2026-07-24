#include <GL/gl.h>

#include "render.h"

void render(HDC CLIENT_AREA_HANDLE){
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(0.005f, 1.0f, 1.0f, 0.0f);

    //Back Face Cube
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f); //RED
    glVertex3f(0.5f, 0.5f, -0.5f);//TR
    glVertex3f(-0.5f, 0.5f, -0.5f);//TL
    glVertex3f(-0.5f, -0.5f, -0.5f);//BL
    glVertex3f(0.5f, -0.5f, -0.5f);//BR
    glEnd();

    //Front Face Cube
    glBegin(GL_POLYGON);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();

    //Left Face Cube
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f); //GREEN
    glVertex3f(-0.5f, 0.5f, 0.5f);//TLF
    glVertex3f(-0.5f, -0.5f, 0.5f);//BLF
    glVertex3f(-0.5f, -0.5f, -0.5f);//BLB
    glVertex3f(-0.5f, 0.5f, -0.5f);//TLB
    glEnd();

    //Right Face Cube
    glBegin(GL_POLYGON);
    glVertex3f(0.5f, 0.5f, 0.5f);//TRF
    glVertex3f(0.5f, -0.5f, 0.5f);//BRF
    glVertex3f(0.5f, -0.5f, -0.5f);//BRB
    glVertex3f(0.5f, 0.5f, -0.5f);//TRB
    glEnd();

    //Top Face Cube
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 1.0f); //PINK
    glVertex3f(0.5f, 0.5f, 0.5f);//TRF
    glVertex3f(-0.5f, 0.5f, 0.5f);//TLF
    glVertex3f(-0.5f, 0.5f, -0.5f);//TLB
    glVertex3f(0.5f, 0.5f, -0.5f);//TRB
    glEnd();

    //Bottom Face Cube
    glBegin(GL_POLYGON);
    glVertex3f(0.5f, -0.5f, 0.5f);//BRF
    glVertex3f(-0.5f, -0.5f, 0.5f);//BLF
    glVertex3f(-0.5f, -0.5f, -0.5f);//BLB
    glVertex3f(0.5f, -0.5f, -0.5f);//BRB
    glEnd();




    glFlush();

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