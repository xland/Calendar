#include <QRect>
#include <QPainter>
#include <QJsonArray>

#include "MainWindow.h"
#include "Util.h"
#include "Skin.h"
#include "WeekBar.h"

WeekBar* weekBar;

WeekBar::WeekBar(QWidget *parent) : QWidget(parent)
{
	auto winWidth = parent->width();
	setGeometry(10, 38, winWidth-18, 24);
}

WeekBar::~WeekBar()
{
	weekBar = nullptr;
}

void WeekBar::init()
{
	if (!weekBar) {
		weekBar = new WeekBar(MainWindow::get());
	}
	weekBar->show();
}
void WeekBar::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setFont(Util::getTextFont(12));
	auto skin = Skin::get();
	painter.setPen(skin->week);
	auto w = width() / 7;
	for (int i = 0; i < 7; i++)
	{
		QRect r(i * w, 0, w, height());
		painter.drawText(r, Qt::AlignCenter, list[i]);
	}
}
