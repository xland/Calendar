#include <QPaintEvent>
#include <QPainter>
#include <QJsonArray>

#include "DayBtn.h"
#include "../Util.h"
#include "../Schedule/DialogList.h"
#include "../Schedule/DialogEdit.h"
#include "../Data/DateModel.h"
#include "../Data/Dates.h"

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
    connect(Dates::get(), &Dates::datesChanged, this, [this]() {update(); });
}

DayBtn::~DayBtn()
{
	
}

void DayBtn::paintEvent(QPaintEvent* event)
{
    auto date = Dates::get()->dates[index];
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    auto r = rect().adjusted(1,1,-1,-1);
    if (isHover) {
        painter.setBrush(QColor(255, 255, 255, 128));
        painter.setPen(Qt::NoPen);
        painter.drawRect(r);
    }
    if (date->isToday) {
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(QColor(180, 60, 80),0.5));
        painter.drawRect(r);
        painter.setPen(QColor(240, 44, 56));
    }
    else {
        painter.setPen(date->isCurMonth ? QColor(31, 35, 41) : QColor(102, 102, 102));
    }

    auto& font = Util::getTextFont(12);
    painter.setFont(font);
    painter.setBrush(Qt::NoBrush);
    QRect textRect = rect();
    textRect.setTop(textRect.top() + 5);
    QTextOption option;
    option.setAlignment(Qt::AlignHCenter);
    painter.drawText(textRect, QString::number(date->date.day()), option);

    font.setPixelSize(10);
    painter.setFont(font);
    textRect.setTop(textRect.top() + 16);
    painter.drawText(textRect, date->lunar, option);

    if (date->hasSchedule) {
        if (!date->isToday) {
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
    auto date = Dates::get()->dates[index];
    if (date->hasSchedule) {
        auto dialogSchedule = new DialogList(date->date);
        dialogSchedule->show();
        dialogSchedule->activateWindow();
    }
    else {
        auto dialogEdit = new DialogEdit("", date->date);
        dialogEdit->show();
        dialogEdit->activateWindow();
    }
}
