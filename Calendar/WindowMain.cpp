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
        labelTitle->setText(L"ÈÕÀú");
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