# EmbedCalendar

# 透明窗口的问题

尝试了两种方案：

1. WS_EX_LAYERED窗口

这种窗口不能作为桌面窗口的子窗口（它也不能有子窗口，因为它收不到WM_PAINT消息）

2. 通过模糊窗口达到了透明效果

```
if (!IsWindowsVistaOrGreater()) { return; }
BOOL is_composition_enable = false;
DwmIsCompositionEnabled(&is_composition_enable);
if (!is_composition_enable) { return; }
HRGN region = CreateRectRgn(0, 0, -1, -1);
DWM_BLURBEHIND bb = { 0 };
bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
bb.hRgnBlur = region;
bb.fEnable = TRUE;
DwmEnableBlurBehindWindow(hwnd, &bb);
DeleteObject(region);
```

3. 挖空窗口

```
HRGN hFullRgn = CreateRectRgn(0, 0, 2560, 1440);
HRGN hHoleRgn = CreateRectRgn(100, 100, 800, 600);
HRGN hFinalRgn = CreateRectRgn(0, 0, 0, 0); // 初始为空区域
CombineRgn(hFinalRgn, hFullRgn, hHoleRgn, RGN_DIFF); // 剩余部分
auto flag = SetWindowRgn(workerW, hFinalRgn, TRUE);
DeleteObject(hFullRgn);
DeleteObject(hHoleRgn);
```


得到桌面壁纸
附加自己UI
绘制到SHELLDLL_DefView的父窗口上
非常快的定时器检查壁纸的变化

窗口x,y,w,h屏幕坐标转化为窗口坐标
为SysListView32窗口的指定区域拍照：Photo1；
Photo2 = 窗口像素+Photo1
把Photo2绘制到SHELLDLL_DefView窗口上
定时重绘


可以给SHELLDLL_DefView绘图
但绘制的内容会盖住SysListView32的图标
此时再给SysListView32拍照的话，拍到的是窗口像素，而不是图标图像