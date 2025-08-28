using System;
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

    private Popup _popup;  
    public DateTimeSelector()
    {
        _popup = new Popup
        {
            PlacementMode = PlacementMode.Center, // 弹出位置
            PlacementTarget = this, 
            IsLightDismissEnabled = true,
        };
        PointerPressed += OnPointerPressed;
        
        
        var text = new TextBlock
        {
            Text = "2025-12-12 12:12:12",
            VerticalAlignment = VerticalAlignment.Center, // 文本垂直居中
            TextAlignment = TextAlignment.Center, // 文本水平居中
        };
        var b = new Border
        {
            Child = text,
            HorizontalAlignment = HorizontalAlignment.Stretch,
            VerticalAlignment = VerticalAlignment.Stretch,
            Background = new SolidColorBrush(new Color(255,122,122,255)),
        };
        Content = b;
    }

    private void OnPointerPressed(object? sender, PointerPressedEventArgs e)
    {
        if (_popup.Child is null)
        {
            _popup.Child = new DateTimeSelectorPopup(DateTime.Now);
        }
        _popup.IsOpen = true;
    }
    
}