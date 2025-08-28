using System.Collections.Generic;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using Avalonia.Input;
using Avalonia.Layout;
using Avalonia.Media;

namespace Calendar;

public class DateTimeSelector:ContentControl
{
    private List<TextBlock> textYear = new List<TextBlock>();
    private List<TextBlock> textMonth = new List<TextBlock>();
    private List<TextBlock> textDay = new List<TextBlock>();
    private List<TextBlock> textHour = new List<TextBlock>();
    private List<TextBlock> textMinute = new List<TextBlock>();
    private List<TextBlock> textSecond = new List<TextBlock>();
    private Popup _popup;  
    public DateTimeSelector()
    {
        _popup = new Popup
        {
            PlacementMode = PlacementMode.Center, // 弹出位置
            PlacementTarget = this, 
            Child = new DateTimeSelectorPopup(),
            //WindowManagerAddShadowHint = true,
            IsLightDismissEnabled = true,
        };
        PointerPressed += OnPointerPressed;
        Background = new SolidColorBrush(new Color(255,122,122,255));
        Content = "2025-12-12 12:12:12";
    }

    private void OnPointerPressed(object? sender, PointerPressedEventArgs e)
    {
        _popup.IsOpen = true;
    }
    
}