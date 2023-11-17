#include <napi.h>
#include <string>
#include <filesystem>
#include <Windows.h>
#include <shlobj_core.h>
#include <shobjidl.h>

Napi::Boolean SetTaskBarIcon(const Napi::CallbackInfo &info)
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(hr))
    {
        auto env = info.Env();
        auto result = Napi::Boolean::New(env, false);
        return result;
    }
    PWSTR appdataLocalPath = NULL; // C:\Users\liuxiaolun\AppData\Local
    hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, NULL, &appdataLocalPath);
    if (FAILED(hr))
    {
        CoUninitialize();
        auto env = info.Env();
        auto result = Napi::Boolean::New(env, false);
        return result;
    }
    auto lnkPathObj = std::filesystem::path(appdataLocalPath).parent_path();
    lnkPathObj.append("Roaming\\Microsoft\\Internet Explorer\\Quick Launch\\User Pinned\\TaskBar\\HikLink.lnk");
    if (!std::filesystem::exists(lnkPathObj))
    {
        CoTaskMemFree(appdataLocalPath);
        CoUninitialize();
        auto env = info.Env();
        auto result = Napi::Boolean::New(env, true);
        return result;
    }
    IShellLink *pShellLink;
    hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **)&pShellLink);
    if (FAILED(hr))
    {
        pShellLink->Release();
        CoTaskMemFree(appdataLocalPath);
        CoUninitialize();
        auto env = info.Env();
        auto result = Napi::Boolean::New(env, false);
        return result;
    }
    IPersistFile *pPersistFile;
    hr = pShellLink->QueryInterface(IID_IPersistFile, (void **)&pPersistFile);
    if (FAILED(hr))
    {
        pPersistFile->Release();
        pShellLink->Release();
        CoTaskMemFree(appdataLocalPath);
        CoUninitialize();
        auto env = info.Env();
        auto result = Napi::Boolean::New(env, false);
        return result;
    }
    auto lnkPathStr = lnkPathObj.wstring();
    hr = pPersistFile->Load(lnkPathStr.c_str(), STGM_READ);
    if (FAILED(hr))
    {
        pPersistFile->Release();
        pShellLink->Release();
        CoTaskMemFree(appdataLocalPath);
        CoUninitialize();
        auto env = info.Env();
        auto result = Napi::Boolean::New(env, false);
        return result;
    }
    std::string linkTarget(MAX_PATH, '\x00');
    hr = pShellLink->GetPath(&linkTarget[0], MAX_PATH, 0, SLGP_SHORTPATH);
    if (FAILED(hr))
    {
        pPersistFile->Release();
        pShellLink->Release();
        CoTaskMemFree(appdataLocalPath);
        CoUninitialize();
        auto env = info.Env();
        auto result = Napi::Boolean::New(env, false);
        return result;
    }
    auto index = linkTarget.find("AppData");
    if (index != std::string::npos)
    {
        pPersistFile->Release();
        pShellLink->Release();
        CoTaskMemFree(appdataLocalPath);
        CoUninitialize();
        auto env = info.Env();
        auto result = Napi::Boolean::New(env, true);
        return result;
    }
    IShellItem *pitem;
    hr = SHCreateItemFromParsingName(lnkPathStr.c_str(), NULL, IID_PPV_ARGS(&pitem));
    if (FAILED(hr))
    {
        pitem->Release();
        pPersistFile->Release();
        pShellLink->Release();
        CoTaskMemFree(appdataLocalPath);
        CoUninitialize();
        auto env = info.Env();
        auto result = Napi::Boolean::New(env, false);
        return result;
    }
    IStartMenuPinnedList *pStartMenuPinnedList;
    hr = CoCreateInstance(CLSID_StartMenuPin, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pStartMenuPinnedList));
    if (FAILED(hr))
    {
        pStartMenuPinnedList->Release();
        pitem->Release();
        pPersistFile->Release();
        pShellLink->Release();
        CoTaskMemFree(appdataLocalPath);
        CoUninitialize();
        auto env = info.Env();
        auto result = Napi::Boolean::New(env, false);
        return result;
    }
    hr = pStartMenuPinnedList->RemoveFromList(pitem);
    auto Tombstones = std::filesystem::path(appdataLocalPath).parent_path();
    Tombstones.append("Roaming\\Microsoft\\Internet Explorer\\Quick Launch\\User Pinned\\Tombstones");
    std::filesystem::remove_all(Tombstones);
    pStartMenuPinnedList->Release();
    pitem->Release();
    pPersistFile->Release();
    pShellLink->Release();
    CoTaskMemFree(appdataLocalPath);
    CoUninitialize();
    auto env = info.Env();
    auto result = Napi::Boolean::New(env, true);
    return result;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("setTaskBarIcon", Napi::Function::New(env, SetTaskBarIcon));
    return exports;
}
NODE_API_MODULE(bear, Init)