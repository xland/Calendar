#include <QPaintEvent>
#include <QPainter>
#include <QJsonArray>

#include "Menu.h"
#include "Skin.h"
#include "Util.h"
#include "DayBtn.h"

DayBtn::DayBtn(const int& index, QWidget* parent) : BtnBase(parent), index{ index }
{
    int lineNum = index / 7;
    int colNum = index % 7;
    int w = (parent->width() - 20) / 7;
    int h = 38;
    setGeometry(colNum * w+10, lineNum * h+78, w, h);
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
    auto r = rect().adjusted(1, 2, -1, -2);
    if (isActive) {
        painter.setBrush(skin->dayActive);
        painter.setPen(Qt::NoPen);
        painter.drawRect(r);
    }
    else if (isToday) {
        painter.setBrush(Qt::NoBrush);
        painter.setPen(skin->dayActive);
        painter.drawRect(r);
    }
    if (!isActive && isHover && !Menu::get()->isVisible()) {
        painter.setBrush(skin->dayHover);
        painter.setPen(Qt::NoPen);
        painter.drawRect(r);
    }
    auto font = Util::getTextFont(12);
    painter.setFont(*font);
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
    textRect.setTop(textRect.top() + 4);
    QTextOption option;
    option.setAlignment(Qt::AlignHCenter);
    painter.drawText(textRect, QString::number(day.day()), option);

    font->setPixelSize(10);
    painter.setFont(*font);
    textRect.setTop(textRect.top() + 16);
    if (isActive) {
        painter.setPen(QColor(255,255,255));
    }
    else if (isToday) {
        painter.setPen(skin->dayActive);
    }
    else {
        painter.setPen(isCurMonth ? skin->lunar : skin->lunarNotCurMonth);
    }
    painter.drawText(textRect, lunar, option);

    QRect r1 = rect();
    auto x = r1.right() - 11;
    auto y = r1.top() + 14;

    //if (isActive) {
    //    painter.setPen(QColor(255,255,255));
    //}
    //else {
    //    painter.setPen(skin->dayWorking);
    //}
    //painter.drawText(QPoint(x, y), docStatus);

    if (hasSchdule) {    
        if (isActive) {
            painter.setBrush(QColor(255, 255, 255));
        }
        else {
            painter.setBrush(skin->dot);
        }
        painter.setPen(Qt::NoPen);
        
        QRect r2(textRect.width() / 2 - 2, textRect.bottom() - 6, 4, 4);
        painter.drawEllipse(r2);
    }
}

void DayBtn::onClick()
{
    if (Menu::get()->isVisible()) return;
}
