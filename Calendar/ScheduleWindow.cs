using System;
using Avalonia.Controls;
using Avalonia.Layout;
using Avalonia.Media;
using Avalonia.Platform;

namespace Calendar;

public class ScheduleWindow: Window
{
    public ScheduleWindow()
    {
        Title = "日程列表";
        Icon = new WindowIcon(AssetLoader.Open(new Uri("avares://Calendar/Res/logo.ico")));
        WindowStartupLocation = WindowStartupLocation.CenterScreen;
        Width = 900; Height = 600;
        var grid = new Grid();
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(220) });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(3)});
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Star });

        var left = new ScheduleList
        {
            HorizontalAlignment = HorizontalAlignment.Stretch
        };
        Grid.SetColumn(left, 0);
        grid.Children.Add(left);

        var spliter = new GridSplitter
        {
            Background = new SolidColorBrush(new Color(255, 122, 122, 222)),
            ResizeBehavior = GridResizeBehavior.PreviousAndNext,
            ResizeDirection = GridResizeDirection.Columns,
            MaxWidth = 3,
            MinWidth = 3,
        };
        Grid.SetColumn(spliter, 1);
        grid.Children.Add(spliter);

        var right = new ScheduleEditor();
        Grid.SetColumn(right, 2);
        grid.Children.Add(right);
        
        Content = grid;
    }
}