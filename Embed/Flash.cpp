#include "Flash.h"
#include "../Util.h"

Flash::Flash(QWidget *parent) : QWidget(parent)
{
	setWindowIcon(QIcon(":/logo.ico"));
	setWindowModality(Qt::ApplicationModal);
	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
	setFixedSize(500, 200);
	setWindowTitle("日程");
	setCursor(Qt::PointingHandCursor);
}

Flash::~Flash()
{

}

void Flash::paintEvent(QPaintEvent* event) 
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.setRenderHint(QPainter::TextAntialiasing, true);
	p.setPen(Qt::NoPen);
	p.setPen(QColor(108, 142, 191));
	p.setBrush(QColor(218, 232, 252,200));
	auto r = rect().adjusted(1, 80, -1, -1);
	p.drawRoundedRect(r,16,16);

	p.setFont(Util::getIconFont(80));
	p.setBrush(Qt::NoBrush);
	p.drawText(width()-106,114, QChar(0xe980));

	p.setFont(Util::getIconFont(38));
	p.setPen(QColor(59, 79, 129));
	p.drawText(r.adjusted(26, 6, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, QChar(0xe60b));
	
	p.setFont(Util::getTextFont(28));
	p.drawText(r.adjusted(68,0,0,0), Qt::AlignLeft|Qt::AlignVCenter, "日程窗口已嵌入桌面");
}

void Flash::init() 
{
	auto flash = new Flash();
	flash->show();
}

void Flash::mousePressEvent(QMouseEvent* event)
{
	this->close();
}

