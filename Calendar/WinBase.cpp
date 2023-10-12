#include "WinBase.h"
#include <format>
#include "App.h"
#include <dwmapi.h>

WinBase::WinBase() {

}
WinBase::~WinBase() {

}

void WinBase::initWindow(const int& x, const int& y, const long& w, const long& h, const std::wstring& title)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    static int num = 0;
    std::wstring className = std::format(L"KaoPu_{}", num++);
    WNDCLASSEX wcx{};
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc = &WinBase::RouteWindowMessage;
    wcx.cbWndExtra = sizeof(WinBase*);
    wcx.hInstance = App::get()->hinstance;
    wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcx.lpszClassName = className.c_str();
    if (!RegisterClassEx(&wcx))
    {
        MessageBox(NULL, L"注册窗口类失败", L"系统提示", NULL);
        return;
    }
    hwnd = CreateWindowEx(NULL, wcx.lpszClassName, title.c_str(),
        WS_OVERLAPPEDWINDOW, x, y, w, h, NULL, NULL, App::get()->hinstance, static_cast<LPVOID>(this));
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    const MARGINS shadowState{ 1,1,1,1 };
    DwmExtendFrameIntoClientArea(hwnd, &shadowState);
}
void WinBase::show() {
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}

LRESULT CALLBACK WinBase::RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_NCCREATE)
    {
        CREATESTRUCT* pCS = reinterpret_cast<CREATESTRUCT*>(lParam);
        LPVOID pThis = pCS->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    auto obj = reinterpret_cast<WinBase*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    if (obj) {
        return obj->WindowProc(hWnd, msg, wParam, lParam);
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK WinBase::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static bool mouseTracing = false;
    switch (msg)
    {
    case WM_NCCALCSIZE:
    {
        if (wParam == TRUE)
        {
            return false;
        }
        break;
    }
    case WM_EXITSIZEMOVE: {
        RECT rect;
        GetWindowRect(hWnd, &rect);
        this->x = rect.left;
        this->y = rect.top;
        return true;
    }
    case WM_SIZE: {
        if (lParam != 0 && pageCtrl != nullptr) {
            RECT rect;
            GetClientRect(hWnd, &rect);
            pageCtrl->put_Bounds(rect);
        };
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

bool WinBase::createPageCtrl(ICoreWebView2Environment* env)
{
    auto callBackInstance = Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(this, &WinBase::pageCtrlCallBack);
    auto result = env->CreateCoreWebView2Controller(hwnd, callBackInstance.Get());
    if (FAILED(result)) {
        return false;
    }
    return true;
}

HRESULT WinBase::pageCtrlCallBack(HRESULT result, ICoreWebView2Controller* controller)
{
    this->pageCtrl = controller;    
    auto hr = controller->get_CoreWebView2(&page);
    RECT bounds;
    GetClientRect(hwnd, &bounds);
    hr = controller->put_Bounds(bounds);

    wil::com_ptr<ICoreWebView2Settings> settings;
    page->get_Settings(&settings);
    settings->put_IsScriptEnabled(TRUE);
    settings->put_AreDefaultScriptDialogsEnabled(TRUE);
    settings->put_IsWebMessageEnabled(TRUE);    
    ctrlReady();
    return hr;
}

void WinBase::navigate(const std::wstring& url)
{
    // Schedule an async task to navigate to Bing
    auto result = page->Navigate(url.data());
    //EventRegistrationToken token;
    //auto navigateCB = Microsoft::WRL::Callback<ICoreWebView2NavigationStartingEventHandler>(this, &WinBase::navigationStarting);
    //page->add_NavigationStarting(navigateCB.Get(), &token);
}

HRESULT WinBase::navigationStarting(ICoreWebView2* webview, ICoreWebView2NavigationStartingEventArgs* args)
{
    //wil::unique_cotaskmem_string uri;
    //args->get_Uri(&uri);
    //std::wstring source(uri.get());
    //if (source.substr(0, 5) != L"https") {
    //	args->put_Cancel(true);
    //}
    return S_OK;
}
void WinBase::openDevTools()
{
    page->OpenDevToolsWindow();
}