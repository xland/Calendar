#pragma once
#include <string>
#include <Windows.h>
#include <wrl.h>
#include <wil/com.h>
#include <WebView2.h>
class WinBase
{
public:
	WinBase();
	~WinBase();
	void show();
	void navigate(const std::wstring& url);
	void openDevTools();
	bool createPageCtrl(ICoreWebView2Environment* env);
	long w, h;
	int x, y;
	HWND hwnd;
protected:
	void initWindow(const int& x, const int& y, const long& w, const long& h, const std::wstring& title);
	virtual void ctrlReady() {};
private:
	static LRESULT CALLBACK RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	HRESULT pageCtrlCallBack(HRESULT result, ICoreWebView2Controller* controller);
	HRESULT navigationStarting(ICoreWebView2* webview, ICoreWebView2NavigationStartingEventArgs* args);
	wil::com_ptr<ICoreWebView2Controller> pageCtrl;
	wil::com_ptr<ICoreWebView2> page;
};

