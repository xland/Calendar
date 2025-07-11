#pragma once
#include "Windows.h"
#include <QtWidgets/QMainWindow>
#include <QJsonObject>

class TitleBar;
class YearBar;
class WeekBar;
class DayBtn;
class SwitchBtn;
class ListBar;
class ListContent;
class TipInfo;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:    
    ~MainWindow();
    void switchEmbed();
    static RAWINPUT* getRawInput(HRAWINPUT lParam);
    static void init();
    static MainWindow* get();
    static bool isEmbed();
public:
    QList<DayBtn*> dayBtns;
    bool isEnter{ false };
protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
private:
    MainWindow(QWidget* parent = nullptr);
    void updateData();
    void onEmbedMouseMove();
    void onEmbedMousePress();
    void onEmbedLeaveWindow();
    void embed();
    static LRESULT CALLBACK processMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
    
};
