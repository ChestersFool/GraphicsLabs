#include <windows.h>

HINSTANCE hInst;
HWND hwndMain;

LRESULT APIENTRY WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    RECT rect;
    LPPOINT lpPoint;
    switch (message)
    {
    case WM_PAINT:
        hdc = GetDC(hwndMain);
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
                            0, 0, 800, 800, (HWND)NULL, (HMENU)NULL, hInstance, NULL);
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