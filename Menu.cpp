#include <QVBoxLayout>
#include <QMouseEvent>
#include <QTimer>
#include <QApplication>

#include "Menu.h"
#include "Skin.h"
#include "MainWindow.h"

Menu* menu;

Menu::Menu(QWidget *parent) : BtnBase(parent)
{
	setGeometry(parent->width() - 124, 40, 109, 136);
	installEventFilter(this);
	connect(this, &BtnBase::leave, this, &Menu::mouseLeave);
}

Menu::~Menu()
{
	menu = nullptr;
}

void Menu::init()
{
	if (!menu) {
		menu = new Menu(MainWindow::get());
		//menu->setData(obj);  //todo
	}
}

Menu* Menu::get()
{
	return menu;
}

void Menu::setData(const QJsonObject& obj)
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setSpacing(2);
	layout->setContentsMargins(4, 4, 4, 4);
	auto lang = obj["lang"].toObject();
	item0 = new MenuItem(QChar(0xe710), lang["setting"].toString(), menu);
	item1 = new MenuItem(QChar(0xe70a), lang["help"].toString(), menu);
	item2 = new MenuItem(QChar(0xe711), lang["advise"].toString(), menu);
	item3 = new MenuItem(QChar(0xe70d), lang["signout"].toString(), menu);
	connect(item0, &BtnBase::click, this, &Menu::menuClick0);
	connect(item1, &BtnBase::click, this, &Menu::menuClick1);
	connect(item2, &BtnBase::click, this, &Menu::menuClick2);
	connect(item3, &BtnBase::click, this, &Menu::menuClick3);
	layout->addWidget(item0);
	layout->addWidget(item1);
	layout->addWidget(item2);
	layout->addWidget(item3);
	setLayout(layout);
}

void Menu::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	auto skin = Skin::get();
	painter.setBrush(skin->menuBg);
	painter.setPen(Qt::NoPen);
	painter.drawRoundedRect(rect(), 4, 4);
}

void Menu::mouseLeave()
{
	QTimer::singleShot(600, [this]() {
		//todo
		//if (!isHover && !TitleBar::get()->menuBtn->isHover) {
		//	menu->hide();
		//}
	});
}

void Menu::menuClick0()
{
}

void Menu::menuClick1()
{
	system("start https://docs.hikvision.com/#/file/nodcnpCtQNbetShKAgO3RUcrHnr");
}

void Menu::menuClick2()
{
	system("start https://wj.hikvision.com.cn/wenjuan/#/answer-sheet?id=66dfa62380e065d458e2f400&isHeader=1&headerStyle=light");
}

void Menu::menuClick3()
{
	qApp->exit();
}
