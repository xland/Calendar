#include <QPainter>
#include "MainWindow.h"
#include "Util.h"
#include "Skin.h"
#include "TipInfo.h"

TipInfo* tipInfo;


TipInfo::TipInfo(QWidget *parent) : QWidget(parent)
{    
    setVisible(false);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

TipInfo::~TipInfo()
{
    tipInfo = nullptr;
}

void TipInfo::init()
{
    if (!tipInfo) {
        tipInfo = new TipInfo(MainWindow::get());
    }
}

TipInfo* TipInfo::get()
{
    return tipInfo;
}

void TipInfo::setText(const QString& text)
{
    this->text = text;
    QFontMetrics fm(Util::getTextFont(14));
    int textAdvance = fm.horizontalAdvance(text);
    setFixedSize(textAdvance + 18, 32);
}

void TipInfo::showInfo(const QPoint& pos)
{
    move(pos);
    this->show();
    this->raise();
}

void TipInfo::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    auto skin = Skin::get();
    painter.setBrush(skin->tipInfoBg);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), 4, 4);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(skin->tipInfo);
    painter.setFont(Util::getTextFont(14));
    painter.drawText(rect(), Qt::AlignCenter, text);
}
