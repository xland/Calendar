#include "Util.h"
#include "ScheduleSearch.h"

ScheduleSearch::ScheduleSearch(QWidget *parent) : QWidget(parent)
{
	setFixedHeight(30);
	input = new QLineEdit(this);
	input->setFixedHeight(29);
	input->setStyleSheet("border:none;padding-left:10px;");
	input->setPlaceholderText("搜索当日日程...");
}

ScheduleSearch::~ScheduleSearch()
{}

void ScheduleSearch::resizeEvent(QResizeEvent * event)
{
	input->setFixedWidth(width() - 36);
}

void ScheduleSearch::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setBrush(QColor(255, 255, 255));
	painter.setPen(Qt::NoPen);
	painter.drawRect(rect());
	painter.setPen(QPen(QColor(120, 120, 120), 1));
	painter.drawLine(0, height(), width(), height());

	painter.setFont(Util::getIconFont(13));
	painter.drawText(QRect(width()-36,0,36,30), Qt::AlignCenter, QChar(0xe6a6));
}

