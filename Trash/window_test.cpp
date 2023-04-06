#include <stdio.h>
#include <math.h>
#include <windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "gdi32.lib")

#define M_PI 3.14159265358979323846

float grad_to_rad(float grd)
{
    return ((M_PI / 180.0) * grd);
}

float rad_to_grad(float rd)
{
    return ((180.0 / M_PI) * rd);
}

POINT Point;

// система координат
struct coordinate_system
{
    int center_x, center_y;
    int axe_x_x, axe_x_y;
    int axe_y_x, axe_y_y;
    int axe_z_x, axe_z_y;

    coordinate_system()
    {
        center_x = 200;
        center_y = 200;
        set_axes();
    }
    void set_axes()
    {
        axe_x_x = 300;
        axe_x_y = 200;
        axe_y_x = 200;
        axe_y_y = 100;
        axe_z_x = 240;
        axe_z_y = 100;
    }

    void draw_axes(HDC hdc)
    {
        MoveToEx(hdc, center_x, center_y, &Point);
        LineTo(hdc, axe_x_x, axe_x_y);

        MoveToEx(hdc, center_x, center_y, &Point);
        LineTo(hdc, axe_y_x, axe_y_y);

        MoveToEx(hdc, center_x, center_y, &Point);
        LineTo(hdc, axe_z_x, axe_z_y);
    }
};

coordinate_system ty;

// куб
struct cube
{
    int cube_center_x, cube_center_y, cube_center_z;
    int dx, dy, dz;

    cube()
    {
        cube_center_x = 40;
        cube_center_y = 30;
        cube_center_z = 50;
        dx = 20;
        dy = 10;
        dz = 5;
    }

    void draw_cube(coordinate_system *cs, HDC hdc)
    {
        //  координаты вершин
        int v1x, v1y, v1z, v2x, v2y, v2z, v3x, v3y, v3z, v4x, v4y, v4z;
        int v5x, v5y, v5z, v6x, v6y, v6z, v7x, v7y, v7z, v8x, v8y, v8z;

        int vt1x, vt1y, vt1z, vt2x, vt2y, vt2z, vt3x, vt3y, vt3z, vt4x, vt4y, vt4z;
        int vt5x, vt5y, vt5z, vt6x, vt6y, vt6z, vt7x, vt7y, vt7z, vt8x, vt8y, vt8z;

        v1x = cube_center_x - dx, v1y = cube_center_y - dy, v1z = cube_center_z - dz,
        v2x = cube_center_x - dx, v2y = cube_center_y - dy, v2z = cube_center_z + dz,
        v3x = cube_center_x + dx, v3y = cube_center_y - dy, v3z = cube_center_z - dz,
        v4x = cube_center_x - dx, v4y = cube_center_y + dy, v4z = cube_center_z - dz;
        v5x = cube_center_x + dx, v5y = cube_center_y + dy, v5z = cube_center_z - dz,
        v6x = cube_center_x - dx, v6y = cube_center_y + dy, v6z = cube_center_z + dz,
        v7x = cube_center_x + dx, v7y = cube_center_y - dy, v7z = cube_center_z + dz,
        v8x = cube_center_x + dx, v8y = cube_center_y + dy, v8z = cube_center_z + dz;

        float snx = sin(grad_to_rad(2.0));
        float csx = cos(grad_to_rad(2.0));
        int oldx, oldy;
        oldx = v1x;
        oldy = v1y;
        v1x = csx * oldx - snx * oldy;
        v1y = snx * oldx + csx * oldy;
        oldx = v2x;
        oldy = v2y;
        v2x = csx * oldx - snx * oldy;
        v2y = snx * oldx + csx * oldy;
        oldx = v3x;
        oldy = v3y;
        v3x = csx * oldx - snx * oldy;
        v3y = snx * oldx + csx * oldy;
        oldx = v4x;
        oldy = v4y;
        v4x = csx * oldx - snx * oldy;
        v4y = snx * oldx + csx * oldy;
        oldx = v5x;
        oldy = v5y;
        v5x = csx * oldx - snx * oldy;
        v5y = snx * oldx + csx * oldy;
        oldx = v6x;
        oldy = v6y;
        v6x = csx * oldx - snx * oldy;
        v6y = snx * oldx + csx * oldy;
        oldx = v7x;
        oldy = v7y;
        v7x = csx * oldx - snx * oldy;
        v7y = snx * oldx + csx * oldy;
        oldx = v8x;
        oldy = v8y;
        v8x = csx * oldx - snx * oldy;
        v8y = snx * oldx + csx * oldy;

        int ADx, ADy, ADz;
        ADx = cs->axe_z_x - cs->center_x;
        ADy = cs->axe_z_y - cs->center_y;
        ADz = 100;

        float poAD = sqrt((float)ADx * ADx + ADy * ADy);
        float onepoAD = poAD / 100.0;

        float d_v1z = onepoAD * (float)v1z;
        float x_v1z = ((float)v1z / 100.0) * 40.0;
        float y_v1z = sqrt(d_v1z * d_v1z - x_v1z * x_v1z);

        int n_center_x_v1z = cs->center_x + x_v1z;
        int n_center_y_v1z = cs->center_y - y_v1z;

        float d_v2z = onepoAD * (float)v2z;
        float x_v2z = ((float)v2z / 100.0) * 40.0;
        float y_v2z = sqrt(d_v2z * d_v2z - x_v2z * x_v2z);

        int n_center_x_v2z = cs->center_x + x_v2z;
        int n_center_y_v2z = cs->center_y - y_v2z;
    }
};

cube d;

HINSTANCE hInst;
HWND hwndMain;

LRESULT APIENTRY WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    RECT rect;
    LPPOINT lpPoint;
    switch (message)
    {
    case WM_PAINT:
        hdc = GetDC(hwndMain);
        
        rect.left = 0;
        rect.top = 0;
        rect.right = 200;
        rect.bottom = 200;

        ty.set_axes();
        ty.draw_axes(hdc);

        ReleaseDC(hwndMain, hdc);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdSHow)
{
    MSG msg;
    WNDCLASSEX wcx;

    hInst = hInstance;

    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc = (WNDPROC)WndProc;
    wcx.cbClsExtra = 0;
    wcx.cbWndExtra = 0;
    wcx.hInstance = hInstance;
    wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wcx.lpszMenuName = "MainMenu";
    wcx.lpszClassName = "MainWClass";
    wcx.hIconSm = NULL;

    if (!RegisterClassEx(&wcx))
    {
        MessageBox(NULL, "!RegisterClassEx(&wcx)", "!RegisterClassEx(&wcx)", NULL);
    }

    hwndMain = CreateWindow("MainWClass", "Main Window",
                            WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
                            0, 0, 800, 800, (HWND)NULL, (HMENU)NULL, hInstance, NULL);
    if (!hwndMain)
    {
        MessageBox(NULL, "!hwndMain", "!hwndMain", NULL);
        return FALSE;
    }
    ShowWindow(hwndMain, SW_SHOW);
    UpdateWindow(hwndMain);

    BOOL fGotMessage;
    while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0 && fGotMessage != -1)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}