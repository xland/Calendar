#include <napi.h>
#include <Windows.h>

WNDPROC OldProc;
LRESULT CALLBACK WindowHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_WINDOWPOSCHANGING)
    {
        WINDOWPOS *pPos = (WINDOWPOS *)lParam;
        if (!(pPos->flags & SWP_NOZORDER) && (pPos->hwndInsertAfter != HWND_BOTTOM))
        {
            pPos->hwndInsertAfter = HWND_BOTTOM;
            return 0;
        }
    }
    return CallWindowProc(OldProc, hwnd, msg, wParam, lParam);
}

Napi::Boolean Embed(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    auto buffer = info[0].As<Napi::Buffer<void *>>();
    HWND hwnd = static_cast<HWND>(*buffer.Data());
    static HWND hwndDefView;
    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
                {
        hwndDefView = FindWindowEx(hwnd, NULL,"SHELLDLL_DefView", NULL);
        if (hwndDefView != NULL) {
            return FALSE;
        }
        return TRUE; }, NULL);
    SetWindowLongPtr(hwnd, GWLP_HWNDPARENT, (LONG_PTR)hwndDefView);
    SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSENDCHANGING);
    OldProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WindowHandler);
    return Napi::Boolean::New(env, true);
}
Napi::Boolean Unembed(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    auto buffer = info[0].As<Napi::Buffer<void *>>();
    HWND hwnd = static_cast<HWND>(*buffer.Data());
    SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)OldProc);
    SetWindowLongPtr(hwnd, GWLP_HWNDPARENT, NULL);
    AllowSetForegroundWindow(ASFW_ANY);
    SetForegroundWindow(hwnd);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    PostMessage(hwnd, WM_ACTIVATE, WA_ACTIVE, 0);
    PostMessage(hwnd, WM_SETFOCUS, 0, 0);
    return Napi::Boolean::New(env, true);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "embed"), Napi::Function::New(env, Embed));
    exports.Set(Napi::String::New(env, "unembed"), Napi::Function::New(env, Unembed));
    return exports;
}
NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)