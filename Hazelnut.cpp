#include "AppWindow.h"

int __stdcall WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nShowCmd
)
{
    AppWindow app;
    if (app.init(L"Hazel Hub", 800, 600) &&
        app.createBtn(L"Editor", 400, 200, 100, 50)) {
        while (app.isRunning())
        {
            app.broadcast();
        }
    }
    return 0;
}