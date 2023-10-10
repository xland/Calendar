#include "WindowMain.h"
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
    initTitleBarBtns();
    calendarGrid = tgui::Grid::create();
    calendarGrid->setPosition(28, 60);
    calendarGrid->setSize(320,260);

    initCalendarTitle();
    initCalendarDate();

    gui->add(calendarGrid);
    gui->mainLoop();
    


}
WindowMain::~WindowMain() {

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

void WindowMain::initTitleBarBtns() {
    tgui::Button::Ptr buttonClose = tgui::Button::create();
    buttonClose->setPosition("100%", 0);
    buttonClose->setOrigin(1.0f, 0.f);
    buttonClose->setSize(50, 40);
    auto renderer = buttonClose->getRenderer();
    renderer->setBorders(tgui::Borders(0, 0, 0, 0));
    renderer->setFont(*Font::icon);
    renderer->setTextSize(17);
    buttonClose->setText(u8"\ue6e7");
    buttonClose->onClick.connect(&WindowMain::close, this);
    gui->add(buttonClose);

    auto buttonMaximize = tgui::Button::copy(buttonClose);
    buttonMaximize->setSize(bindSize(buttonClose));
    buttonMaximize->setPosition({ tgui::bindLeft(buttonClose), tgui::bindTop(buttonClose) });
    buttonMaximize->setText(u8"\ue6e5");
    buttonMaximize->onClick.connect(&WindowMain::maximize, this);
    gui->add(buttonMaximize);

    auto buttonMinimize = tgui::Button::copy(buttonMaximize);
    buttonMinimize->setSize(bindSize(buttonMaximize));
    buttonMinimize->setPosition({ tgui::bindLeft(buttonMaximize), tgui::bindTop(buttonMaximize) });
    buttonMinimize->setText(u8"\ue6e8");
    buttonMinimize->onClick.connect(&WindowMain::minimize, this);
    gui->add(buttonMinimize);
}

void WindowMain::initCalendarTitle() {
    std::array<tgui::String, 7> headerLableArr[]{ L"一",L"二",L"三",L"四",L"五",L"六",L"日" };
    auto labelCalendar1 = tgui::Label::create();
    labelCalendar1->setText(headerLableArr->at(0));
    labelCalendar1->getRenderer()->setTextSize(20);
    auto lr = labelCalendar1->getRenderer();
    lr->setTextColor(tgui::Color(120, 120, 120));
    calendarGrid->addWidget(labelCalendar1, 0, 0);
    for (size_t i = 1; i < 7; i++)
    {
        auto label = tgui::Label::copy(labelCalendar1);
        label->setText(headerLableArr->at(i));
        calendarGrid->addWidget(label, 0, i);
    }
}
void WindowMain::initCalendarDate() {

    tgui::Button::Ptr btn = tgui::Button::create();
    auto renderer = btn->getRenderer();
    renderer->setBorders(tgui::Borders(0, 0, 0, 0));
    renderer->setTextSize(17);
    btn->setText("12");
    calendarGrid->addWidget(btn, 1, 0);
    for (size_t y = 1; y < 7; y++)
    {
        for (size_t x = 0; x < 7; x++)
        {
            if (y == 1 && x == 0) {
                continue;
            }
            auto item = tgui::Button::copy(btn);
            item->setText(L"12");
            calendarGrid->addWidget(item, y, x);
        }
    }
}

bool WindowMain::isPosInCaption(const POINT& mousePos, const RECT& winRect) {
	if (mousePos.y < winRect.top+50 && mousePos.x < winRect.right - 150) {
		return true;
	}
	return false;
}