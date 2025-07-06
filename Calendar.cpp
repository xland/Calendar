#include <QVBoxLayout>
#include <QLabel>

#include "Calendar.h"
#include "TitleBar.h"
#include "Body.h"

Calendar::Calendar(QWidget *parent) : QMainWindow(parent)
{
	resize(800, 600);
	auto centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);
	auto layout = new QVBoxLayout(centralWidget);

	auto title = new TitleBar(centralWidget);
	auto body = new Body(centralWidget);
	layout->addWidget(title);
	layout->addWidget(body);
}

Calendar::~Calendar()
{}

