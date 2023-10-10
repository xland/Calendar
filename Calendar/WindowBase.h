#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class WindowBase
{
public:
	WindowBase();
	~WindowBase();
	void initWindow();
	virtual bool isPosInCaption(const POINT& mousePos, const RECT& winRect) { return false; };
	void close();
	static std::map<HWND, WindowBase*> wndMap;
	HWND hwnd;
	tgui::Gui* gui;
	sf::RenderWindow* sfWin;
protected:
private:
};

