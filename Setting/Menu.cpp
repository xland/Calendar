#include "Menu.h"

#include "../Util.h"
#include "../BtnBase.h"

Menu::Menu(QWidget *parent) : QWidget(parent)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(218, 232, 252));
    setPalette(pal);
    setAutoFillBackground(true);

    setFixedWidth(160);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    initMenus(layout);
    layout->addStretch();
    setLayout(layout);
}

Menu::~Menu()
{

}

void Menu::menuClick()
{
    auto item = (MenuItem*)sender();
    if (item->isSelected) {
        return;
    }
    for (int i = 0; i < menus.size(); i++)
    {
        if (menus[i] == item) {
            menus[i]->isSelected = true;
            menus[i]->update();
            emit menuChanged(menus[i]->text);
        }
        else {
            if (menus[i]->isSelected) {
                menus[i]->isSelected = false;
                menus[i]->update();
            }
        }
    }
}

void Menu::initMenus(QVBoxLayout* layout)
{
    auto item = new MenuItem("设置", true);
    menus.append(item);
    layout->addWidget(item);
    connect(item, &BtnBase::click, this, &Menu::menuClick);

    item = new MenuItem("作者");
    menus.append(item);
    layout->addWidget(item);
    connect(item, &BtnBase::click, this, &Menu::menuClick);

    item = new MenuItem("赞助");
    menus.append(item);
    layout->addWidget(item);
    connect(item, &BtnBase::click, this, &Menu::menuClick);

    item = new MenuItem("关于");
    menus.append(item);
    layout->addWidget(item);
    connect(item, &BtnBase::click, this, &Menu::menuClick);
}


