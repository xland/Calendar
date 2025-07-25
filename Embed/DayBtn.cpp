#include <QPaintEvent>
#include <QPainter>
#include <QJsonArray>

#include "Skin.h"
#include "DayBtn.h"
#include "../Util.h"
#include "../Schedule/DialogList.h"

DayBtn::DayBtn(const int& index, QWidget* parent) : BtnBase(parent), index{ index }
{
    int lineNum = index / 7;
    int colNum = index % 7;
    int w = (parent->width() - 20) / 7;
    int h = 40;
    setGeometry(colNum * w+10, lineNum * h+66, w, h);
    setMouseTracking(true);
    setCursor(Qt::CursorShape::PointingHandCursor);
    connect(this, &DayBtn::click, this, &DayBtn::onClick);
}

DayBtn::~DayBtn()
{
	
}

void DayBtn::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    auto skin = Skin::get();
    auto r = rect().adjusted(1,1,-1,-1);
    auto isToday = day == QDate::currentDate();
    if (isActive) {
        painter.setBrush(skin->dayActive);
        painter.setPen(Qt::NoPen);
        painter.drawRect(r);
    }
    else if (isToday) {
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(QColor(180, 60, 80),0.5));
        painter.drawRect(r);
    }
    if (!isActive && isHover) {
        painter.setBrush(skin->dayHover);
        painter.setPen(Qt::NoPen);
        painter.drawRect(r);
    }
    auto& font = Util::getTextFont(12);
    painter.setFont(font);
    painter.setBrush(Qt::NoBrush);
    if (isActive) {
        painter.setPen(QColor(255, 255, 255));
    }
    else if (isToday) {
        painter.setPen(skin->dayActive);
    }
    else {
        painter.setPen(isCurMonth ? skin->day : skin->dayNotCurMonth);
    }
    QRect textRect = rect();
    textRect.setTop(textRect.top() + 5);
    QTextOption option;
    option.setAlignment(Qt::AlignHCenter);
    painter.drawText(textRect, QString::number(day.day()), option);

    font.setPixelSize(10);
    painter.setFont(font);
    textRect.setTop(textRect.top() + 16);
    if (isActive) {
        painter.setPen(QColor(255,255,255));
    }
    else if (isToday) {
        painter.setPen(skin->dayActive);
    }
    else {
        painter.setPen(isCurMonth ? skin->day : skin->dayNotCurMonth);
    }
    painter.drawText(textRect, lunar, option);

    if (hasSchdule) {    
        if (!isToday) {
            painter.setBrush(Qt::NoBrush);
            painter.setPen(QPen(QColor(140, 140, 140), 0.5));
            painter.drawRect(r);
        }
        painter.setBrush(QColor(180, 60, 80));
        painter.setPen(Qt::NoPen);
        auto tr = r.bottomRight();
        tr.setY(tr.y() + 1); tr.setX(tr.x() + 1);
        QPolygon polygon;
        polygon << tr << QPoint(tr.x()-8,tr.y()) << QPoint(tr.x(), tr.y()-8);
        painter.drawPolygon(polygon);
    }
}

void DayBtn::onClick()
{
    auto dialogSchedule = new DialogList(day);
    dialogSchedule->show();
    dialogSchedule->activateWindow();

}
