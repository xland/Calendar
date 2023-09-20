#include "Util.h"
std::string ConvertToUTF8(const std::wstring& wstr)
{
    const int count = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(), NULL, 0, NULL, NULL);
    std::string str(count, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
    return str;
}

std::string ConvertToUTF8(const LPWSTR& wstr)
{
    const int count = WideCharToMultiByte(CP_UTF8, 0, wstr, (int)wcslen(wstr), NULL, 0, NULL, NULL);
    std::string str(count, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &str[0], count, NULL, NULL);
    return str;
}

std::wstring ConvertToUTF16(const std::string& input) {
    const auto size = MultiByteToWideChar(CP_UTF8, 0, input.data(), static_cast<int>(input.size()), nullptr, 0);
    std::wstring output(size, L'\0');
    if (size != MultiByteToWideChar(CP_UTF8, 0, input.data(), static_cast<int>(input.size()), &output[0], static_cast<int>(output.size()))) {
        output.clear();
    }
    return output;
}

void ChangeCursor(LPCTSTR cursor)
{
    auto hCursor = LoadCursor(NULL, cursor);
    SetCursor(hCursor);
}

void Debug(const std::string& info)
{
    OutputDebugStringA("\r\n");
    OutputDebugStringA(info.c_str());
    OutputDebugStringA("\r\n");
}