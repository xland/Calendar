#include "MenuItem.h"
#include "../Util.h"

MenuItem::MenuItem(const QString& text, bool isSelected, QWidget* parent) : BtnBase(parent), text{ text }, isSelected{isSelected}
{
	setFixedHeight(32);
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

MenuItem::~MenuItem()
{

}

void MenuItem::paintEvent(QPaintEvent* event)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.setRenderHint(QPainter::TextAntialiasing, true);
	QColor hoverBg, textColor;
	if (isSelected) {
		hoverBg.setRgb(100, 120, 200);
		textColor.setRgb(255, 255, 255);
	}
	else {
		hoverBg.setRgb(200, 220, 250);
		textColor.setRgb(60, 60, 60);
	}
	if (isHover || isSelected) {
		p.setPen(Qt::NoPen);
		p.setBrush(hoverBg);
		p.drawRect(rect());
		p.setBrush(QColor(255,255,255));
		QPolygon polygon;
		polygon << QPoint(width()-5,height()/2) << QPoint(width(), height() / 2 - 4) << QPoint(width(), height() / 2 + 4);
		p.drawPolygon(polygon);
	}
	p.setPen(textColor);
	p.setBrush(Qt::NoBrush);
	p.setFont(Util::getTextFont(13));
	p.drawText(rect(), Qt::AlignCenter, text);
}

