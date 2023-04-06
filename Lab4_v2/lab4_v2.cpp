#include "Classes.cpp"

const int WINDOW_SIZE = 800;
const double PI = 3.1415926535897932384;

HINSTANCE hInst;
HWND hwndMain;

CPoint camera(0, 0, 400);
C3DRectangle first(CPoint(-50, -50, 0), CPoint(-50, -100, 0), CPoint(-100, -100, 0), CPoint(-100, -50, 0), CPoint(-50, -50, 50), CPoint(-50, -100, 50), CPoint(-100, -100, 50), CPoint(-100, -50, 50));
C3DRectangle second(CPoint(-50, 50, 0), CPoint(-50, 100, 0), CPoint(-100, 100, 0), CPoint(-100, 50, 0), CPoint(-50, 50, 50), CPoint(-50, 100, 50), CPoint(-100, 100, 50), CPoint(-100, 50, 50));
RotationMatrix m(PI / 100);

LRESULT APIENTRY WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    LPPOINT lpPoint;

    switch (message)
    {
    case WM_PAINT: // ! DRAWING
        hdc = GetDC(hwndMain);

        SelectObject(hdc, GetStockObject(BLACK_PEN));

        Rectangle(hdc, 0, 0, WINDOW_SIZE, WINDOW_SIZE);

        drawAxis(hdc, WINDOW_SIZE);

        rorateX3DRectangle(first, PI / 120);
        draw3DRectangle(first, camera, hdc, WINDOW_SIZE);

        rorateY3DRectangle(second, PI / 120);
        draw3DRectangle(second, camera, hdc, WINDOW_SIZE, true);

        std::this_thread::sleep_for(std::chrono::milliseconds(17));

        ReleaseDC(hwndMain, hdc);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdSHow)
{
    MSG msg;
    WNDCLASSEX wcx;

    hInst = hInstance;

    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc = (WNDPROC)WndProc;
    wcx.cbClsExtra = 0;
    wcx.cbWndExtra = 0;
    wcx.hInstance = hInstance;
    wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wcx.lpszMenuName = "MainMenu";
    wcx.lpszClassName = "MainWClass";
    wcx.hIconSm = NULL;

    if (!RegisterClassEx(&wcx))
    {
        MessageBox(NULL, "!RegisterClassEx(&wcx)", "!RegisterClassEx(&wcx)", NULL);
    }

    hwndMain = CreateWindow("MainWClass", "Main Window",
                            WS_OVERLAPPEDWINDOW,
                            0, 0, WINDOW_SIZE, WINDOW_SIZE, (HWND)NULL, (HMENU)NULL, hInstance, NULL);
    if (!hwndMain)
    {
        MessageBox(NULL, "!hwndMain", "!hwndMain", NULL);
        return FALSE;
    }
    ShowWindow(hwndMain, SW_SHOW);
    UpdateWindow(hwndMain);

    BOOL fGotMessage;
    while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0 && fGotMessage != -1)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}