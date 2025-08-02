#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Author.h"

Author::Author(QWidget *parent) : QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QPalette pal = palette();
	pal.setColor(QPalette::Window, QColor(255, 255, 255));
	setPalette(pal);
	setAutoFillBackground(true);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(0);

    QLabel* label1 = new QLabel(this);
    label1->setTextFormat(Qt::RichText);
    label1->setText(QString("知乎：<a href=\"%1\">%2</a>").arg("https://www.zhihu.com/people/liulun", "https://www.zhihu.com/people/liulun"));
    label1->setOpenExternalLinks(true);
    label1->setStyleSheet("font-size: 14px;");
    layout->addWidget(label1);
    layout->addSpacing(12);

    QLabel* label2 = new QLabel(this);
    label2->setTextFormat(Qt::RichText);
    label2->setText(QString("CSDN：<a href=\"%1\">%2</a>").arg("https://blog.csdn.net/liulun", "https://blog.csdn.net/liulun"));
    label2->setOpenExternalLinks(true);
    label2->setStyleSheet("font-size: 14px;");
    layout->addWidget(label2);
    layout->addSpacing(12);

    QLabel* label3 = new QLabel(this);
    label3->setTextFormat(Qt::RichText);
    label3->setText(QString("GitHub：<a href=\"%1\">%2</a>").arg("https://github.com/xland", "https://github.com/xland"));
    label3->setOpenExternalLinks(true);
    label3->setStyleSheet("font-size: 14px;");
    layout->addWidget(label3);
    layout->addSpacing(12);

    QLabel* label4 = new QLabel(this);
    label4->setText("公众号：桌面软件");
    label4->setStyleSheet("font-size: 14px;");
    layout->addWidget(label4);

    QLabel* label5 = new QLabel(this);
    label5->setFixedSize(160, 160);
    QPixmap pixmap1(":/gongzhonghao.jpg");
    pixmap1 = pixmap1.scaled(label5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label5->setPixmap(pixmap1);
    label5->setAlignment(Qt::AlignCenter);
    layout->addWidget(label5);
    layout->addSpacing(12);

    QLabel* label6 = new QLabel(this);
    label6->setText("作者微信");
    label6->setStyleSheet("font-size: 14px;");
    layout->addWidget(label6);

    QLabel* label7 = new QLabel(this);
    label7->setFixedSize(160, 160);
    QPixmap pixmap2(":/author.jpg");
    pixmap2 = pixmap2.scaled(label7->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation);
    label7->setPixmap(pixmap2);
    label7->setAlignment(Qt::AlignCenter);
    layout->addWidget(label7);

    layout->addStretch();
    setLayout(layout);
}

Author::~Author()
{

}
