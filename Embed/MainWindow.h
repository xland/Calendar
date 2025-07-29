#pragma once
#include "Windows.h"
#include <QtWidgets/QMainWindow>
#include <QJsonObject>

class YearBar;
class WeekBar;
class DayBtn;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:    
    ~MainWindow();
    void updateData(const QDate& day);
    static RAWINPUT* getRawInput(HRAWINPUT lParam);
    static void init();
    static MainWindow* get();
public:
    QList<DayBtn*> dayBtns;
    bool isEnter{ false };
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    MainWindow(QWidget* parent = nullptr);
    void onEmbedMouseMove();
    void onEmbedMousePress();
    void onEmbedLeaveWindow();
    void embed();
    static LRESULT CALLBACK processMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
    YearBar* yearBar;
    WeekBar* weekBar;
};
