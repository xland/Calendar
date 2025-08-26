using System;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Layout;
using Avalonia.Media;
using Avalonia.Platform;

namespace Calendar;

public class MainWindow: Window
{
    public MainWindow()
    {
        Title = "Calendar";
        Icon = new WindowIcon(AssetLoader.Open(new Uri("avares://Calendar/Res/logo.ico")));
        Width = 370; Height = 300;
        MaxWidth = 370; MaxHeight = 300;
        MinHeight = 370; MinHeight = 300;
        Background = new SolidColorBrush(Colors.Transparent);
        SystemDecorations = SystemDecorations.None;
        CanResize = false;
        WindowStartupLocation = Avalonia.Controls.WindowStartupLocation.CenterScreen;

        var border = new Border
        {
            BorderThickness = new Thickness(0.6),
            BorderBrush = new SolidColorBrush(Avalonia.Media.Color.Parse("#66000000")),
            Background = new SolidColorBrush(Avalonia.Media.Color.Parse("#CCFFFFFF")),
            CornerRadius = new CornerRadius(3),
            Padding = new Thickness(0)
        };
        var stackPanel = new StackPanel
        {
            Orientation = Orientation.Vertical
        };
        var header = new Header();
        stackPanel.Children.Add(header);
        
        var dateBox = new DateBox();
        stackPanel.Children.Add(dateBox);
        
        border.Child = stackPanel;
        Content = border;
    }
}