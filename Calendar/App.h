#pragma once
#include <vector>
#include <Windows.h>
#include "WinBase.h"
#include <filesystem>
#include <WebView2.h>
class App
{
public:
	~App();
	static void init(const HINSTANCE& hInstance);
	static void dispose();
	static App* get();
	HRESULT envReady(HRESULT result, ICoreWebView2Environment* env);
	HINSTANCE hinstance;
private:
	App(const HINSTANCE& hInstance);
	void ensureAppFolder();
	bool checkRegKey(const HKEY& key, const std::wstring& subKey);
	bool checkRuntime();
	std::vector<WinBase*> windows;
	std::filesystem::path appFolder;
	ICoreWebView2Environment* webEnv;
};

