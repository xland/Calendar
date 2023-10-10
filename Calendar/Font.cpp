#include "Font.h"
#include <Windows.h>
#include "resource.h" 

tgui::Font* Font::text;
tgui::Font* Font::icon;

void Font::Dispose()
{
    delete Font::text;
    delete Font::icon;
}
void Font::Init() {
    Font::text = new tgui::Font("C:\\Windows\\Fonts\\simhei.ttf");

    HMODULE instance = GetModuleHandle(NULL);
    HRSRC resID = FindResource(instance, MAKEINTRESOURCE(IDR_ICON_FONT), L"ICON_FONT");
    if (resID == 0) {
        MessageBox(NULL, L"查找字体图标资源失败", L"系统提示", NULL);
        return;
    }
    size_t resSize = SizeofResource(instance, resID);
    HGLOBAL res = LoadResource(instance, resID);
    if (res == 0) {
        MessageBox(NULL, L"加载字体图标资源失败", L"系统提示", NULL);
        return;
    }
    LPVOID resData = LockResource(res);
    Font::icon = new tgui::Font(resData, resSize);
}
