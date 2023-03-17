#include <iostream>
#include <Windows.h>
#include <cmath>
#include <chrono>
#include <thread>

#define LEFT 1   // * 0001
#define RIGHT 2  // * 0010
#define BOTTOM 4 // * 0100
#define TOP 8    // * 1000

HWND hwnd = GetConsoleWindow();
HDC hdc = GetDC(hwnd);
RECT window = {};
const double PI = 3.1415926535897932384;

using std::cout, std::cin;

class CRectangle
{
public:
    double top, right, bottom, left;

    CRectangle(double top, double right, double bottom, double left)
    {
        this->top = top;
        this->right = right;
        this->bottom = bottom;
        this->left = left;
    }

    void Draw()
    {
        Rectangle(hdc, left, top, right, bottom);
    }
};

class CPoint
{
public:
    double x, y;
    int binaryCode;

    CPoint(double x, double y, int binaryCode)
    {
        this->x = x;
        this->y = y;
        this->binaryCode = binaryCode;
    }

    void calculate(CRectangle &rec)
    {
        binaryCode = (x < rec.left ? LEFT : 0) + (x > rec.right ? RIGHT : 0) + (y < rec.top ? TOP : 0) + (y > rec.bottom ? BOTTOM : 0);
    }
};

double calculate(CRectangle &rec, CPoint &point)
{
    return (point.x < rec.left ? LEFT : 0) + (point.x > rec.right ? RIGHT : 0) + (point.y < rec.top ? TOP : 0) + (point.y > rec.bottom ? BOTTOM : 0);
}

int main()
{
    CRectangle rec(100, 200, 200, 100);
    CPoint first(234, 100, 0), second(424, 432, 0);

    SelectObject(hdc, GetStockObject(WHITE_PEN));
    SelectObject(hdc, GetStockObject(NULL_BRUSH));

    rec.Draw();
    first.calculate(rec);
    second.calculate(rec);
    cout << first.binaryCode << '\t' << second.binaryCode;

    std::getchar();
    return 0;
}