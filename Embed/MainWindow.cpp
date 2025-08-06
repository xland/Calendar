#include <Windows.h>
#include <windowsx.h>
#include <QVBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QScreen>
#include <QWindow>
#include <QEvent>
#include <QApplication>

#include "MainWindow.h"
#include "BtnBase.h"
#include "YearBar.h"
#include "WeekBar.h"
#include "DayBtn.h"
#include "Alert.h"
#include "UpcomingItem.h"
#include "Upcomings.h"
#include "../Util.h"
#include "../Data/Schedules.h"
#include "../Data/TickTock.h"
#include "../Data/SettingModel.h"


namespace {
    WNDPROC oldProc;
    MainWindow* win;
}
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_QuitOnClose, false);
    setAttribute(Qt::WA_TranslucentBackground, true);
    upcomings = new Upcomings(this);
    for (int i = 0; i < 42; i++)
    {
        dayBtns.append(new DayBtn(i, this));
    }
    yearBar = new YearBar(this);
    weekBar = new WeekBar(this);
    embed();
}
MainWindow::~MainWindow()
{
}
void MainWindow::init()
{
    win = new MainWindow();
    win->show();
    TickTock::get()->start();
}

MainWindow* MainWindow::get()
{
    return win;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setBrush(QColor(255,255,255,153));
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect(), 4, 4);
}

void MainWindow::moveEvent(QMoveEvent* event)
{
    QMainWindow::moveEvent(event);
    auto setting = SettingModel::get();
    if (setting->X != pos().x() && setting->Y != pos().y()) {
        SettingModel::get()->updatePos(pos());
    }    
}

void MainWindow::onEmbedMouseMove()
{
    auto pos = mapFromGlobal(QCursor::pos());
    auto children = findChildren<BtnBase*>();
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
    auto gPos = QCursor::pos();
    auto pos = mapFromGlobal(gPos);
    auto child = dynamic_cast<BtnBase*>(childAt(pos));
    if (!child) return;
    QMouseEvent e(QEvent::MouseButtonPress, QPointF(1, 1), gPos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    child->mousePressEvent(&e);
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
    auto setting = SettingModel::get();
    if (setting->X == 999999 && setting->Y == 999999) {
        auto pos = screen()->geometry().topRight();
        move(pos.x() - width() - 80, pos.y() + 80);
    }
    else {
        move(setting->X, setting->Y);
    }
    auto workerW = Util::getWorkerW();
    auto hwnd = (HWND)winId();
    SetParent(hwnd, workerW);
    RAWINPUTDEVICE rids[1];
    rids[0].usUsagePage = 0x01;
    rids[0].usUsage = 0x02;
    rids[0].dwFlags = 0x00000100;
    rids[0].hwndTarget = hwnd;
    RegisterRawInputDevices(rids, 1, sizeof(rids[0]));
    oldProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)MainWindow::processMsg);
}

LRESULT CALLBACK MainWindow::processMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg != WM_INPUT ) {
        return CallWindowProc(oldProc, hWnd, uMsg, wParam, lParam);
    }
    POINT globalPos;
    GetCursorPos(&globalPos);
    RECT rect;
    GetWindowRect(hWnd, &rect);
    if (globalPos.x < rect.left || globalPos.y < rect.top || globalPos.x > rect.right || globalPos.y > rect.bottom) {
        win->onEmbedLeaveWindow();
        return CallWindowProc(oldProc, hWnd, uMsg, wParam, lParam);
    }

    HWND hwnd = WindowFromPoint(globalPos);
    WCHAR className[28];
    int len = GetClassName(hwnd, className, 28);
    if ((lstrcmp(TEXT("SysListView32"), className) != 0) && (lstrcmp(TEXT("WorkerW"), className) != 0) && (lstrcmp(TEXT("Progman"), className) != 0)) {
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
