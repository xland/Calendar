#include "DialogSetting.h"
#include "Menu.h"
#include "About.h"
#include "Setting.h"
#include "Donate.h"
#include "Author.h"

DialogSetting::DialogSetting(QWidget *parent) : QWidget(parent)
{
    setWindowIcon(QIcon(":/logo.ico"));
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(600, 500);
    setWindowTitle("应用设置");

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    auto menu = new Menu();
    layout->addWidget(menu);
    layout->addWidget(new Setting());
    connect(menu, &Menu::menuChanged, this, &DialogSetting::menuChanged);
    setLayout(layout);
}

DialogSetting::~DialogSetting()
{

}

void DialogSetting::menuChanged(QString menuText)
{
    auto l = layout();
    QLayoutItem* item = l->takeAt(1);
    if (item) {
        QWidget* widget = item->widget();
        if (widget) {
            widget->hide();
            widget->deleteLater();
        }
        delete item;
    }

    if (menuText == "设置") {
        l->addWidget(new Setting());
    }
    else if (menuText == "作者") {
        l->addWidget(new Author());
    }
    else if (menuText == "赞助") {
        l->addWidget(new Donate());
    }
    else if (menuText == "关于") {
        l->addWidget(new About());
    }
}

