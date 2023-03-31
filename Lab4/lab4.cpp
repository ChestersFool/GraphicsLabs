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
    float x, y;
    x = p1.x * distanceCPoint(p1, camera) / p1.z;
    y = p1.y * distanceCPoint(p1, camera) / p1.z;
    MoveToEx(hdc, x + camera.x, y + camera.y, NULL);
    x = p2.x * distanceCPoint(p2, camera) / p2.z;
    y = p2.y * distanceCPoint(p2, camera) / p2.z;
    LineTo(hdc, x + camera.x, y + camera.y);
}

// void drawLine(CPoint p1, CPoint p2, CPoint camera)
// {
//     float x, y;
//     x = p1.x / distanceCPoint(p1, camera) * p1.z;
//     y = p1.y / distanceCPoint(p1, camera) * p1.z;
//     MoveToEx(hdc, x + camera.x, y + camera.y, NULL);
//     x = p2.x / distanceCPoint(p2, camera) * p2.z;
//     y = p2.y / distanceCPoint(p2, camera) * p2.z;
//     LineTo(hdc, x + camera.x, y + camera.y);
// }

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
}

int main()
{
    std::getchar();
    const float Z = 50;

    SelectObject(hdc, GetStockObject(WHITE_PEN));
    SelectObject(hdc, GetStockObject(NULL_BRUSH));

    //
    //
    // CPoint camera(0, 0, 0), camera2(100, 100, 0);
    // CRectangle first(CPoint(100, 100, Z), CPoint(120, 150, Z), CPoint(170, 150, Z), CPoint(150, 100, Z), camera), second(CPoint(100, 100, Z), CPoint(120, 150, Z), CPoint(170, 150, Z), CPoint(150, 100, Z), camera2);

    // drawRectangle(first);
    // HPEN myPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    // SelectObject(hdc, myPen);

    // drawRectangle(second);
    //
    //

    CPoint camera(125, 125, 0), camera2(250, 125, 0);
    C3DRectangle first(CPoint(100, 100, Z), CPoint(100, 150, Z), CPoint(150, 150, Z), CPoint(150, 100, Z), CPoint(100, 100, Z + 50), CPoint(100, 150, Z + 50), CPoint(150, 150, Z + 50), CPoint(150, 100, Z + 50), camera);

    draw3DRectangle(first);

    first.setCamera(camera2);
    draw3DRectangle(first);

    std::getchar();
    std::getchar();
    return 0;
}