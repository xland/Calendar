
#include <QDateEdit>
#include <QPushButton>
#include <QHeaderView>

#include "DialogList.h"
#include "DialogEdit.h"
#include "../Data/Schedules.h"

DialogList::DialogList(const QDate& day, QWidget *parent) : QWidget(parent),
startTime{ QDateTime(day,QTime(0,0,0)) }, endTime{ QDateTime(day,QTime(23,59,59,999)) }
{
    setWindowIcon(QIcon(":/logo.ico"));
    setObjectName("DialogList");
    setStyleSheet("#DialogList{background:#ffffff;}");
	setWindowModality(Qt::ApplicationModal);
	setAttribute(Qt::WA_DeleteOnClose);
    resize(900, 600);
    setWindowTitle(QString("日程列表"));
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setSpacing(12);
    initSearchBar(layout);
    initList(layout);
    connect(Schedules::get(), &Schedules::scheduleChanged, this, &DialogList::initTableRows);
}

DialogList::~DialogList()
{

}

void DialogList::showEvent(QShowEvent* event)
{
    input->setFocus();
}

void DialogList::initSearchBar(QVBoxLayout* layout)
{
    auto searchBar = new QWidget(this);
    auto searchLayout = new QHBoxLayout(searchBar);
    searchLayout->setContentsMargins(0, 0, 0, 0);
    searchLayout->setSpacing(0);

    auto label1 = new QLabel("开始日期：");
    label1->setStyleSheet("font-size:13px;");
    searchLayout->addWidget(label1);

    QString calendarStyle{ R"(QDateEdit{border:1px solid gray;border-radius:0px;}QCalendarWidget{border:2px solid red;})" };
    calendar1 = new QDateEdit(this);
    calendar1->setCalendarPopup(true);
    calendar1->setFixedSize(100, 26);
    calendar1->setStyleSheet(calendarStyle);
    calendar1->setDate(startTime.date());
    searchLayout->addWidget(calendar1);
    searchLayout->addSpacing(30);

    auto label2 = new QLabel("结束日期：");
    label2->setStyleSheet("font-size:13px;");
    searchLayout->addWidget(label2);

    calendar2 = new QDateEdit(this);
    calendar2->setCalendarPopup(true);
    calendar2->setStyleSheet(calendarStyle);
    calendar2->setFixedSize(100,26);
    calendar2->setDate(endTime.date());
    searchLayout->addWidget(calendar2);
    searchLayout->addSpacing(30);

    auto label3 = new QLabel("日程关键字：");
    label3->setStyleSheet("font-size:13px;");
    searchLayout->addWidget(label3);

    input = new QLineEdit();
    input->setStyleSheet(R"(QLineEdit{border:1px solid gray;border-radius:0px;padding-left:4px;pandding-right:4px;})");
    input->setFixedSize(160,26);
    connect(input, &QLineEdit::returnPressed, this, [this](){ initTableRows(); });
    searchLayout->addWidget(input);
    searchLayout->addSpacing(8);

    auto btn1 = new QPushButton("搜索");
    QString btnStyle{"QPushButton {background-color:%1;color:#ffffff;border:none;border-radius:3px;font-size:13px;color:#ffffff}"
"QPushButton:hover{background-color: %2;}"};
    btn1->setCursor(Qt::PointingHandCursor);
    btn1->setStyleSheet(btnStyle.arg("#5D6B99").arg("#3B4F81"));
    btn1->setFixedSize(80, 26);
    connect(btn1, &QPushButton::clicked, [this](){ initTableRows(); });
    searchLayout->addWidget(btn1);
    searchLayout->addSpacing(8);
    searchLayout->addStretch();
    auto btn2 = new QPushButton("增加日程");
    btn2->setCursor(Qt::PointingHandCursor);
    btn2->setStyleSheet(btnStyle.arg("#267F00").arg("#166F00"));
    btn2->setFixedSize(80, 26);
    connect(btn2, &QPushButton::clicked, [this]() {(new DialogEdit(QString(),startTime.date()))->show();});
    searchLayout->addWidget(btn2);
    layout->addWidget(searchBar);
}

void DialogList::initList(QVBoxLayout* layout)
{
    table = new QTableWidget(0, 4);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->setColumnWidth(1, 100);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 120);
    table->verticalHeader()->setVisible(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setFocusPolicy(Qt::NoFocus);
    table->horizontalHeader()->setSectionsClickable(false);
    table->verticalHeader()->setSectionsClickable(false);
    table->setStyleSheet(R"(QTableView{gridline-color:#CCD5F0;border: 1px solid #CCD5F0;}QTableView::item{padding:0px;margin:0px;border:none;} 
QHeaderView::section{background-color:transparent;})");
    table->setHorizontalHeaderLabels(QStringList() << "日程内容" << "日程类型" << "开始时间" << "操作");   
    initTableRows();
    layout->addWidget(table);
}

void DialogList::initTableRows()
{
    for (int row = 0; row < table->rowCount(); ++row) {
        QWidget* widget = table->cellWidget(row, 3);
        if (widget) {
            widget->deleteLater();
        }
    }
    table->clearContents();
    auto data = Schedules::get()->getData(calendar1->date(),calendar2->date(), input->text().trimmed());
    table->setRowCount(data.size());
    for (int row = 0; row < data.size(); ++row) {
        auto st = QDateTime::fromSecsSinceEpoch(data[row]->FirstTime);
        table->setItem(row, 0, new QTableWidgetItem(data[row]->Schedule));
        table->setItem(row, 1, new QTableWidgetItem(getTypeStr(data[row]->RepeatType, st.date())));
        table->setItem(row, 2, new QTableWidgetItem(st.toString("yyyy-MM-dd hh:mm:ss")));
        initRowBtns(row, data[row]->Id);
    }
}

void DialogList::initRowBtns(const int& row, const QString& id)
{
    QString btnStyle{"QPushButton{background-color:%1;color:#ffffff;border:none;border-radius:3px;font-size:12px;}"
"QPushButton:hover{background-color:%2;}"};
    QPushButton* btn1 = new QPushButton("修改");    
    btn1->setFixedSize(50, 22);
    btn1->setStyleSheet(btnStyle.arg("#5D6B99").arg("#3B4F81"));
    btn1->setCursor(Qt::PointingHandCursor);
    connect(btn1, &QPushButton::clicked, [&id, this]() {editBtnClick(id);});

    QPushButton* btn2 = new QPushButton("删除");
    btn2->setFixedSize(50, 22);
    btn2->setStyleSheet(btnStyle.arg("#CE7C8F").arg("#B83E52"));
    btn2->setCursor(Qt::PointingHandCursor);
    connect(btn2, &QPushButton::clicked, [&id,this]() {delBtnClick(id); });

    QWidget* container = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(container);
    layout->setSpacing(6);
    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->setAlignment(Qt::AlignCenter); // 水平垂直都居中
    layout->setContentsMargins(0, 0, 0, 0);
    table->setCellWidget(row, 3, container);    
}



void DialogList::delBtnClick(const QString& id)
{
    ScheduleModel::del(id);
    initTableRows();
}

void DialogList::editBtnClick(const QString& id)
{
   auto de = new DialogEdit(id,QDate::currentDate());//第二个参数没用
   de->show();
}

QString DialogList::getTypeStr(const int& type, const QDate& date)
{
    QString typeStr;
    if (type == 0) {
        return "不重复";
    }
    else if (type == 1) {
        return "每天";
    }
    else if (type == 2) {
        return "每个工作日";
    }
    else if (type == 3) {
        static QString days[] = { "一", "二", "三", "四","五","六","日" };
        return QString("每周%1").arg(days[date.dayOfWeek() - 1]);
    }
    else if (type == 4) {
        return QString("每月第%1天").arg(date.day());
    }
    else if (type == 5) {
        return QString("每年%1月%2日").arg(QString::number(date.month()).trimmed(), QString::number(date.day()).trimmed());
    }
    return "";
}

