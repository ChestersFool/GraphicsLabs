#define UNICODE
#define _UNICODE
#include <windows.h>
#include <tchar.h>
const TCHAR CLSNAME[] = TEXT("helloworldWClass");
LRESULT CALLBACK winproc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdSHow)
{
    HDC hdc;
    WNDCLASSEX wc = {};
    MSG msg;
    HWND hwnd;

    wc.cbSize = sizeof(wc);
    wc.style = 0;
    wc.lpfnWndProc = winproc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = CLSNAME;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, TEXT("Could not register window class"),
                   NULL, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_LEFT,
                          CLSNAME,
                          NULL,
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          NULL,
                          NULL,
                          hPrevInstance,
                          NULL);
    if (!hwnd)
    {
        MessageBox(NULL, TEXT("Could not create window"), NULL, MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, nCmdSHow);
    UpdateWindow(hwnd);
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
LRESULT CALLBACK winproc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp)
{
    return DefWindowProc(hwnd, wm, wp, lp);
}