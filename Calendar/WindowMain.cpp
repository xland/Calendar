#include "WindowMain.h"
#include "CalendarSmall.h"
#include "TitleBarBtns.h"
#include <memory>
#include <array>
#include "Font.h"

WindowMain::WindowMain() {

	initWindow();
	WindowBase::wndMap[hwnd] = this;
    gui = new tgui::Gui{ *sfWin };
    Font::Init();
    tgui::Font::setGlobalFont(*Font::text);    

    auto panel = tgui::Panel::create();
    panel->setPosition(0, 0);
    panel->setSize(380, "100%");
    panel->getRenderer()->setBackgroundColor(tgui::Color(253, 233, 235));
    gui->add(panel);
    initWinTitle();
    gui->add(CalendarSmall::create());
    gui->add(TitleBarBtns::create());
    gui->mainLoop();
}
WindowMain::~WindowMain() {
    Font::Dispose();
}

void WindowMain::initWinTitle() {
    auto labelIcon = tgui::Label::create();
    labelIcon->setText(u8"\ue685");
    labelIcon->setPosition(12, 6);
    labelIcon->getRenderer()->setTextSize(22);
    auto renderer = labelIcon->getRenderer();
    renderer->setFont(*Font::icon);
    renderer->setTextColor(tgui::Color(240, 44, 56));
    gui->add(labelIcon);

    auto labelTitle = tgui::Label::create();
    labelTitle->setText(L"日历");
    labelTitle->setPosition(36, 8);
    labelTitle->getRenderer()->setTextSize(20);
    renderer = labelTitle->getRenderer();
    renderer->setTextColor(tgui::Color(120, 120, 120));
    gui->add(labelTitle);
}

bool WindowMain::isPosInCaption(const POINT& mousePos, const RECT& winRect) {
	if (mousePos.y < winRect.top+50 && mousePos.x < winRect.right - 150) {
		return true;
	}
	return false;
}