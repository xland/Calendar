#pragma once
#include <string>
#include <Windows.h>

std::string ConvertToUTF8(const std::wstring& wstr);
std::string ConvertToUTF8(const LPWSTR& wstr);
std::wstring ConvertToUTF16(const std::string& input);
void ChangeCursor(LPCTSTR cursor);
void Debug(const std::string& info);

