#include <QFont>
#include <QFontDatabase>
#include <Windows.h>
#include <windowsx.h>
#include <QVBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QWindow>
#include <QEvent>
#include <QTimer>
#include <QApplication>

#include "Skin.h"
#include "MainWindow.h"
#include "BtnBase.h"
#include "YearBar.h"
#include "WeekBar.h"
#include "DayBtn.h"
#include "Util.h"
#include "TipInfo.h"

namespace {
    WNDPROC oldProc;
    MainWindow* win;
    bool isEmbeded{ true };
}
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_QuitOnClose, false);
    setAttribute(Qt::WA_TranslucentBackground, true);
    updateData(); //todo
    if (isEmbeded) {
        embed();
    }
}
MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    auto skin = Skin::get();
    painter.setBrush(skin->bg);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), 4, 4);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{

}

void MainWindow::switchEmbed()
{
    if (isEmbeded) {
        auto hwnd = (HWND)winId();
        SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)oldProc);
        SetParent(hwnd, nullptr);
    }
    delete win;
    win = nullptr;
    isEmbeded = !isEmbeded;
}


void MainWindow::onEmbedMouseMove()
{
    auto pos = mapFromGlobal(QCursor::pos());
    auto children = findChildren<BtnBase*>();
    auto flag1{ false };
    for (auto& child:children)
    {
        auto rect = QRect(child->mapTo(this, QPoint(0, 0)), child->size());;
        if (rect.contains(pos)) {
            child->enterEvent(nullptr);
        }
        else {
            child->leaveEvent(nullptr);
        }
    }
}

void MainWindow::onEmbedMousePress()
{
    auto pos = mapFromGlobal(QCursor::pos());
    auto child = dynamic_cast<BtnBase*>(childAt(pos));
    if (!child) return;
    //todo
    //QMouseEvent e(QEvent::MouseButtonPress, QPointF(0, 0), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    //child->mousePressEvent(&e);
}

void MainWindow::onEmbedLeaveWindow()
{
    if (!isEnter) return;
    auto children = findChildren<BtnBase*>();
    for (auto& child : children)
    {
        child->leaveEvent(nullptr);
    }
    isEnter = false;
}

void MainWindow::embed()
{
    auto workerW = Util::getWorkerW();
    auto hwnd = (HWND)winId();
    SetParent(hwnd, workerW);
    //QTimer::singleShot(1000, [hwnd]() {
        RAWINPUTDEVICE rids[1];
        rids[0].usUsagePage = 0x01;
        rids[0].usUsage = 0x02;
        rids[0].dwFlags = 0x00000100;
        rids[0].hwndTarget = hwnd;
        RegisterRawInputDevices(rids, 1, sizeof(rids[0]));
        oldProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)MainWindow::processMsg);
    //});

}

LRESULT CALLBACK MainWindow::processMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //auto win = (MainWindow*)QApplication::topLevelWidgets().first();  //  || !win 
    if (uMsg != WM_INPUT ) {
        return CallWindowProc(oldProc, hWnd, uMsg, wParam, lParam);
    }
    POINT globalPos;
    GetCursorPos(&globalPos);
    RECT rect;
    GetWindowRect(hWnd, &rect);
    if (globalPos.x < rect.left || globalPos.y < rect.top ||
        globalPos.x > rect.right || globalPos.y > rect.bottom) {
        win->onEmbedLeaveWindow();
        return CallWindowProc(oldProc, hWnd, uMsg, wParam, lParam);
    }

    HWND hwnd = WindowFromPoint(globalPos);
    WCHAR className[28];
    int len = GetClassName(hwnd, className, 28);
    if ((lstrcmp(TEXT("SysListView32"), className) != 0) &&
        (lstrcmp(TEXT("WorkerW"), className) != 0) &&
        (lstrcmp(TEXT("Progman"), className) != 0)) {
        win->onEmbedLeaveWindow();
        return CallWindowProc(oldProc, hWnd, uMsg, wParam, lParam);
    }
    win->isEnter = true;
    auto raw = getRawInput((HRAWINPUT)lParam);
    if (raw->header.dwType == RIM_TYPEMOUSE)
    {
        RAWMOUSE rawMouse = raw->data.mouse;
        if (rawMouse.usButtonFlags == RI_MOUSE_WHEEL)
        {
            auto wheelDelta = (short)rawMouse.usButtonData;
        }
        else {
            switch (rawMouse.ulButtons)
            {
            case RI_MOUSE_LEFT_BUTTON_DOWN:
            {
                win->onEmbedMousePress();
                break;
            }
            default:
            {
                win->onEmbedMouseMove();
                break;
            }
            }
        }
    }
    return CallWindowProc(oldProc, hWnd, uMsg, wParam, lParam);
}

RAWINPUT* MainWindow::getRawInput(HRAWINPUT lParam) {
    UINT dwSize = sizeof(RAWINPUT);
    static BYTE lpb[sizeof(RAWINPUT)];
    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
    return (RAWINPUT*)lpb;
}

void MainWindow::init()
{
    win = new MainWindow();
    win->show();
}

MainWindow* MainWindow::get()
{
    return win;
}

bool MainWindow::isEmbed()
{
    return isEmbeded;
}

void MainWindow::updateData()
{
    auto x = 100;
    auto y = 100;
    move(x, y);
    setFixedSize(QSize(372, 380));
    auto dayArr = Util::getOneMonthDay(QDate::currentDate());
    int i = 0;
    for (auto& dayData:dayArr)
    {
        auto day = new DayBtn(i, this);
        day->day = std::get<0>(dayData);
        day->lunar = "廿二";
        day->docStatus = "has";
        day->hasSchdule = false;
        day->isActive = false;
        day->isToday = false;
        day->isCurMonth = true;
        dayBtns.append(day);
        i += 1;

    }
}
