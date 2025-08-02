#include <Windows.h>
#include <QWindow>
#include <QApplication>
#include "Moving.h"
#include "MainWindow.h"

namespace {
	HHOOK g_mouseHook;
	QPoint posSpan;
	LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
		if (nCode >= 0) {
			if (wParam == WM_MOUSEMOVE) {
				MSLLHOOKSTRUCT* pMouse = (MSLLHOOKSTRUCT*)lParam;
				auto wins = qApp->allWindows();
				foreach(QWindow * window, wins) {
					if (window->title() == "窗口移动中...") {
						auto hwnd = (HWND)window->winId();
						SetWindowPos(hwnd, NULL, pMouse->pt.x -posSpan.x(), pMouse->pt.y -posSpan.y(),
							0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
						break;
					}
				}
			}
			else if(wParam == WM_LBUTTONUP){
				UnhookWindowsHookEx(g_mouseHook);
				g_mouseHook = NULL;
				INPUT input = { 0 };
				input.type = INPUT_MOUSE;
				input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
				SendInput(1, &input, sizeof(INPUT));
				auto wins = qApp->allWindows();
				foreach(QWindow * window, wins) {
					if (window->title() == "窗口移动中...") {
						auto win = MainWindow::get();
						win->move(window->position());
						window->close();
						return 0;
					}
				}
			}
		}
		return CallNextHookEx(g_mouseHook, nCode, wParam, lParam);
	}
}
Moving::Moving(QWidget *parent) : QWidget(parent)
{
	setWindowIcon(QIcon(":/logo.ico"));
	setWindowModality(Qt::ApplicationModal);
	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
	setWindowTitle("窗口移动中...");
	setCursor(Qt::SizeAllCursor);
}

Moving::~Moving()
{

}

void Moving::paintEvent(QPaintEvent* event)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.setRenderHint(QPainter::TextAntialiasing, true);
	p.setPen(QColor(108, 142, 191));
	p.setBrush(QColor(218, 232, 252, 200));
	auto r = rect().adjusted(1,1,-1,-1);
	p.drawRoundedRect(r, 4, 4);
}

void Moving::showEvent(QShowEvent* event)
{
	auto hwnd = (HWND)windowHandle()->winId();
	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	posSpan.setX(cursorPos.x - windowRect.left);
	posSpan.setY(cursorPos.y - windowRect.top);
	g_mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);
}

void Moving::resetPos()
{
	auto pos = QCursor::pos() - posSpan;
	move(pos);
}
