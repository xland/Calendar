using System;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Interactivity;
using Avalonia.Layout;
using Avalonia.Media;
using Avalonia.VisualTree;

namespace Calendar;

public class Header:UserControl
{
    public Header()
    {
        Height = 40;
        Background = new SolidColorBrush(Colors.Transparent);
        var grid = new Grid();
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Auto });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Auto });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Star });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Auto });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Auto });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Auto });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Auto });

        var labelDate = new TextBlock
        {
            Text = "2025年8月18日",
            VerticalAlignment = Avalonia.Layout.VerticalAlignment.Center,
            Padding = new Thickness(16,0,12,0),
        };
        Grid.SetColumn(labelDate, 0);
        grid.Children.Add(labelDate);
        
        var lunarDate = new TextBlock
        {
            Text = "润六月廿五",
            VerticalAlignment = Avalonia.Layout.VerticalAlignment.Center,
        };
        Grid.SetColumn(lunarDate, 1);
        grid.Children.Add(lunarDate);
        
        var border = new Border();
        Grid.SetColumn(border, 2);
        grid.Children.Add(border);

        var scb = new SolidColorBrush(Avalonia.Media.Color.Parse("#ddd"));
        var todayBtn = new BtnIcon
        {
            Content = "\uE667",
            Width = 28,
            Height = 26,
            HoveredColor = scb,
            PressedColor =  scb,
        };
        Grid.SetColumn(todayBtn, 3);
        grid.Children.Add(todayBtn);
        
        var leftBtn = new BtnIcon
        {
            Content = "\ue60e",
            Width = 28,
            Height = 26,
            HoveredColor = scb,
            PressedColor =  scb,
        };
        Grid.SetColumn(leftBtn, 4);
        grid.Children.Add(leftBtn);
        
        var rightBtn = new BtnIcon
        {
            Content = "\ue638",
            Width = 28,
            Height = 26,
            HoveredColor = scb,
            PressedColor =  scb,
        };
        Grid.SetColumn(rightBtn, 5);
        grid.Children.Add(rightBtn);
        
        var settingBtn = new BtnIcon
        {
            Content = "\ue643",
            Width = 28,
            Height = 26,
            HoveredColor = scb,
            PressedColor =  scb,
            Margin = new Thickness(0, 0, 12, 0),
        };
        Grid.SetColumn(settingBtn, 6);
        grid.Children.Add(settingBtn);
        
        
        Content = grid;

        PointerPressed += OnPointerPressed;
    }
    
    private void OnPointerPressed(object? sender, PointerPressedEventArgs e)
    {
        if (!e.GetCurrentPoint(this).Properties.IsLeftButtonPressed)
        {
            return;
        }
        var window = this.FindAncestorOfType<Window>();
        window?.BeginMoveDrag(e);
    }
}