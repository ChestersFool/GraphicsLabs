#include <iostream>
#include <Windows.h>
#include <cmath>

HWND hwnd = GetConsoleWindow();
HDC hdc = GetDC(hwnd);
RECT window = {};
const double PI = 3.1415926535897932384;

//tjj
void drawPifagorsTree(int x, int y, int l, double radian)
{
    if (l <= 20)
        return;

    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x + l * cos(radian + PI / 6), y - l * sin(radian + PI / 6));

    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x + l * cos(radian - PI / 6), y - l * sin(radian - PI / 6));

    drawPifagorsTree(x + l * cos(radian + PI / 6), y - l * sin(radian + PI / 6), l / 1.3, radian + PI / 6);
    drawPifagorsTree(x + l * cos(radian - PI / 6), y - l * sin(radian - PI / 6), l / 1.3, radian - PI / 6);
}

int main()
{
    SelectObject(hdc, GetStockObject(WHITE_PEN));
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));

    int x = 1000, y = 900, l = 200;
    double radian = PI / 2;
    std::getchar();

    MoveToEx(hdc, x, y, NULL);
    y -= l * sin(radian);
    LineTo(hdc, x, y);

    l /= 1.3;

    drawPifagorsTree(x, y, l, radian);

    ReleaseDC(hwnd, hdc);

    std::cin >> x;
    return 0;
}
