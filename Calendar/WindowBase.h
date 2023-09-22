#pragma once
#include <Windows.h>
#include <blend2d.h>
#include <string>
#include <vector>
#include <memory>
#include "ViewBase.h"
class WindowBase
{
public:
	WindowBase();
	~WindowBase();
	void repaint();
	void show();
	HWND hwnd;
	long w, h;
	int x, y;
	std::vector<std::shared_ptr<ViewBase>> views;
protected:
	void initWindow(const int& x, const int& y, const long& w, const long& h, const std::wstring& title);
	virtual void onPaint() {};
	virtual bool isPosInCaption(const int& x, const int& y) { return false; };
	BLContext* paintCtx;
	bool isLeftBtnDown;
private:
	void paintToClient();
	void initCanvas();
	int hitTest(LPARAM lParam);
	POINT pointToClient(LPARAM lParam);
	static LRESULT CALLBACK routeWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	std::wstring title;
	void* pixelData;
	unsigned long pixelDataSize;
	HBITMAP bitmap;
	BLImage* canvasImage;
};

