#pragma once
#include <iostream>
#include <Windows.h>
#include <stdint.h>
#include <cmath>

#include <chrono>
#include <thread>

class CPoint
{
public:
    double x, y, z;

    CPoint() = default;
    CPoint(double x, double y, double z) : x(x), y(y), z(z) {}
};

class C2DRectangle
{
public:
    CPoint point[4];

    C2DRectangle() = default;
    C2DRectangle(CPoint p1, CPoint p2, CPoint p3, CPoint p4)
    {
        point[0] = p1;
        point[1] = p2;
        point[2] = p3;
        point[3] = p4;
    }
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

struct RotationMatrix
{
    double matrix[3][3];

    RotationMatrix() = default;
    RotationMatrix(double angle)
    {
        matrix[0][0] = cos(angle);
        matrix[0][1] = 0;
        matrix[0][2] = sin(angle);
        matrix[1][0] = 0;
        matrix[1][1] = 1;
        matrix[1][2] = 0;
        matrix[2][0] = -sin(angle);
        matrix[2][1] = 0;
        matrix[2][2] = cos(angle);
    }
};

double distanceCPoints(CPoint p1, CPoint p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
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

    DeleteObject(myPen);
}

void rorateX3DRectangle(C3DRectangle &rect, const double rad)
{
    for (int i = 0; i < 8; i++)
    {
        rect.point[i].x = rect.point[i].x;
        rect.point[i].y = (rect.point[i].y * cos(rad)) - (rect.point[i].z * sin(rad));
        rect.point[i].z = (rect.point[i].y * sin(rad)) + (rect.point[i].z * cos(rad));
    }
}

void rorateAntiX3DRectangle(C3DRectangle &rect, const double rad)
{
    for (int i = 0; i < 8; i++)
    {
        rect.point[i].x = rect.point[i].x;
        rect.point[i].y = (rect.point[i].y * cos(rad)) + (rect.point[i].z * sin(rad));
        rect.point[i].z = (-rect.point[i].y * sin(rad)) + (rect.point[i].z * cos(rad));
    }
}

void rorateY3DRectangle(C3DRectangle &rect, const double rad)
{
    for (int i = 0; i < 8; i++)
    {
        rect.point[i].x = (rect.point[i].x * cos(rad)) + (rect.point[i].z * sin(rad));
        rect.point[i].y = rect.point[i].y;
        rect.point[i].z = (-rect.point[i].x * sin(rad)) + (rect.point[i].z * cos(rad));
    }
}

void draw2DRectangle(C2DRectangle &rect, CPoint &camera, HDC hdc, int WINDOW_SIZE)
{
    POINT point[4] = {rect.point[0].x + camera.x + WINDOW_SIZE / 2, (rect.point[0].y + camera.y) * (-1) + WINDOW_SIZE / 2,
                      rect.point[1].x + camera.x + WINDOW_SIZE / 2, (rect.point[1].y + camera.y) * (-1) + WINDOW_SIZE / 2,
                      rect.point[2].x + camera.x + WINDOW_SIZE / 2, (rect.point[2].y + camera.y) * (-1) + WINDOW_SIZE / 2,
                      rect.point[3].x + camera.x + WINDOW_SIZE / 2, (rect.point[3].y + camera.y) * (-1) + WINDOW_SIZE / 2};
    Polygon(hdc, point, 4);
}

void sort2DRectangles(C2DRectangle rects[6], CPoint camera)
{
    C2DRectangle temp;
    double z1, z2;

    for (int k = 0; k < 5; k++)
        for (int i = 0; i < 5; i++)
        {
            z1 = z2 = 0;
            for (int j = 0; j < 4; j++)
            {
                z1 += distanceCPoints(rects[i].point[j], camera) / 4;
                z2 += distanceCPoints(rects[i + 1].point[j], camera) / 4;
            }
            // * from far to near
            if (z1 < z2)
            {
                temp = rects[i];
                rects[i] = rects[i + 1];
                rects[i + 1] = temp;
            }
        }
}

void draw3DRectangle(C3DRectangle rect1, CPoint camera, HDC hdc, int WINDOW_SIZE, bool transperent = false, bool toWhite = false)
{   
    C3DRectangle rect = rect1;
    for (int i = 0; i < 8; i++)
    {
        rect.point[i].x = int((rect.point[i].x - camera.x) * distanceCPoints(rect.point[i], camera) / fabs(rect.point[i].z - camera.z));
        rect.point[i].y = int((rect.point[i].y - camera.y) * distanceCPoints(rect.point[i], camera) / fabs(rect.point[i].z - camera.z));
    }

    C2DRectangle rects[6]{{rect.point[0], rect.point[1], rect.point[2], rect.point[3]},
                          {rect.point[4], rect.point[5], rect.point[6], rect.point[7]},
                          {rect.point[1], rect.point[2], rect.point[6], rect.point[5]},
                          {rect.point[0], rect.point[3], rect.point[7], rect.point[4]},
                          {rect.point[0], rect.point[1], rect.point[5], rect.point[4]},
                          {rect.point[2], rect.point[3], rect.point[7], rect.point[6]}};

    sort2DRectangles(rects, camera);

    for (int i = 0; i < 6; i++)
    {   
        HPEN myPen = CreatePen(PS_SOLID, 1, RGB(20 * i, 20 * i, 20 * i));
        HBRUSH myBrush = CreateSolidBrush(RGB(20 * i, 20 * i, 20 * i));

        SelectObject(hdc, myPen);
        SelectObject(hdc, myBrush);

        if(toWhite)
        {
            SelectObject(hdc, GetStockObject(WHITE_PEN));
            SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        }

        if(transperent)
            SelectObject(hdc, GetStockObject(NULL_BRUSH));

        draw2DRectangle(rects[i], camera, hdc, WINDOW_SIZE);

        DeleteObject(myPen);
        DeleteObject(myBrush);
    }

}

// void drawLine(CPoint p1, CPoint p2, CPoint camera, HDC hdc, int WINDOW_SIZE)
// {
//     double x, y;

//     x = (p1.x - camera.x) * distanceCPoints(p1, camera) / fabs(p1.z - camera.z);
//     y = (p1.y - camera.y) * distanceCPoints(p1, camera) / fabs(p1.z - camera.z);

//     MoveToEx(hdc, x + camera.x + WINDOW_SIZE / 2, (y + camera.y) * (-1) + WINDOW_SIZE / 2, NULL);

//     x = (p2.x - camera.x) * distanceCPoints(p2, camera) / fabs(p2.z - camera.z);
//     y = (p2.y - camera.y) * distanceCPoints(p2, camera) / fabs(p2.z - camera.z);

//     LineTo(hdc, x + camera.x + WINDOW_SIZE / 2, (y + camera.y) * (-1) + WINDOW_SIZE / 2);
// }

// void draw3DRectangle(C3DRectangle rect, CPoint camera, HDC hdc, int WINDOW_SIZE)
// {
//     HPEN myPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
//     HBRUSH myBrush = CreateSolidBrush(RGB(0, 0, 0));
//     SelectObject(hdc, myPen);
//     SelectObject(hdc, GetStockObject(BLACK_BRUSH));

//     for (int i = 0; i < 4; i++)
//         drawLine(rect.point[i], rect.point[(i + 1) % 4], camera, hdc, WINDOW_SIZE);

//     for (int i = 0; i < 4; i++)
//         drawLine(rect.point[i], rect.point[i + 4], camera, hdc, WINDOW_SIZE);

//     for (int i = 0; i < 4; i++)
//         drawLine(rect.point[i + 4], rect.point[(i + 1) % 4 + 4], camera, hdc, WINDOW_SIZE);

//     for (int i = 0; i < 4; i++)
//         for (int i = -1; i <= 1; i++)
//             for (int j = -1; j <= 1; j++)
//                 SetPixel(hdc, camera.x + i + WINDOW_SIZE / 2, (camera.y + j) * (-1) + WINDOW_SIZE / 2, RGB(255, 255, 255));
// }