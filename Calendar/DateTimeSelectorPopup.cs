using System;
using System.Collections.Generic;
using System.Linq;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using Avalonia.Input;
using Avalonia.Layout;
using Avalonia.Media;

namespace Calendar;

public class DateTimeSelectorPopup:ContentControl
{
    private DateTime _selectedTime;

    public DateTime SelectedTime
    {
        get
        {
            return _selectedTime;
        }
        set
        {
            _selectedTime = value;
        }
    }
    private List<Border> years = new  List<Border>();
    private List<Border> months = new  List<Border>();
    private List<Border> dates = new  List<Border>();
    private List<Border> hours = new  List<Border>();
    private List<Border> minutes = new  List<Border>();
    private List<Border> seconds = new  List<Border>();
    private Grid grid;
    public DateTimeSelectorPopup(DateTime selectedTime)
    {
        _selectedTime = selectedTime;
        Width = 280;
        Height = 250;
        PointerWheelChanged += OnPointerWheelChanged;
        PointerMoved += OnPointerMoved;
        initGrid();
        initItem();
        
    }

    private void initGrid()
    {
        var border = new Border
        {
            BorderThickness = new Thickness(1),
            BorderBrush = new SolidColorBrush(new Color(255,200,200,200)),
            CornerRadius = new CornerRadius(3),
        };
        Content = border;

        grid = new Grid();
        grid.ColumnDefinitions.AddRange(
            Enumerable.Range(0, 6).Select(_ => new ColumnDefinition { Width = GridLength.Star })
        );
        grid.RowDefinitions.AddRange(
            Enumerable.Range(0, 7).Select(_ => new RowDefinition { Height = GridLength.Star })
        );
        border.Child = grid;
    }

    private void setYearItem(bool isWheelUp)
    {
        if (isWheelUp)
        {
            SelectedTime = _selectedTime.AddYears(-1);
        }
        else
        {
            SelectedTime = _selectedTime.AddYears(1);
        }
        
    }
    
    private void initItem()
    {
        for (int i = 0; i < 7; i++)
        {
            var year = _selectedTime.Year + i - 3;
            var text = new TextBlock
            {
                Text = year.ToString()+"年",
                VerticalAlignment = VerticalAlignment.Center,
                TextAlignment = TextAlignment.Center,
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
            years.Add(b);
            Grid.SetColumn(b, 0);
            Grid.SetRow(b,i);
            grid.Children.Add(b); 
        }
        
        for (int i = 0; i < 7; i++)
        {
            var text = new TextBlock
            {
                VerticalAlignment = VerticalAlignment.Center,
                TextAlignment = TextAlignment.Center,
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
            months.Add(b);
            Grid.SetColumn(b, 1);
            Grid.SetRow(b,i);
            grid.Children.Add(b); 
        }
        
        
        for (int i = 0; i < 7; i++)
        {
            var text = new TextBlock
            {
                VerticalAlignment = VerticalAlignment.Center,
                TextAlignment = TextAlignment.Center,
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
            dates.Add(b);
            Grid.SetColumn(b, 2);
            Grid.SetRow(b,i);
            grid.Children.Add(b); 
        }
        
        for (int i = 0; i < 7; i++)
        {
            var text = new TextBlock
            {
                VerticalAlignment = VerticalAlignment.Center,
                TextAlignment = TextAlignment.Center,
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
            hours.Add(b);
            Grid.SetColumn(b, 3);
            Grid.SetRow(b,i);
            grid.Children.Add(b); 
        }
        
        for (int i = 0; i < 7; i++)
        {
            var text = new TextBlock
            {
                VerticalAlignment = VerticalAlignment.Center,
                TextAlignment = TextAlignment.Center,
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
            minutes.Add(b);
            Grid.SetColumn(b, 4);
            Grid.SetRow(b,i);
            grid.Children.Add(b); 
        }
        
        for (int i = 0; i < 7; i++)
        {
            var text = new TextBlock
            {
                VerticalAlignment = VerticalAlignment.Center,
                TextAlignment = TextAlignment.Center,
            };
            var b = new Border
            {
                Child = text,
                HorizontalAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch, 
                Background = i == 3?new SolidColorBrush(new Color(255,230,240,250)):new SolidColorBrush(Colors.Transparent),
            };
            seconds.Add(b);
            Grid.SetColumn(b, 5);
            Grid.SetRow(b,i);
            grid.Children.Add(b); 
        }
    }

    private void OnPointerWheelChanged(object? sender, PointerWheelEventArgs e)
    {
        var pos = e.GetPosition(this);
        var indexX = (int) (pos.X / (this.Width / 6));
        var indexY = (int) (pos.Y / (this.Height / 7));
        if (indexX == 0)
        {
            years[indexY].Background = new SolidColorBrush(new Color(255,220,220,220));
            setYearItem(e.Delta.Y > 0);
        }
        e.Handled = true;
    }

    private void OnPointerMoved(object? sender, PointerEventArgs e)
    {
        var pos = e.GetPosition(this);
        var indexY = (int) (pos.Y / (this.Height / 7));
        if(indexY == 3 ) return;
        var indexX = (int) (pos.X / (this.Width / 6));
        if (indexX == 0)
        {
            for (int i = 0; i < 7; i++)
            {
                if (i == 3)
                {
                    years[i].Background = new SolidColorBrush(new Color(255,230,240,250));
                }
                else if (i == indexY)
                {
                    years[i].Background = new SolidColorBrush(new Color(255,220,220,220));
                }
                else
                {
                    years[i].Background = new SolidColorBrush(new Color(255,255,255,255));
                }
            }
        }
        e.Handled = true;
    }
}