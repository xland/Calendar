#include "TitleBarBtns.h"
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/SignalManager.hpp>
#include "Font.h"
#include "EventBus.h"
#include <dwmapi.h>

TitleBarBtns::TitleBarBtns() {
    tgui::Button::Ptr btnMinimize = tgui::Button::create();
    auto renderer = btnMinimize->getRenderer();
    renderer->setBorders(tgui::Borders(0, 0, 0, 0));
    renderer->setFont(*Font::icon);
    renderer->setTextSize(17);
    btnMinimize->setText(u8"\ue6e8");
    btnMinimize->onClick.connect(&TitleBarBtns::minimize, this);
    this->add(btnMinimize);

    auto btnMaxRestore = tgui::Button::copy(btnMinimize);
    btnMaxRestore->setSize(bindSize(btnMinimize));
    btnMaxRestore->setText(u8"\ue6e5");
    btnMaxRestore->setUserData(false);
    btnMaxRestore->onClick.connect(&TitleBarBtns::maximizeRestore, this);
    this->add(btnMaxRestore);

    auto btnClose = tgui::Button::copy(btnMinimize);
    btnClose->setWidgetName("closeBtn");
    btnClose->setSize(bindSize(btnMinimize));
    btnClose->setText(u8"\ue6e7");
    btnClose->onClick.connect(&TitleBarBtns::close, this);
    this->add(btnClose);

    setPosition("100%", 0);
    setOrigin(1.0f, 0.f);
    setSize(150, 40);

    //tgui::SignalManager::getSignalManager()->
    //tgui::Signal onMyEvent = { "MyEvent" };
    //onMyEvent.emit()

    EventBus::on("maximized", [this]() {
        auto btn = (tgui::Button*)this->get(1).get();
        btn->setText(u8"\ue6e9");
        btn->setUserData(true);
    });

    EventBus::on("restored", [this]() {
        auto btn = (tgui::Button*)this->get(1).get();
        btn->setText(u8"\ue6e5");
        btn->setUserData(false);
    });
}
TitleBarBtns::~TitleBarBtns() {

}
TitleBarBtns::Ptr TitleBarBtns::create() {
	return std::make_shared<TitleBarBtns>();
}

void TitleBarBtns::close() {
    auto gui = (tgui::BackendGuiSFML*)this->getParentGui();
    HWND hwnd = gui->getWindow()->getNativeHandle();
    SendMessage(hwnd, WM_CLOSE, NULL, NULL);
    PostQuitMessage(0);
}
void TitleBarBtns::minimize() {
    auto gui = (tgui::BackendGuiSFML*)this->getParentGui();
    HWND hwnd = gui->getWindow()->getNativeHandle();
    ShowWindow(hwnd, SW_SHOWMINIMIZED);
}
void TitleBarBtns::maximizeRestore() {
    auto gui = (tgui::BackendGuiSFML*)this->getParentGui();
    HWND hwnd = gui->getWindow()->getNativeHandle();
    auto isMaximaize = this->get(1)->getUserData<bool>();
    if (isMaximaize) {
        ShowWindow(hwnd, SW_SHOWNORMAL);
    }
    else
    {
        ShowWindow(hwnd, SW_SHOWMAXIMIZED);
    }    
}