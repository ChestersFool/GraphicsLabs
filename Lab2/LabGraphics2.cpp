#include <iostream>
#include <Windows.h>
#include <cmath>
#include <chrono>
#include <thread>

HWND hwnd = GetConsoleWindow();
HDC hdc = GetDC(hwnd);
RECT window = {};
const double PI = 3.1415926535897932384;

void drawPifagorsTree(int x, int y, int lenght, double radian, int depth)
{
    if (lenght <= 20)
        return;

    HPEN myPen = CreatePen(PS_SOLID, 9 - depth, RGB(0, 14 * depth + 40, 0));
    SelectObject(hdc, myPen);

    std::this_thread::sleep_for(std::chrono::milliseconds(35));

    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x + lenght * cos(radian + PI / 6), y - lenght * sin(radian + PI / 6));

    drawPifagorsTree(x + lenght * cos(radian + PI / 6), y - lenght * sin(radian + PI / 6), lenght / 1.3, radian + PI / 6, depth + 1);

    SelectObject(hdc, myPen);

    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x + lenght * cos(radian - PI / 6), y - lenght * sin(radian - PI / 6));

    drawPifagorsTree(x + lenght * cos(radian - PI / 6), y - lenght * sin(radian - PI / 6), lenght / 1.3, radian - PI / 6, depth + 1);

    DeleteObject(myPen);
}

int main()
{
    HPEN myPen = CreatePen(PS_SOLID, 9, RGB(0, 40, 0));
    SelectObject(hdc, myPen);

    int x = 1000, y = 1050, lenght = 250;
    double radian = PI / 2;
    std::getchar();

    MoveToEx(hdc, x, y, NULL);
    y -= lenght * sin(radian);
    LineTo(hdc, x, y);

    lenght /= 1.3;

    drawPifagorsTree(x, y, lenght, radian, 1);

    ReleaseDC(hwnd, hdc);

    std::cin >> x;
    return 0;
}
