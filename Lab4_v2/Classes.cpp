#pragma ONCE
#include <iostream>
#include <Windows.h>
#include <stdint.h>
#include <cmath>

#include <chrono>
#include <thread>

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
    CPoint point[8];

    C3DRectangle() = default;
    C3DRectangle(CPoint p1, CPoint p2, CPoint p3, CPoint p4, CPoint p5, CPoint p6, CPoint p7, CPoint p8)
    {
        point[0] = p1;
        point[1] = p2;
        point[2] = p3;
        point[3] = p4;
        point[4] = p5;
        point[5] = p6;
        point[6] = p7;
        point[7] = p8;
    }
};

float distanceCPoints(CPoint p1, CPoint p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
}

void drawLine(CPoint p1, CPoint p2, CPoint camera, HDC hdc, int WINDOW_SIZE)
{
    float x, y;

    x = (p1.x - camera.x) * distanceCPoints(p1, camera) / fabs(p1.z - camera.z);
    y = (p1.y - camera.y) * distanceCPoints(p1, camera) / fabs(p1.z - camera.z);

    MoveToEx(hdc, x + camera.x + WINDOW_SIZE / 2, (y + camera.y) * (-1) + WINDOW_SIZE / 2, NULL);

    x = (p2.x - camera.x) * distanceCPoints(p2, camera) / fabs(p2.z - camera.z);
    y = (p2.y - camera.y) * distanceCPoints(p2, camera) / fabs(p2.z - camera.z);

    LineTo(hdc, x + camera.x + WINDOW_SIZE / 2, (y + camera.y) * (-1) + WINDOW_SIZE / 2);
}

void draw3DRectangle(C3DRectangle rect, CPoint camera, HDC hdc, int WINDOW_SIZE)
{
    HPEN myPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    SelectObject(hdc, myPen);

    for (int i = 0; i < 4; i++)
    {
        drawLine(rect.point[i], rect.point[(i + 1) % 4], camera, hdc, WINDOW_SIZE);
        drawLine(rect.point[i], rect.point[i + 4], camera, hdc, WINDOW_SIZE);
        drawLine(rect.point[i + 4], rect.point[(i + 1) % 4 + 4], camera, hdc, WINDOW_SIZE);
    }

    for (int i = 0; i < 4; i++)

        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
                SetPixel(hdc, camera.x + i + WINDOW_SIZE / 2, (camera.y + j) * (-1) + WINDOW_SIZE / 2, RGB(255, 255, 255));
}

void drawAxis(HDC hdc, int WINDOW_SIZE)
{
    HPEN myPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(hdc, myPen);

    MoveToEx(hdc, WINDOW_SIZE / 2, 0, NULL);
    LineTo(hdc, WINDOW_SIZE / 2, WINDOW_SIZE);

    MoveToEx(hdc, 0, WINDOW_SIZE / 2, NULL);
    LineTo(hdc, WINDOW_SIZE, WINDOW_SIZE / 2);

    MoveToEx(hdc, WINDOW_SIZE, 0, NULL);
    LineTo(hdc, 0, WINDOW_SIZE);
}