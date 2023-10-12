#include "App.h"
#include "WinCalendar.h"
#include <functional>
#include <Windows.h>
#include <wrl.h>
#include <wil/com.h>  //Microsoft.Windows.ImplementationLibrary
#include <WebView2.h>
#include <string>
#include <Shlobj.h>
#include <shellapi.h>

static App* app;

App::App(const HINSTANCE& hInstance) :hinstance{ hInstance }
{
	auto win = new WinCalendar();
	windows.push_back(win);
	//PageEnvironment::Init([&win]() {
	//	win->CreatePageController();
	//	});
}
App::~App()
{

}

void App::init(const HINSTANCE& hInstance) {
	app = new App(hInstance);
    app->checkRuntime();
    app->ensureAppFolder();
    //auto options = Microsoft::WRL::Make<CoreWebView2EnvironmentOptions>();
    //options->put_AdditionalBrowserArguments(L"--allow-file-access-from-files");
    //Microsoft::WRL::ComPtr<ICoreWebView2EnvironmentOptions4> options4;
    //HRESULT oeResult = options.As(&options4);
    //if (oeResult != S_OK) {
    //    // UNREACHABLE - cannot continue  todo
    //}
    //const WCHAR* allowedSchemeOrigins[5] = { L"about://*", L"http://*", L"https://*", L"file://*", L"socket://*" };
    //auto defaultRegistration = Microsoft::WRL::Make<CoreWebView2CustomSchemeRegistration>(L"kp");
    //defaultRegistration->put_HasAuthorityComponent(TRUE);
    //defaultRegistration->put_TreatAsSecure(TRUE);
    //defaultRegistration->SetAllowedOrigins(5, allowedSchemeOrigins);
    //ICoreWebView2CustomSchemeRegistration* registrations[1] = { defaultRegistration.Get() };
    //options4->SetCustomSchemeRegistrations(1, static_cast<ICoreWebView2CustomSchemeRegistration**>(registrations));
    auto envCBInstance = Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(app, &App::envReady);
    HRESULT result = CreateCoreWebView2EnvironmentWithOptions(nullptr, app->appFolder.c_str(), nullptr/*options.Get()*/, envCBInstance.Get());
    if (FAILED(result)) {
        auto result = MessageBox(nullptr, L"环境初始化失败，即将退出",
            L"系统提示", MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1);
        exit(1);
    }
}

App* App::get() {
	return app;
}
void App::dispose()
{
	delete app;
}

HRESULT App::envReady(HRESULT result, ICoreWebView2Environment* env)
{
	this->webEnv = env;

	return S_OK;
}


bool App::checkRegKey(const HKEY& key, const std::wstring& subKey) {
    size_t bufferSize = 20; //每位4个，共4位，加3个点，再多给一位，后面会截掉多余的
    std::wstring valueBuf;
    valueBuf.resize(bufferSize);
    auto valueSize = static_cast<DWORD>(bufferSize * sizeof(wchar_t));
    auto rc = RegGetValue(key, subKey.c_str(), L"pv", RRF_RT_REG_SZ, nullptr,
        static_cast<void*>(valueBuf.data()), &valueSize
    );
    if (rc == ERROR_SUCCESS)
    {
        valueSize /= sizeof(wchar_t);
        valueBuf.resize(static_cast<size_t>(valueSize - 1));//todo 这个版本号可能有用
        if (valueBuf.empty() || valueBuf == L"0.0.0.0") {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool App::checkRuntime()
{
    std::wstring regSubKey = L"\\Microsoft\\EdgeUpdate\\Clients\\{F3017226-FE2A-4295-8BDF-00C3A9A7E4C5}";
    bool hasRuntime = checkRegKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\WOW6432Node" + regSubKey);
    if (hasRuntime) return true;
    hasRuntime = checkRegKey(HKEY_CURRENT_USER, L"Software" + regSubKey);
    if (!hasRuntime) {
        auto result = MessageBox(nullptr, L"您得系统中缺少必要组件，现在为您打开下载链接，下载相关组件？",
            L"系统提示", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON1);
        if (result == IDOK) {
            ShellExecute(0, 0, L"https://go.microsoft.com/fwlink/p/?LinkId=2124703", 0, 0, SW_SHOW);
        }
        return false;
    }
    return true;
}

void App::ensureAppFolder() {
    PWSTR pathTmp;
    auto ret = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &pathTmp);
    if (ret != S_OK) {
        CoTaskMemFree(pathTmp);
        auto result = MessageBox(nullptr, L"未找到系统应用程序目录AppData，即将退出",
            L"系统提示", MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1);
        exit(1);
    }
    appFolder = pathTmp;
    CoTaskMemFree(pathTmp);
    appFolder /= L"Calendar";
    if (!std::filesystem::exists(appFolder)) {
        auto flag = std::filesystem::create_directory(appFolder);
        if (!flag) {
            MessageBox(nullptr, L"数据目录创建失败，即将退出",
                L"系统提示", MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1);
            exit(1);
        }
    }
}