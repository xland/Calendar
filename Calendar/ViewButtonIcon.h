#pragma once
#include "ViewBase.h"
#include <memory>
class ViewButtonIcon : public ViewBase
{
public:
	ViewButtonIcon(WindowBase* parent);
	~ViewButtonIcon();
	void paint(BLContext* paintCtx) override;
	static std::shared_ptr<ViewButtonIcon> createMinimizeBtn(WindowBase* parent);
	static std::shared_ptr<ViewButtonIcon> createMaximizeRestoreBtn(WindowBase* parent);
	static std::shared_ptr<ViewButtonIcon> createCloseBtn(WindowBase* parent);
	std::string text;
	double fontSize{18.0};
private:
};

