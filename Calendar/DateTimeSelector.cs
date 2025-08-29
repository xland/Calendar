using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using Avalonia.Input;
using Avalonia.Layout;
using Avalonia.Media;
using System;
using System.Collections.Generic;
using static System.Net.Mime.MediaTypeNames;

namespace Calendar;

public class DateTimeSelector:ContentControl
{

    private Popup _popup;
    private TextBlock text;
    public DateTimeSelector()
    {
        Cursor = new Cursor(StandardCursorType.Hand);
        _popup = new Popup
        {
            Placement = PlacementMode.Center, // 弹出位置
            PlacementTarget = this, 
            IsLightDismissEnabled = true,
        };
        PointerPressed += OnPointerPressed;
        _popup.Closed += OnPopupClosed;


        text = new TextBlock
        {
            Text = "2025-12-12 12:12:12",
            VerticalAlignment = VerticalAlignment.Center, // 文本垂直居中
            TextAlignment = TextAlignment.Center, // 文本水平居中
        };
        var b = new Border
        {
            Child = text,
            HorizontalAlignment = HorizontalAlignment.Center,
            VerticalAlignment = VerticalAlignment.Center,
            CornerRadius = new CornerRadius(3),
            Background = new SolidColorBrush(new Color(255, 238, 238, 238)),
            Padding = new Thickness(8, 6, 8, 6),
        };
        Content = b;
        PointerEntered += (object? sender, PointerEventArgs e) => {
            b.Background = new SolidColorBrush(new Color(255, 218, 218, 218));
            e.Handled = true;
        };
        PointerExited += (object? sender, PointerEventArgs e) => {
            b.Background = new SolidColorBrush(new Color(255, 238, 238, 238));
            e.Handled = true;
        };

    }

    private void OnPointerPressed(object? sender, PointerPressedEventArgs e)
    {
        if (_popup.Child is null)
        {
            _popup.Child = new DateTimeSelectorPopup(DateTime.Now);
        }
        _popup.IsOpen = true;
    }
    private void OnPopupClosed(object? sender, EventArgs e)
    {
        var dtsp = _popup.Child as DateTimeSelectorPopup;
        text.Text = dtsp.SelectedTime.ToString("yyyy-MM-dd HH:mm:ss");
    }
}