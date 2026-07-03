#include "pch.h"
#include "Calendar.h"
#include "App.h"

namespace {
    // 保存Calendar单例，保证窗口生命周期与进程一致
    std::unique_ptr<Calendar> calendar;
}

Calendar::Calendar(const int& x, const int& y, const int& w, const int& h)
    : WinBase(x, y, w, h)
{
    // 创建窗口，App::makeDC会在createWindow内部被调用
    // 这里加上WS_EX_LAYERED以外的样式不需要，因为WinBase使用DirectComposition实现半透明
    createWindow();
}

Calendar::~Calendar()
{
}

void Calendar::start()
{
    int w = 800;
    int h = 400;
    int x = 3000;
    int y = 60;

    calendar = std::make_unique<Calendar>(x, y, w, h);
    calendar->show();
}

void Calendar::onPaint()
{
    // 惰性创建画刷
    if (!bgBrush.Get()) {
        // 半透明深色背景，Alpha=0.55，注意需要预乘（PremultipliedAlpha）
        float a = 0.55f;
        D2D1_COLOR_F bg{ 0.10f * a, 0.10f * a, 0.14f * a, a };
        render->CreateSolidColorBrush(bg, bgBrush.GetAddressOf());
    }
    if (!textBrush.Get()) {
        // 前景文字/边框：白色
        D2D1_COLOR_F fg{ 1.0f, 1.0f, 1.0f, 1.0f };
        render->CreateSolidColorBrush(fg, textBrush.GetAddressOf());
    }

    // 清空为完全透明
    render->Clear(D2D1::ColorF(0, 0, 0, 0));

    // 绘制圆角半透明背景
    D2D1_ROUNDED_RECT rr{
        D2D1::RectF(0.f, 0.f, static_cast<float>(w), static_cast<float>(h)),
        12.f, 12.f
    };
    render->FillRoundedRectangle(rr, bgBrush.Get());

    // 标题
    auto title = makeTextLayout(L"Calendar", static_cast<float>(w), 40.f, 18.f);
    render->DrawTextLayout(D2D1::Point2F(0.f, 12.f), title.Get(), textBrush.Get());
}

LRESULT Calendar::onHitTest(WPARAM wParam, LPARAM lParam)
{
    // WM_NCHITTEST 的 lParam 是屏幕坐标，需要转换为客户区坐标
    POINT pt{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
    ScreenToClient(hwnd, &pt);
    // 只有左上角 100x100 的区域用于拖拽，其它区域走客户区，从而触发 onMouseDown 等事件
    if (pt.x >= 0 && pt.x < 100 && pt.y >= 0 && pt.y < 100) {
        return HTCAPTION;
    }
    return HTCLIENT;
}

BOOL Calendar::onCursor()
{
    SetCursor(LoadCursor(nullptr, IDC_ARROW));
    return TRUE;
}

void Calendar::onDestroy()
{
    App::exit(0);
}

void Calendar::onMouseDown(const int& x, const int& y, bool isRight)
{
    static HWND workerW;
    if (!workerW) {
        HWND progman = FindWindow(L"Progman", NULL);
        SendMessage(progman, 0x052C, 0xD, 0);
        SendMessage(progman, 0x052C, 0xD, 1);
        EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
            HWND defView = FindWindowEx(hwnd, NULL, L"SHELLDLL_DefView", NULL);
            if (defView != NULL) {
                auto tar = (HWND*)lParam;
                *tar = FindWindowEx(NULL, hwnd, L"WorkerW", NULL);
            }
            return TRUE;
            }, (LPARAM)&workerW);
    }
    // 记住嵌入前的屏幕坐标，SetParent 不会自动重新映射坐标
    RECT before;
    GetWindowRect(hwnd, &before);
    SetParent(hwnd, workerW);
    // WorkerW 覆盖整个虚拟桌面，其 (0,0) 位于虚拟桌面左上角，
    // 若存在位于主屏上方的副屏，该原点会在主屏之上（y 为负），
    // 因此需要把目标屏幕坐标转换为 WorkerW 客户区坐标，再重新定位。
    POINT pt{ before.left, before.top };
    ScreenToClient(workerW, &pt);
    SetWindowPos(hwnd, nullptr, pt.x, pt.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOREDRAW);
 //   RECT rect;
 //   GetWindowRect(hwnd, &rect);
	//auto str = std::format(L"Calendar moved to WorkerW, rect: left={}, top={}, right={}, bottom={}\n", rect.left, rect.top, rect.right, rect.bottom);
	//OutputDebugString(str.data());
}
