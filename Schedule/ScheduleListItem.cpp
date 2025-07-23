#include "ScheduleListItem.h"
#include "Util.h"
#include "../Data/ScheduleModel.h"
#include "Eventer.h"

ScheduleListItem::ScheduleListItem(ScheduleModel* model, QWidget* parent) : QWidget(parent), model{model}
{
	setFixedHeight(28);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setCursor(Qt::PointingHandCursor);
}

ScheduleListItem::~ScheduleListItem()
{

}

void ScheduleListItem::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setFont(Util::getTextFont(12));
	auto r = rect();
	if (isSelected) {
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(206, 216, 246));
		painter.drawRect(r);
	}
	else if (isHover) {
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(230, 230, 230));
		painter.drawRect(r);
	}
	r.adjust(10, 0, -10, 0);
	QFontMetrics metrics(painter.font());
	QString elidedText = metrics.elidedText(model->JobInfo, Qt::ElideRight, r.width());
	painter.setPen(QColor(30, 30, 30));
	painter.setBrush(Qt::NoBrush);
	painter.drawText(r, Qt::AlignLeft|Qt::AlignVCenter, elidedText);
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
		update();
	}
}

void ScheduleListItem::mousePressEvent(QMouseEvent* event)
{
	isSelected = !isSelected;
	Eventer::get()->fire("updateData", model);
	update();
	emit click();
}

