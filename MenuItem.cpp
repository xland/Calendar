#include "MenuItem.h"
#include "Skin.h"
#include "Util.h"


MenuItem::MenuItem(const QChar& icon, const QString& text, QWidget *parent) : BtnBase(parent),
icon{ icon }, text{text}
{

}

MenuItem::~MenuItem()
{
	
}

void MenuItem::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	auto skin = Skin::get();
	if (isHover) {
		painter.setPen(Qt::NoPen);
		painter.setBrush(skin->menuHover);
		painter.drawRoundedRect(rect(), 4, 4);
	}

	painter.setPen(skin->menu);
	painter.setBrush(Qt::NoBrush);
	auto font = Util::getTextFont(14);
	painter.setFont(*font);
	painter.drawText(QPoint(30, 20), text);
	painter.setFont(Util::getIconFont(13));
	painter.drawText(QPoint(10, 20), icon);
}
