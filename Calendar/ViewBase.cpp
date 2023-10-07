#include "ViewBase.h"
#include "WindowBase.h"

ViewBase::ViewBase(WindowBase* parent) :parent{ parent } {

}
ViewBase::~ViewBase() {

}

void ViewBase::mouseMove(const int& x, const int& y) {
    if (box.contains(x, y)) {
        if (isCursorHand) {
            SetCursor(LoadCursor(NULL, IDC_HAND));
        }
        if (!isMouseEnter) {
            isMouseEnter = true;
            if (onMouseEnter) {
                onMouseEnter(this);
            }
        }
    }
    else
    {
        if (isMouseEnter) {
            isMouseEnter = false;
            if (onMouseOut) {
                onMouseOut(this);
            }
        }
    }
}
void ViewBase::mouseUp(const int& x, const int& y) {
    if (isMouseEnter) {
        if (onMouseUp) {
            onMouseUp(this);
        }
    }
}
void ViewBase::mouseDown(const int& x, const int& y) {

}
void ViewBase::changeSize(const int& w, const int& h) {
    if (dockType == 1) {
        box.x0 = parent->w - (w - box.x0);
        box.x1 = parent->w - (w - box.x1);
    }
}