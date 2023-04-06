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
    float x, y;

    CPoint() = default;
    CPoint(float x, float y) : x(x), y(y) {}
};

struct PointForRotate
{
    float x, y, koef = 1;

    PointForRotate() = default;
    PointForRotate(float x, float y) : x(x), y(y) {}
};

struct RotationMatrix
{
    float matrix[3][3];

    RotationMatrix() = default;
    RotationMatrix(float angle)
    {
        matrix[0][0] = cos(angle);
        matrix[0][1] = sin(angle);
        matrix[0][2] = 0;
        matrix[1][0] = -sin(angle);
        matrix[1][1] = cos(angle);
        matrix[1][2] = 0;
        matrix[2][0] = 0;
        matrix[2][1] = 0;
        matrix[2][2] = 1;
    }
};

int main()
{
    HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD maxWindow = GetLargestConsoleWindowSize(out_handle);
    SMALL_RECT srctWindow = {0, 0, maxWindow.X - 50, maxWindow.Y - 15};
    SMALL_RECT minWindow = {0, 0, 0, 0};
    SetConsoleWindowInfo(out_handle, true, &minWindow);
    SetConsoleScreenBufferSize(out_handle, maxWindow);
    SetConsoleWindowInfo(out_handle, true, &srctWindow);

    SelectObject(hdc, GetStockObject(WHITE_PEN));

    std::getchar();

    CPoint rec[4]{{100, 100}, {100, 200}, {200, 200}, {200, 100}};

    for (int i = 0; i < 4; i++)
    {
        MoveToEx(hdc, rec[i].x, rec[i].y, NULL);
        LineTo(hdc, rec[(i + 1) % 4].x, rec[(i + 1) % 4].y);
    }

    // ( x    y )    
    //      *
    // ( cos(a) -sin(a) ) 
    // ( sin(a) cos(a)  )    
    RotationMatrix m(PI / 100);
    int result[2], coordsPoint[2];

    // * FOR 4 POINTS
    for (int k = 0; k < 4; k++)
    {
        for (int i = 0; i < 2; i++)
            result[i] = 0;

        // * COPY OF COORDS
        coordsPoint[0] = rec[k].x;
        coordsPoint[1] = rec[k].y;

        // * MULTIPLY
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                result[i] += coordsPoint[j] * m.matrix[j][i];

        // * SET NEW COORDS
        rec[k].x = result[0];
        rec[k].y = result[1];
    }

    for (int i = 0; i < 4; i++)
    {
        MoveToEx(hdc, rec[i].x, rec[i].y, NULL);
        LineTo(hdc, rec[(i + 1) % 4].x, rec[(i + 1) % 4].y);
    }

    ReleaseDC(hwnd, hdc);

    std::getchar();
    std::getchar();
    return 0;
}