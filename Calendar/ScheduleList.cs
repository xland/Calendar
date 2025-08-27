using System;
using Avalonia.Controls;
using Avalonia.Layout;
using Avalonia.Platform;

namespace Calendar;

public class ScheduleList: Window
{
    public ScheduleList()
    {
        Title = "日程列表";
        Icon = new WindowIcon(AssetLoader.Open(new Uri("avares://Calendar/Res/logo.ico")));
        Width = 900; Height = 600;
        var stackPanel = new StackPanel
        {
            Orientation = Orientation.Vertical
        };
        Content = stackPanel;
    }
}