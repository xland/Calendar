#include "pch.h"
#include "App.h"
#include "Setting.h"
#include "Tray.h"
#include "Update.h"
#include "./Win/WinSetting.h"

std::unique_ptr<App> app;


App::~App()
{
}

void App::init()
{
    auto ptr = new App();
    app.reset(ptr);
}

void App::dispose()
{
    WinSetting::dispose();
    Setting::dispose();
    app.reset();
}

App* App::get()
{
    return app.get();
}


App::App()
{
    Ling::init();
    auto app = Ling::App::get();
    app->initArgs();
    Ling::D2D::addFonts({ L"icon.ttf" });
    Setting::init();
    bool flag = app->refuseSecondInstance();
    if (flag) return;
    Tray::init();
    // 开机自启不启动截图；--enter=tray 也一样，升级完重启新版本走的就是它 ——
    // 都是"只挂个托盘图标待命"，这条路上一个窗口都不建，图形设备也就根本不会创建
    if (app->args[L"--auto-start"] == L"true" || app->args[L"--enter"] == L"tray") {
        Update::checkLater();
        return;
    }
}
