#include <iostream>
#include <Windows.h>
#include <stdint.h>
#include <cmath>

#include <chrono>
#include <thread>

using std::cout, std::cin;

HWND hwnd = GetConsoleWindow();
HDC hdc = GetDC(hwnd);
RECT window = {};

const double PI = 3.1415926535897932384;

class CPoint
{
public:
    float x, y, z;

    CPoint() = default;
    CPoint(float x, float y, float z) : x(x), y(y), z(z) {}
};

class CRectangle
{
public:
    CPoint p1, p2, p3, p4;
    CPoint camera;

    CRectangle() = default;
    CRectangle(CPoint p1, CPoint p2, CPoint p3, CPoint p4, CPoint camera) : p1(p1), p2(p2), p3(p3), p4(p4), camera(camera) {}
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

float distanceCPoint(CPoint p1, CPoint p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
}

void drawLine(CPoint p1, CPoint p2, CPoint camera)
{
    float x, y, z, coef1 = distanceCPoint(p1, camera) * (p1.z - camera.z), coef2 = distanceCPoint(p2, camera) * (p2.z - camera.z);
    // x = (p1.x - camera.x) / distanceCPoint(p1, camera) * (p1.z - camera.z);
    // y = (p1.y - camera.y) / distanceCPoint(p1, camera) * (p1.z - camera.z);
    x = (p1.x - camera.x) * distanceCPoint(p1, camera) / (p1.z - camera.z);
    y = (p1.y - camera.y) * distanceCPoint(p1, camera) / (p1.z - camera.z);

    MoveToEx(hdc, x + camera.x, y + camera.y, NULL);
    // MoveToEx(hdc, camera.x + x / distanceCPoint(p1, camera) * (p1.z - camera.z), camera.y + y / distanceCPoint(p1, camera) * (p1.z - camera.z), NULL);

    // x = (p2.x - camera.x) / distanceCPoint(p2, camera) * (p2.z - camera.z);
    // y = (p2.y - camera.y) / distanceCPoint(p2, camera) * (p2.z - camera.z);
    x = (p2.x - camera.x) * distanceCPoint(p2, camera) / (p2.z - camera.z);
    y = (p2.y - camera.y) * distanceCPoint(p2, camera) / (p2.z - camera.z);

    LineTo(hdc, x + camera.x, y + camera.y);
    // LineTo(hdc, camera.x + x / distanceCPoint(p2, camera) * (p1.z - camera.z), camera.y + y / distanceCPoint(p2, camera) * (p1.z - camera.z));
}

void drawRectangle(CRectangle rect)
{
    drawLine(rect.p1, rect.p2, rect.camera);
    drawLine(rect.p2, rect.p3, rect.camera);
    drawLine(rect.p3, rect.p4, rect.camera);
    drawLine(rect.p4, rect.p1, rect.camera);
}

void draw3DRectangle(C3DRectangle rect)
{
    SelectObject(hdc, GetStockObject(WHITE_PEN));
    drawLine(rect.p1, rect.p2, rect.camera);
    drawLine(rect.p2, rect.p3, rect.camera);
    drawLine(rect.p4, rect.p1, rect.camera);
    HPEN myPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    SelectObject(hdc, myPen);
    drawLine(rect.p3, rect.p4, rect.camera);

    HPEN myPen1 = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    SelectObject(hdc, myPen1);
    drawLine(rect.p5, rect.p6, rect.camera);
    drawLine(rect.p6, rect.p7, rect.camera);
    drawLine(rect.p7, rect.p8, rect.camera);
    drawLine(rect.p8, rect.p5, rect.camera);

    HPEN myPen2 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    SelectObject(hdc, myPen2);
    drawLine(rect.p1, rect.p5, rect.camera);
    drawLine(rect.p2, rect.p6, rect.camera);
    drawLine(rect.p3, rect.p7, rect.camera);
    drawLine(rect.p4, rect.p8, rect.camera);

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            SetPixel(hdc, rect.camera.x + i, rect.camera.y + j, RGB(255, 255, 255));
}

int main()
{
    HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD maxWindow = GetLargestConsoleWindowSize(out_handle);
    SMALL_RECT srctWindow = {0, 0, maxWindow.X - 50, maxWindow.Y - 15};
    SMALL_RECT minWindow = {0, 0, 0, 0};
    SetConsoleWindowInfo(out_handle, true, &minWindow);
    SetConsoleScreenBufferSize(out_handle, maxWindow);
    SetConsoleWindowInfo(out_handle, true, &srctWindow);

    std::getchar();
    const float Z = 50;
    const int DISMOVEMENT = 200;

    CPoint camera(425 + DISMOVEMENT, 425, 0), camera2(475, 100, -400);

    C3DRectangle first(CPoint(400 + DISMOVEMENT, 400, Z), CPoint(400 + DISMOVEMENT, 450, Z), CPoint(450 + DISMOVEMENT, 450, Z), CPoint(450 + DISMOVEMENT, 400, Z), CPoint(400 + DISMOVEMENT, 400, Z + 50), CPoint(400 + DISMOVEMENT, 450, Z + 50), CPoint(450 + DISMOVEMENT, 450, Z + 50), CPoint(450 + DISMOVEMENT, 400, Z + 50), camera);

    draw3DRectangle(first);

    C3DRectangle second(CPoint(400, 400, Z), CPoint(400, 550, Z), CPoint(550, 550, Z), CPoint(550, 400, Z), CPoint(400, 400, Z + 50), CPoint(400, 550, Z + 50), CPoint(550, 550, Z + 50), CPoint(550, 400, Z + 50), camera2);
    draw3DRectangle(second);

    std::getchar();
    std::getchar();
    return 0;
}