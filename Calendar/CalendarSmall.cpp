#include "CalendarSmall.h"
#include "CalendarModel.h"

CalendarSmall::CalendarSmall(){
	setPosition(20, 60);
	setSize(340, 260);
    initTitle();
    initDate();
}

CalendarSmall::Ptr CalendarSmall::create()
{
    return std::make_shared<CalendarSmall>();
}

CalendarSmall::~CalendarSmall() {

}

void CalendarSmall::initTitle() {
    std::array<tgui::String, 7> headerLableArr[]{ L"一",L"二",L"三",L"四",L"五",L"六",L"日" };
    auto labelCalendar1 = tgui::Label::create();
    labelCalendar1->setText(headerLableArr->at(0));
    labelCalendar1->getRenderer()->setTextSize(16);
    labelCalendar1->setHeight(30);
    auto lr = labelCalendar1->getRenderer();
    lr->setTextColor(tgui::Color(180, 180, 180));
    addWidget(labelCalendar1, 0, 0);
    for (size_t i = 1; i < 7; i++)
    {
        auto label = tgui::Label::copy(labelCalendar1);
        label->setText(headerLableArr->at(i));
        addWidget(label, 0, i);
    }
}

void CalendarSmall::initDate() {
    tgui::Button::Ptr btn = tgui::Button::create();
    auto renderer = btn->getRenderer();
    renderer->setBorders(tgui::Borders(0, 0, 0, 0));
    renderer->setTextSize(18);
    renderer->setBackgroundColor(tgui::Color(0, 0, 0, 0));
    renderer->setBackgroundColorDown(tgui::Color(240, 44, 56));
    renderer->setBackgroundColorHover(tgui::Color(240, 44, 56));
    renderer->setTextColorHover(tgui::Color(255, 255, 255));
    renderer->setTextColorDownHover(tgui::Color(255, 255, 255));
    btn->setMouseCursor(tgui::Cursor::Type::Hand);
    auto model = CalendarModel::get();
    if (!model->data[0].isInCurMonth) {
        renderer->setTextColor(tgui::Color(160, 160, 160));
    }
    renderer->setRoundedBorderRadius(3.f);
    btn->setSize("12%", "12%");
    btn->setText(tgui::String(model->data[0].day));
    addWidget(btn, 1, 0);
    unsigned index = 1;
    for (size_t y = 1; y < 7; y++)
    {
        for (size_t x = 0; x < 7; x++)
        {
            if (y == 1 && x == 0) {
                continue;
            }
            auto item = tgui::Button::copy(btn);
            item->setText(tgui::String(model->data[index].day));
            if (model->data[index].isInCurMonth) {
                item->getRenderer()->setTextColor(tgui::Color(80, 80, 80));
            }
            else
            {
                item->getRenderer()->setTextColor(tgui::Color(160, 160, 160));
            }
            addWidget(item, y, x);
            index += 1;
        }
    }
}