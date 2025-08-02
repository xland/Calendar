#include <QVBoxLayout>
#include <QLabel>

#include "Donate.h"

Donate::Donate(QWidget *parent) : QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QPalette pal = palette();
	pal.setColor(QPalette::Window, QColor(255, 255, 255));
	setPalette(pal);
	setAutoFillBackground(true);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setContentsMargins(16, 16, 16, 16);
	layout->setSpacing(0);

    QLabel* label0 = new QLabel(this);
    label0->setText("您的支持是我不断前进的动力。谢谢！");
    label0->setStyleSheet("font-size: 14px;");
    layout->addWidget(label0);
    layout->addSpacing(12);

    QLabel* label1 = new QLabel(this);
    label1->setText("支付宝支付");
    label1->setStyleSheet("font-size: 14px;");
    layout->addWidget(label1);

    QLabel* label2 = new QLabel(this);
    label2->setFixedSize(160, 160);
    QPixmap pixmap1(":/alipay.jpg");
    pixmap1 = pixmap1.scaled(label2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label2->setPixmap(pixmap1);
    label2->setAlignment(Qt::AlignCenter);
    layout->addWidget(label2);
    layout->addSpacing(12);

    QLabel* label3 = new QLabel(this);
    label3->setText("微信支付");
    label3->setStyleSheet("font-size: 14px;");
    layout->addWidget(label3);

    QLabel* label4 = new QLabel(this);
    label4->setFixedSize(160, 160);
    QPixmap pixmap2(":/wechat.png");
    pixmap2 = pixmap2.scaled(label4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label4->setPixmap(pixmap2);
    label4->setAlignment(Qt::AlignCenter);
    layout->addWidget(label4);

    layout->addStretch();
}

Donate::~Donate()
{
}

