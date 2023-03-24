#include <iostream>
#include <Windows.h>
#include <stdint.h>
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

    // * CONSTRUCTOR WITH TWO POINT
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
    double x = 0, y = 0;
    uint8_t binaryCode = 0;

    CPoint(double x, double y, uint8_t binaryCode)
    {
        this->x = x;
        this->y = y;
        this->binaryCode = binaryCode;
    }

    CPoint() {}

    // * CALCULATION OF BINARY CODE FOR TASK
    void calculate(CRectangle &rec)
    {
        binaryCode = (x < rec.left ? LEFT : 0) + (x > rec.right ? RIGHT : 0) + (y < rec.top ? TOP : 0) + (y > rec.bottom ? BOTTOM : 0);
    }

    CPoint &operator=(const CPoint &outher)
    {
        this->x = outher.x;
        this->y = outher.y;
        this->binaryCode = outher.binaryCode;

        return *this;
    }
};

class CDirectVariation
{
public:
    double a, b, c;

    CDirectVariation(CPoint &first, CPoint &second)
    {
        a = fabs(first.y - second.y);
        b = fabs(first.x - second.x);
        c = fabs(first.x * second.y - first.y * second.x);
    }

    void Enumeration(CPoint &first, CPoint &second)
    {
        a = fabs(first.y - second.y);
        b = fabs(first.x - second.x);
        c = fabs(first.x * second.y - first.y * second.x);
    }
};

void DrawSegment(CPoint &first, CPoint &second)
{
    MoveToEx(hdc, first.x, first.y, NULL);
    LineTo(hdc, second.x, second.y);
}

/*
 * 0 two points out of rectangle
 * 1 two points in rectangle
 */
bool SutherlandCoen(CPoint &first, CPoint &second, CRectangle &rec)
{
    CPoint outOfRec;
    CDirectVariation direct(first, second);
    bool firstOutOfRec;

    first.calculate(rec);
    second.calculate(rec);

    while (first.binaryCode | second.binaryCode)
    {
        if (first.binaryCode & second.binaryCode)
            return 0;
        //
        //
        //
        if (first.binaryCode)
        {
            outOfRec = first;
            firstOutOfRec = true;
        }
        else
        {
            outOfRec = second;
            firstOutOfRec = false;
        }
        //
        //
        //
        if (outOfRec.binaryCode & LEFT)
        {
            outOfRec.y += direct.a * (rec.left - outOfRec.x) / direct.b;
            outOfRec.x = rec.left;
            outOfRec.binaryCode -= LEFT;
        }
        else if (outOfRec.binaryCode & RIGHT)
        {
            outOfRec.y -= direct.a * (rec.right - outOfRec.x) / direct.b;
            outOfRec.x = rec.right;
            outOfRec.binaryCode -= RIGHT;
        }
        else if (outOfRec.binaryCode & TOP)
        {
            outOfRec.x += direct.b * (rec.top - outOfRec.y) / direct.a;
            outOfRec.y = rec.top;
            outOfRec.binaryCode -= TOP;
        }
        else if (outOfRec.binaryCode & BOTTOM)
        {
            outOfRec.x -= direct.b * (rec.bottom - outOfRec.y) / direct.a;
            outOfRec.y = rec.bottom;
            outOfRec.binaryCode -= BOTTOM;
        }

        firstOutOfRec ? first = outOfRec : second = outOfRec;
        direct.Enumeration(first, second);
    }
    return 1;
}

int main()
{
    std::getchar();

    CRectangle rec(100, 200, 200, 100);
    CPoint points[10] = {
        CPoint(150, 150, 0),
        CPoint(50, 50, 0),
        CPoint(250, 75, 0),
        CPoint(50, 75, 0),
        CPoint(150, 20, 0),
        CPoint(150, 220, 0),
        CPoint(110, 110, 0),
        CPoint(190, 110, 0),
        CPoint(50, 50, 0),
        CPoint(50, 150, 0),
    };

    HPEN myPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    SelectObject(hdc, GetStockObject(WHITE_PEN));
    SelectObject(hdc, GetStockObject(NULL_BRUSH));

    rec.Draw();
    for (int i = 0; i < 10; i += 2)
    {
        SelectObject(hdc, GetStockObject(WHITE_PEN));
        DrawSegment(points[i], points[i + 1]);

        if (SutherlandCoen(points[i], points[i + 1], rec))
        {
            SelectObject(hdc, myPen);
            DrawSegment(points[i], points[i + 1]);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::getchar();
    std::getchar();
    std::getchar();

    return 0;
}