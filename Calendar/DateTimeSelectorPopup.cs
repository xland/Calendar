using System.Linq;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using Avalonia.Layout;
using Avalonia.Media;

namespace Calendar;

public class DateTimeSelectorPopup:ContentControl
{
    public DateTimeSelectorPopup()
    {
        Width = 280;
        Height = 250;
        var border = new Border
        {
            BorderThickness = new Thickness(1),
            BorderBrush = new SolidColorBrush(new Color(255,200,200,200)),
            CornerRadius = new CornerRadius(3),
        };
        Content = border;

        var grid = new Grid();
        grid.ColumnDefinitions.AddRange(
            Enumerable.Range(0, 6).Select(_ => new ColumnDefinition { Width = GridLength.Star })
        );
        grid.RowDefinitions.AddRange(
            Enumerable.Range(0, 7).Select(_ => new RowDefinition { Height = GridLength.Star })
        );
        border.Child = grid;
        
        for (int i = 0; i < 7; i++)
        {
            var text = new TextBlock
            {
                Text = "2025年",
                VerticalAlignment = VerticalAlignment.Center, // 文本垂直居中
                TextAlignment = TextAlignment.Center, // 文本水平居中
            };
            var b = new Border
            {
                Child = text,
                HorizontalAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch,
                BorderThickness = new  Thickness(0,0,1,0),
                BorderBrush = new SolidColorBrush(new Color(255,200,200,200)),
                Background = i == 3?new SolidColorBrush(new Color(255,230,240,250)):new SolidColorBrush(Colors.Transparent),
            };
            Grid.SetColumn(b, 0);
            Grid.SetRow(b,i);
            grid.Children.Add(b); 
        }
        
        for (int i = 0; i < 7; i++)
        {
            var text = new TextBlock
            {
                Text = "12月",
                VerticalAlignment = VerticalAlignment.Center, // 文本垂直居中
                TextAlignment = TextAlignment.Center, // 文本水平居中
            };
            var b = new Border
            {
                Child = text,
                HorizontalAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch, // Border 填充整个单元格
                BorderThickness = new  Thickness(0,0,1,0),
                BorderBrush = new SolidColorBrush(new Color(255,200,200,200)),
                Background = i == 3?new SolidColorBrush(new Color(255,230,240,250)):new SolidColorBrush(Colors.Transparent),
            };
            Grid.SetColumn(b, 1);
            Grid.SetRow(b,i);
            grid.Children.Add(b); 
        }
        
        
        for (int i = 0; i < 7; i++)
        {
            var text = new TextBlock
            {
                Text = "12日",
                VerticalAlignment = VerticalAlignment.Center, // 文本垂直居中
                TextAlignment = TextAlignment.Center, // 文本水平居中
            };
            var b = new Border
            {
                Child = text,
                HorizontalAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch,
                BorderThickness = new  Thickness(0,0,1,0),
                BorderBrush = new SolidColorBrush(new Color(255,200,200,200)),
                Background = i == 3?new SolidColorBrush(new Color(255,230,240,250)):new SolidColorBrush(Colors.Transparent),
            };
            Grid.SetColumn(b, 2);
            Grid.SetRow(b,i);
            grid.Children.Add(b); 
        }
        
        for (int i = 0; i < 7; i++)
        {
            var text = new TextBlock
            {
                Text = "12时",
                VerticalAlignment = VerticalAlignment.Center, // 文本垂直居中
                TextAlignment = TextAlignment.Center, // 文本水平居中
            };
            var b = new Border
            {
                Child = text,
                HorizontalAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch,
                BorderThickness = new  Thickness(0,0,1,0),
                BorderBrush = new SolidColorBrush(new Color(255,200,200,200)),
                Background = i == 3?new SolidColorBrush(new Color(255,230,240,250)):new SolidColorBrush(Colors.Transparent),
            };
            Grid.SetColumn(b, 3);
            Grid.SetRow(b,i);
            grid.Children.Add(b); 
        }
        
        for (int i = 0; i < 7; i++)
        {
            var text = new TextBlock
            {
                Text = "12分",
                VerticalAlignment = VerticalAlignment.Center, // 文本垂直居中
                TextAlignment = TextAlignment.Center, // 文本水平居中
            };
            var b = new Border
            {
                Child = text,
                HorizontalAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch,
                BorderThickness = new  Thickness(0,0,1,0),
                BorderBrush = new SolidColorBrush(new Color(255,200,200,200)),
                Background = i == 3?new SolidColorBrush(new Color(255,230,240,250)):new SolidColorBrush(Colors.Transparent),
            };
            Grid.SetColumn(b, 4);
            Grid.SetRow(b,i);
            grid.Children.Add(b); 
        }
        
        for (int i = 0; i < 7; i++)
        {
            var text = new TextBlock
            {
                Text = "12秒",
                VerticalAlignment = VerticalAlignment.Center, // 文本垂直居中
                TextAlignment = TextAlignment.Center, // 文本水平居中
            };
            var b = new Border
            {
                Child = text,
                HorizontalAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch, // Border 填充整个单元格
                Background = i == 3?new SolidColorBrush(new Color(255,230,240,250)):new SolidColorBrush(Colors.Transparent),
            };
            Grid.SetColumn(b, 5);
            Grid.SetRow(b,i);
            grid.Children.Add(b); 
        }
    }
}