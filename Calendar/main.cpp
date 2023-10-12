#include <Windows.h>
#include "App.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    auto result = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (result != S_OK) {
        return 0;
    }
    App::Init(hInstance);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    App::Dispose();
    CoUninitialize();
    return (int)msg.wParam;
    return 0;
}