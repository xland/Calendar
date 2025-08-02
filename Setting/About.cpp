#include <QLabel>
#include <QVBoxLayout>
#include "About.h"
#include "../Res/Res.h"

About::About(QWidget *parent) : QWidget(parent)
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
    label0->setText(QString("版本号：%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH));
    layout->addWidget(label0);
    layout->addSpacing(12);

    QLabel* label1 = new QLabel(this);
    label1->setTextFormat(Qt::RichText);
    label1->setText(QString("项目地址：<a href=\"%1\">%2</a>").arg("https://github.com/xland/Calendar", "https://github.com/xland/Calendar"));
    label1->setOpenExternalLinks(true);
    label1->setStyleSheet("font-size: 14px;");
    layout->addWidget(label1);
    layout->addSpacing(12);

    QLabel* label2 = new QLabel(this);
    label2->setText("本项目于2023年9月20日第一次提交代码，作者承诺会持续维护下去。也希望大家多多支持。");
    label2->setWordWrap(true);
    label2->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(label2);

    layout->addStretch();
}

About::~About()
{
}

