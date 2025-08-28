using System;
using Avalonia.Controls;
using Avalonia.Layout;
using Avalonia.Media;
using Avalonia.Platform;

namespace Calendar;

public class ScheduleEdit: Window
{
    public ScheduleEdit()
    {
        Title = "日程列表";
        Icon = new WindowIcon(AssetLoader.Open(new Uri("avares://Calendar/Res/logo.ico")));
        WindowStartupLocation = WindowStartupLocation.CenterScreen;
        Width = 800; Height = 500;
        var grid = new Grid();
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Star });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(1)});
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Star });
        
        var border = new Border
        {
            Background = new SolidColorBrush(new Color(255,122,222,222)),
        };
        Grid.SetColumn(border, 0);
        grid.Children.Add(border);

        var spliter = new GridSplitter
        {
            Background = new SolidColorBrush(new Color(255, 122, 122, 222)),
            ResizeBehavior = GridResizeBehavior.PreviousAndNext,
            ResizeDirection = GridResizeDirection.Columns,
            HorizontalAlignment = HorizontalAlignment.Stretch,
            VerticalAlignment = VerticalAlignment.Stretch
        };
        Grid.SetColumn(spliter, 1);
        grid.Children.Add(spliter);
        
        var border2 = new Border
        {
            Background = new SolidColorBrush(new Color(255,122,222,122)),
        };
        Grid.SetColumn(border2, 2);
        grid.Children.Add(border2);
        
        Content = grid;
    }
}