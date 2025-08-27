using System;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using Avalonia.Input;
using Avalonia.Interactivity;
using Avalonia.Layout;
using Avalonia.Media;

namespace Calendar;

public class Week:ContentControl
{
    public Week()
    {
        Height = 36;
        var ug = new UniformGrid();
        ug.Columns = 7;
        ug.Rows = 1;
        ug.Margin = new Thickness(10,4,10,0);

        string[] digits = [ "一", "二", "三", "四", "五", "六", "日"];

        var scb = new SolidColorBrush(new Color(255, 160, 160,160));
        for (var i = 0; i < 7; i++)
        {
            var tb = new TextBlock
            {
                Text = digits[i],
                Foreground = scb,
                VerticalAlignment = Avalonia.Layout.VerticalAlignment.Center,
                HorizontalAlignment = Avalonia.Layout.HorizontalAlignment.Center,
            };
            ug.Children.Add(tb);
        }
        
        Content = ug;
        
    }
}