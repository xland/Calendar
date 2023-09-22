#include "ViewBase.h"
ViewBase::ViewBase(WindowBase* parent) :parent{ parent } {

}
ViewBase::~ViewBase() {

}

void ViewBase::mouseMove(const int& x, const int& y) {
    if (box.contains(x, y)) {
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