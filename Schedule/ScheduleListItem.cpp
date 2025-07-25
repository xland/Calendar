#include <QMouseEvent>

#include "../Data/ScheduleModel.h"
#include "../Data/Schedules.h"
#include "ScheduleEdit.h"
#include "ScheduleListItem.h"
#include "Util.h"
#include "Eventer.h"

ScheduleListItem::ScheduleListItem(ScheduleModel* model, QWidget* parent) : QWidget(parent), model{model}
{
	setFixedHeight(28);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setCursor(Qt::PointingHandCursor);
	setMouseTracking(true);

}

ScheduleListItem::~ScheduleListItem()
{

}

void ScheduleListItem::paintEvent(QPaintEvent* event)
{
	//QPainter painter(this);
	//painter.setRenderHint(QPainter::Antialiasing, true);
	//painter.setRenderHint(QPainter::TextAntialiasing, true);
	//painter.setFont(Util::getTextFont(12));
	//auto r = rect();
	//if (model->isSelected) {
	//	painter.setPen(Qt::NoPen);
	//	painter.setBrush(QColor(206, 216, 246));
	//	painter.drawRect(r);
	//}
	//else if (isHover) {
	//	painter.setPen(Qt::NoPen);
	//	painter.setBrush(QColor(230, 230, 230));
	//	painter.drawRect(r);
	//}
	//r.adjust(10, 0, -10, 0);
	//QFontMetrics metrics(painter.font());
	//QString elidedText = metrics.elidedText(model->JobInfo, Qt::ElideRight, r.width());
	//painter.setPen(QColor(30, 30, 30));
	//painter.setBrush(Qt::NoBrush);
	//painter.drawText(r, Qt::AlignLeft|Qt::AlignVCenter, elidedText);

	//if (isHover) {
	//	r = QRect(width() - 32, 0, 32, height());
	//	painter.setPen(Qt::NoPen);
	//	painter.setBrush(QColor(30, 30, 30,isHoverDel?80:40));
	//	painter.drawRect(r);
	//	painter.setPen(QColor(255, 255, 255));
	//	painter.setBrush(Qt::NoBrush);
	//	painter.setFont(Util::getIconFont(11));
	//	painter.drawText(r, Qt::AlignCenter, QChar(0xe604));
	//}
}

void ScheduleListItem::enterEvent(QEnterEvent* event)
{
	if (!isHover) {
		isHover = true;
		update();
	}
}

void ScheduleListItem::leaveEvent(QEvent* event)
{
	if (isHover) {
		isHover = false;
		isHoverDel = false;
		update();
	}
}

void ScheduleListItem::mouseMoveEvent(QMouseEvent* event)
{
	QRect r(width() - 32, 0, 32, height());
	auto pos = event->pos();
	bool flag{ false };
	flag = r.contains(pos);
	if (flag != isHoverDel) {
		isHoverDel = flag;
		update();
	}
}

void ScheduleListItem::mousePressEvent(QMouseEvent* event)
{
/*	if (isHoverDel) {
	}
	else{
		if (!model->isSelected) {
			model->isSelected = true;
			update();
			emit click();
			auto parent = topLevelWidget();
			auto tar = parent->findChild<ScheduleEdit*>();
			tar->updateData();
		}
	}*/	
}

void ScheduleListItem::showEvent(QShowEvent* event)
{
	QRect r(width() - 32, 0, 32, height());
	auto pos = mapFromGlobal(QCursor::pos());
	isHoverDel = r.contains(pos);
}

