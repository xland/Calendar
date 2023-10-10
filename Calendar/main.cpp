#include <Windows.h>
#include "WindowMain.h"
#include "Font.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    auto win = new WindowMain();
    Font::Dispose();
    return 0;
}