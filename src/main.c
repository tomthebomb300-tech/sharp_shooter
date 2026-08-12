#include <stdio.h>
#include <windows.h>
#include <windowsx.h>

#include "update.h"
#include "render.h"
#include "types.h"

const char WINDOW_CLASS_NAME[] = "window";
HWND WINDOW_HANDLE;
HDC CLIENT_AREA_HANDLE;
Game *game;
POINT centre;
RAWINPUTDEVICE rid;

const int CLIENT_AREA_HEIGHT = 800;
const int CLIENT_AREA_WIDTH = 800;
const int WINDOW_HEIGHT = CLIENT_AREA_HEIGHT + 20;
const int WINDOW_WIDTH = CLIENT_AREA_WIDTH + 43;

void setupGame(){
    centre.x = WINDOW_WIDTH/2;
    centre.y = WINDOW_HEIGHT/2;
    
    ClientToScreen(WINDOW_HANDLE, &centre);
    SetCursorPos(centre.x, centre.y);

    rid.usUsagePage = 0x01; //Generic Desktop Controls
    rid.usUsage = 0x02;     //Mouse
    rid.dwFlags = 0;
    rid.hwndTarget = WINDOW_HANDLE;
    RegisterRawInputDevices(&rid, 1, sizeof(rid));
    
    game = malloc(sizeof(Game));
    game->mouseCoords.x = centre.x;
    game->mouseCoords.y = centre.y;

    game->key_down[KEY_W] = 0;
    game->key_down[KEY_A] = 0;
    game->key_down[KEY_S] = 0;
    game->key_down[KEY_D] = 0;
    game->key_down[KEY_UP] = 0;
    game->key_down[KEY_DOWN] = 0;
    game->key_down[KEY_ESC] = 0;
    game->key_down[KEY_LEFTCLICK] = 0;

    game->gameState = GAME_STATE_PLAYING;

    //Camera
    Coordinates3 c = {0.0f, 0.25f, 0.0f};
    Camera camera = {
        .coordinates = c,
        .yaw = 0.0f,
        .pitch = 0.0f,
        .FOV = 60.0f,
        .aspectRatio = CLIENT_AREA_HEIGHT/CLIENT_AREA_WIDTH, 
        .zNear = 0.1f,
        .zFar = 100.0f,
        .speed = 0.0001f,
        .sensitivity = 1.0f
    };
    game->camera = camera;
}

void keyDown(WPARAM key){
    if(key == 'W'){game->key_down[KEY_W] = 1;}
    else if(key == 'A'){game->key_down[KEY_A] = 1;}
    else if(key == 'S'){game->key_down[KEY_S] = 1;}
    else if(key == 'D'){game->key_down[KEY_D] = 1;}
    else if(key == VK_UP){game->key_down[KEY_UP] = 1;}
    else if(key == VK_DOWN){game->key_down[KEY_DOWN] = 1;}
    else if(key == VK_ESCAPE){game->key_down[KEY_ESC] = 1;}
    else if(key == VK_LBUTTON){game->key_down[KEY_LEFTCLICK] = 1;}
}

void keyUp(WPARAM key){
    if(key == 'W'){game->key_down[KEY_W] = 0;}
    else if(key == 'A'){game->key_down[KEY_A] = 0;}
    else if(key == 'S'){game->key_down[KEY_S] = 0;}
    else if(key == 'D'){game->key_down[KEY_D] = 0;}
    else if(key == VK_UP){game->key_down[KEY_UP] = 0;}
    else if(key == VK_DOWN){game->key_down[KEY_DOWN] = 0;}
    else if(key == VK_ESCAPE){game->key_down[KEY_ESC] = 0;}
    else if(key == VK_LBUTTON){game->key_down[KEY_LEFTCLICK] = 0;}
}

void mouseMove(int dx, int dy){
    game->mouseCoords.x += dx;
    game->mouseCoords.y += dy;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
        case WM_LBUTTONDOWN:
            keyDown(wParam);
        break;
        case WM_LBUTTONUP:
            keyUp(wParam);
        break;
        case WM_KEYDOWN:
            keyDown(wParam);
        break;
        case WM_KEYUP:
            keyUp(wParam);
        break;
        case WM_INPUT:
            UINT size = 0;
            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER));

            BYTE *buffer = malloc(size);
            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, buffer, &size, sizeof(RAWINPUTHEADER));

            RAWINPUT *raw = (RAWINPUT *)buffer;
            if(raw->header.dwType == RIM_TYPEMOUSE){
                int dx = raw->data.mouse.lLastX;
                int dy = raw->data.mouse.lLastY;
                mouseMove(dx, dy);
        break;
        }
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    WNDCLASSEX wc;
    MSG Msg;

    HBRUSH backgroundBrush = CreateSolidBrush(RGB(0,0,0));

    //Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = backgroundBrush;
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = WINDOW_CLASS_NAME;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    DeleteObject(backgroundBrush);

    if(!RegisterClassEx(&wc)){
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    //Creating the Window
    WINDOW_HANDLE = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        WINDOW_CLASS_NAME,
        "Sharp Shooter",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL, NULL, hInstance, NULL);

    if(WINDOW_HANDLE == NULL){
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(WINDOW_HANDLE, nCmdShow);
    UpdateWindow(WINDOW_HANDLE);

    setupGame();

    CLIENT_AREA_HANDLE = GetDC(WINDOW_HANDLE);
    setupGraphics(CLIENT_AREA_HANDLE);
    
    int run = 1;
    while(run){
        //The Message Loop
        while(PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)){
            if(Msg.message == WM_QUIT)
                run = 0;
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }
        update(game);
        render(CLIENT_AREA_HANDLE, game);
    }
    ReleaseCapture();
    return Msg.wParam;
}