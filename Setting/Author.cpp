#include "Author.h"

Author::Author(QWidget *parent) : QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QPalette pal = palette();
	pal.setColor(QPalette::Window, QColor(255, 255, 255));
	setPalette(pal);
	setAutoFillBackground(true);
}

Author::~Author()
{

}

