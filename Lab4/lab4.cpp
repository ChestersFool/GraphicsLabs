#include <iostream>
#include <Windows.h>
#include <stdint.h>
#include <cmath>

#include <chrono>
#include <thread>

using std::cout, std::cin;

const double PI = 3.1415926535897932384;
const int WINDOW_SIZE = 800;

class CPoint
{
public:
    float x, y, z;

    CPoint() = default;
    CPoint(float x, float y, float z) : x(x), y(y), z(z) {}
};

class C3DRectangle
{
public:
    CPoint p1, p2, p3, p4, p5, p6, p7, p8;
    CPoint camera;

    C3DRectangle() = default;
    C3DRectangle(CPoint p1, CPoint p2, CPoint p3, CPoint p4, CPoint p5, CPoint p6, CPoint p7, CPoint p8, CPoint camera) : p1(p1), p2(p2), p3(p3), p4(p4), p5(p5), p6(p6), p7(p7), p8(p8), camera(camera) {}

    void setCamera(CPoint camera)
    {
        this->camera = camera;
    }
};

float distanceCPoints(CPoint p1, CPoint p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
}

void drawLine(CPoint p1, CPoint p2, CPoint camera, HDC hdc)
{
    float x, y;

    x = (p1.x - camera.x) * distanceCPoints(p1, camera) / fabs(p1.z - camera.z);
    y = (p1.y - camera.y) * distanceCPoints(p1, camera) / fabs(p1.z - camera.z);

    MoveToEx(hdc, x + camera.x + WINDOW_SIZE / 2, (y + camera.y) * (-1) + WINDOW_SIZE / 2, NULL);

    x = (p2.x - camera.x) * distanceCPoints(p2, camera) / fabs(p2.z - camera.z);
    y = (p2.y - camera.y) * distanceCPoints(p2, camera) / fabs(p2.z - camera.z);

    LineTo(hdc, x + camera.x + WINDOW_SIZE / 2, (y + camera.y) * (-1) + WINDOW_SIZE / 2);
}

void draw3DRectangle(C3DRectangle rect, HDC hdc)
{
    SelectObject(hdc, GetStockObject(WHITE_PEN));
    drawLine(rect.p1, rect.p2, rect.camera, hdc);
    drawLine(rect.p2, rect.p3, rect.camera, hdc);
    drawLine(rect.p4, rect.p1, rect.camera, hdc);
    drawLine(rect.p3, rect.p4, rect.camera, hdc);

    HPEN myPen1 = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    SelectObject(hdc, myPen1);
    drawLine(rect.p5, rect.p6, rect.camera, hdc);
    drawLine(rect.p6, rect.p7, rect.camera, hdc);
    drawLine(rect.p7, rect.p8, rect.camera, hdc);
    drawLine(rect.p8, rect.p5, rect.camera, hdc);

    HPEN myPen2 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    SelectObject(hdc, myPen2);
    drawLine(rect.p1, rect.p5, rect.camera, hdc);
    drawLine(rect.p2, rect.p6, rect.camera, hdc);
    drawLine(rect.p3, rect.p7, rect.camera, hdc);
    drawLine(rect.p4, rect.p8, rect.camera, hdc);

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            SetPixel(hdc, rect.camera.x + i + WINDOW_SIZE / 2, (rect.camera.y + j) * (-1) + WINDOW_SIZE / 2, RGB(255, 255, 255));
}

int main()
{
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);
    RECT window = {};

    HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD maxWindow = GetLargestConsoleWindowSize(out_handle);
    SMALL_RECT srctWindow = {0, 0, maxWindow.X - 50, maxWindow.Y - 15};
    SMALL_RECT minWindow = {0, 0, 0, 0};
    SetConsoleWindowInfo(out_handle, true, &minWindow);
    SetConsoleScreenBufferSize(out_handle, maxWindow);
    SetConsoleWindowInfo(out_handle, true, &srctWindow);

    std::getchar();

    CPoint camera(0, 0, 100);

    C3DRectangle first(CPoint(50, 50, 0), CPoint(50, 100, 0), CPoint(100, 100, 0), CPoint(100, 50, 0), CPoint(50, 50, 50), CPoint(50, 100, 50), CPoint(100, 100, 50), CPoint(100, 50, 50), camera);

    draw3DRectangle(first, hdc);

    ReleaseDC(hwnd, hdc);

    std::getchar();
    std::getchar();

    return 0;
}