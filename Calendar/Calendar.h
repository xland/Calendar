#pragma once
#include "WinBase.h"

class Calendar : public WinBase
{
public:
    Calendar(const int& x, const int& y, const int& w, const int& h);
    ~Calendar() override;

    static void start();

protected:
    void onPaint() override;
    LRESULT onHitTest(WPARAM wParam, LPARAM lParam) override;
    LRESULT onMouseActivate() override { return MA_ACTIVATE; }
    BOOL onCursor() override;
    void onDestroy() override;
	void onMouseDown(const int& x, const int& y, bool isRight) override;

private:
    ComPtr<ID2D1SolidColorBrush> bgBrush;
    ComPtr<ID2D1SolidColorBrush> textBrush;
};
