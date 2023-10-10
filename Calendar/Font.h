#pragma once
#include <TGUI/TGUI.hpp>
class Font
{
public:
	~Font();
	static void Init();
	static void Dispose();
	static tgui::Font* text;
	static tgui::Font* icon;
private:
};
