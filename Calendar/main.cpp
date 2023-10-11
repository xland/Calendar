#include <Windows.h>
#include "WindowMain.h"
#include "Font.h"
#include "CalendarModel.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    CalendarModel::init();
    auto win = new WindowMain();
    delete win;
    CalendarModel::dispose();
    
    return 0;
}