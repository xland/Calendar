#include "Font.h"
#include <Windows.h>
#include "resource.h"

static Font* font;

Font::Font()
{
    initFontIcon();
    initFontText();
}
Font::~Font()
{
    delete fontText;
    delete fontIcon;

}
void Font::Dispose()
{
    delete font;
}
void Font::Init() {
    font = new Font();
}

Font* Font::Get()
{
    return font;
}

void Font::initFontText()
{
    BLFontFace face;
    BLResult err = face.createFromFile("C:\\Windows\\Fonts\\simhei.ttf"); //����
    if (err) {
        MessageBox(NULL, L"ϵͳ�������ʧ��", L"ϵͳ��ʾ", NULL);
        return;
    }
    fontText = new BLFont();
    fontText->createFromFace(face, 16.0f);
}

void Font::initFontIcon()
{
    HMODULE instance = GetModuleHandle(NULL);
    HRSRC resID = FindResource(instance, MAKEINTRESOURCE(IDR_ICON_FONT), L"ICON_FONT");
    if (resID == 0) {
        MessageBox(NULL, L"��������ͼ����Դʧ��", L"ϵͳ��ʾ", NULL);
        return;
    }
    size_t resSize = SizeofResource(instance, resID);
    HGLOBAL res = LoadResource(instance, resID);
    if (res == 0) {
        MessageBox(NULL, L"��������ͼ����Դʧ��", L"ϵͳ��ʾ", NULL);
        return;
    }
    LPVOID resData = LockResource(res);
    BLFontData fontData;
    BLResult result = fontData.createFromData(resData, resSize);
    //BOOL flag = VirtualFree(resData, resSize, MEM_RELEASE);
    if (result != BL_SUCCESS) {
        MessageBox(NULL, L"��������ͼ��ʧ��", L"ϵͳ��ʾ", NULL);
        return;
    }
    BLFontFace face;
    face.createFromData(fontData, 0);
    fontIcon = new BLFont();
    result = fontIcon->createFromFace(face, 28.0f);
    if (result != BL_SUCCESS) {
        MessageBox(NULL, L"��������ͼ��ʧ��", L"ϵͳ��ʾ", NULL);
        return;
    }
}
