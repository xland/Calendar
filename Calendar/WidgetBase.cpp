#include "WidgetBase.h"
WidgetBase::WidgetBase(WindowBase* parent) :parent{ parent } {

}
WidgetBase::~WidgetBase() {

}
void WidgetBase::paint(BLContext* paintCtx) {

}


bool WidgetBase::MouseMove(const int& x, const int& y) {
    if (box.contains(x, y)) {
        if (!isMouseEnter) {
            isMouseEnter = true;
            if (onMouseEnter) {
                onMouseEnter(this);
            }
            return true;
        }
    }
    else
    {
        if (isMouseEnter) {
            isMouseEnter = false;
            if (onMouseOut) {
                onMouseOut(this);
            }
            return true;
        }
    }
    return false;
}
bool WidgetBase::MouseUp(const int& x, const int& y) {
    if (isMouseEnter) {
        if (onMouseUp) {
            onMouseUp(this);
        }
        return true;
    }
    return false;
}