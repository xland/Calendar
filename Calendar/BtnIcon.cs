using System;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using Avalonia.Input;
using Avalonia.Interactivity;
using Avalonia.Media;
using Avalonia.Threading;


namespace Calendar;

public class BtnIcon: BtnBase
{
    public BtnIcon()
    {
        var iconFont = (FontFamily)Application.Current.FindResource("IconFont");
        FontFamily = iconFont;
    }
}