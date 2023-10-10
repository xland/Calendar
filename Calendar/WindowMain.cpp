#include "WindowMain.h"
#include <memory>

WindowMain::WindowMain() {
	initWindow();
	WindowBase::wndMap[hwnd] = this;
    gui = new tgui::Gui{ *sfWin };
    tgui::Font font("C:\\Windows\\Fonts\\simhei.ttf");
    tgui::Font icon("D:\\project\\Calendar\\Calendar\\Res\\iconfont.ttf");
    tgui::Font::setGlobalFont(font);
    

    auto panel = tgui::Panel::create();
    panel->setPosition(0, 0);
    panel->setSize(380, "100%");
    panel->getRenderer()->setBackgroundColor(tgui::Color(253, 233, 235));
    gui->add(panel);
    {
        auto labelIcon = tgui::Label::create();
        labelIcon->setText(u8"\ue685");
        labelIcon->setPosition(12, 6);
        labelIcon->getRenderer()->setTextSize(22);
        auto renderer = labelIcon->getRenderer();
        renderer->setFont(icon);
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

    tgui::Button::Ptr buttonClose = tgui::Button::create();
    buttonClose->setPosition("100%", 0);
    buttonClose->setOrigin(1.0f, 0.f);
    buttonClose->setSize(50, 40);
    auto renderer = buttonClose->getRenderer();
    renderer->setBorders(tgui::Borders( 0,0,0,0 ));
    renderer->setFont(icon);
    renderer->setTextSize(17);
    buttonClose->setText(u8"\ue6e7");
    buttonClose->onClick.connect(&WindowMain::close, this);
    gui->add(buttonClose);


    auto buttonMaximize = tgui::Button::copy(buttonClose);
    buttonMaximize->setSize(bindSize(buttonClose));    
    buttonMaximize->setPosition({ tgui::bindLeft(buttonClose), tgui::bindTop(buttonClose) });
    buttonMaximize->setText(u8"\ue6e5");
    gui->add(buttonMaximize);

    auto buttonMinimize = tgui::Button::copy(buttonMaximize);
    buttonMinimize->setSize(bindSize(buttonMaximize));
    buttonMinimize->setPosition({ tgui::bindLeft(buttonMaximize), tgui::bindTop(buttonMaximize) });
    buttonMinimize->setText(u8"\ue6e8");
    gui->add(buttonMinimize);

    auto grid = tgui::Grid::create();
    grid->setPosition(12, 66);
    grid->setSize(356,300);
    

    auto labelCalendar1 = tgui::Label::create();
    labelCalendar1->setText(L"一");
    labelCalendar1->getRenderer()->setTextSize(20);
    auto lr = labelCalendar1->getRenderer();
    lr->setTextColor(tgui::Color(120, 120, 120));
    grid->addWidget(labelCalendar1, 0, 0);

    auto labelCalendar2 = tgui::Label::copy(labelCalendar1);
    labelCalendar2->setText(L"二");
    grid->addWidget(labelCalendar2, 0, 1);

    auto labelCalendar3 = tgui::Label::copy(labelCalendar1);
    labelCalendar3->setText(L"三");
    grid->addWidget(labelCalendar3, 0, 2);

    auto labelCalendar4 = tgui::Label::copy(labelCalendar1);
    labelCalendar4->setText(L"四");
    grid->addWidget(labelCalendar4, 0, 3);

    gui->add(grid);
    gui->mainLoop();
}
WindowMain::~WindowMain() {

}

bool WindowMain::isPosInCaption(const POINT& mousePos, const RECT& winRect) {
	if (mousePos.y < winRect.top+50 && mousePos.x < winRect.right - 150) {
		return true;
	}
	return false;
}