#include "WindowMain.h"
#include <memory>

WindowMain::WindowMain() {
	initWindow();
	WindowBase::wndMap[hwnd] = this;
    gui = new tgui::Gui{ *sfWin };
    tgui::Button::Ptr button = tgui::Button::create();
    button->onClick.connect([]() {
        auto func = []() {
            auto a = new WindowMain();
            };
        std::thread t(func);
        t.detach();
        });
    button->setPosition(100, 50);
    auto editBox = tgui::EditBox::create();
    editBox->setPosition(100, 400);
    tgui::Font::setGlobalFont("C:\\Windows\\Fonts\\simhei.ttf");
    gui->add(button);
    gui->add(editBox, "MyWidgetName");
    gui->mainLoop();
}
WindowMain::~WindowMain() {

}

bool WindowMain::isPosInCaption(const POINT& mousePos, const RECT& winRect) {
	if (mousePos.y < winRect.top+50) {
		return true;
	}
	return false;
}