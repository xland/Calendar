#include <Windows.h>
#include "WindowMain.h"
#include "Font.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    Font::Init();
    WindowBase* win = new WindowMain();
    win->show();
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    delete win;
    Font::Dispose();
    return 0;
}