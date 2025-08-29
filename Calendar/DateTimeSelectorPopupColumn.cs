using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using Avalonia.Input;
using Avalonia.Layout;
using Avalonia.Media;
using Avalonia.VisualTree;
using System;
using System.Collections.Generic;

namespace Calendar;

public class DateTimeSelectorPopupColumn:ContentControl
{
    private int columnIndex;
    private int hoverIndex = -1;
    private List<Border> borders = new List<Border>();
    private List<TextBlock> texts = new List<TextBlock>();
    public DateTimeSelectorPopupColumn(int columnIndex)
    {
        this.columnIndex = columnIndex;
        Cursor = new Cursor(StandardCursorType.Hand);

        PointerWheelChanged += OnPointerWheelChanged;
        PointerMoved += OnPointerMoved;
        PointerExited += OnPointerExited;
        PointerPressed += OnPointerPressed;

        var grid = new UniformGrid
        {
            Rows=7,
            Columns=1,
        };       
        Content = grid;

        for (int i = 0; i < 7; i++)
        {
            var text = new TextBlock
            {
                VerticalAlignment = VerticalAlignment.Center,
                TextAlignment = TextAlignment.Center,
                FontSize = 13,
            };
            texts.Add(text);
            var b = new Border
            {
                Child = text,
                HorizontalAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch,
                BorderThickness = new  Thickness(0,0, columnIndex != 5?1:0, 0),
                BorderBrush = new SolidColorBrush(new Color(255, 200, 200, 200)),
                Background = i==3? new SolidColorBrush(new Color(255, 230, 240, 250)) : new SolidColorBrush(Colors.Transparent),
            };
            borders.Add(b);
            grid.Children.Add(b);
        }
    }
    
    private void OnPointerWheelChanged(object? sender, PointerWheelEventArgs e)
    {
        //var pos = e.GetPosition(this);
        //var indexY = (int) (pos.Y / (Bounds.Height / 7));
        // years[indexY].Background = new SolidColorBrush(new Color(255,220,220,220));
        // setYearItem(e.Delta.Y > 0);

        var val = e.Delta.Y > 0 ? -1 : 1;
        var popup = this.FindAncestorOfType<DateTimeSelectorPopup>();
        popup.setDateTimeByWheel(columnIndex,val);
        e.Handled = true;
    }

    private void OnPointerMoved(object? sender, PointerEventArgs e)
    {
        var pos = e.GetPosition(this);
        var indexY = (int) (pos.Y / (Bounds.Height / 7));
        if(indexY == hoverIndex) return;
        if(hoverIndex != -1 && hoverIndex != 3)
        {
            borders[hoverIndex].Background = new SolidColorBrush(Colors.Transparent);
        }
        if(indexY != 3)
        {
            borders[indexY].Background = new SolidColorBrush(new Color(255, 240, 240, 240));
        }
        hoverIndex = indexY;
        e.Handled = true;
    }

    private void OnPointerExited(object? sender, PointerEventArgs e)
    {
        if(hoverIndex != -1 && hoverIndex != 3)
        {
            borders[hoverIndex].Background = new SolidColorBrush(Colors.Transparent);            
        }
        hoverIndex = -1;
    }

    public void SetDateTime(DateTime dateTime)
    {
        if (columnIndex == 0)
        {
            SetYear(dateTime.Year);
        }
        else if (columnIndex == 1)
        {
            SetMonth(dateTime.Month);
        }
        else if (columnIndex == 2)
        {
            var preMonth = dateTime.AddMonths(-1);
            var preDays = DateTime.DaysInMonth(preMonth.Year, preMonth.Month);
            var nextDays = DateTime.DaysInMonth(dateTime.Year, dateTime.Month);
            SetDay(dateTime.Day, preDays,nextDays);
        }
        else if (columnIndex == 3)
        {
            SetHour(dateTime.Hour);
        }
        else if (columnIndex == 4)
        {
            SetMinute(dateTime.Minute);
        }
        else if (columnIndex == 5)
        {
            SetSecond(dateTime.Second);
        }
    }
    private void SetYear(int year)
    {
        for (int i = 0; i < 7; i++)
        {
            var val = year + i - 3;
            texts[i].Text = val.ToString() + "年";
        }
    }
    private void SetMonth(int month)
    {
        for (int i = 0; i < 7; i++)
        {
            var val = month + i - 3;
            if(val <= 0) val = val + 12;
            if (val > 12) val = val - 12;
            texts[i].Text = val.ToString() + "月";
        }
    }
    private void SetDay(int day,int preMonthDateCount,int dateCount)
    {
        for (int i = 0; i < 7; i++)
        {
            var val = day + i - 3;
            if(val <= 0) val = val + preMonthDateCount;
            if (val > dateCount) val = val - dateCount;
            texts[i].Text = val.ToString() + "日";
        }
    }
    private void SetHour(int hour)
    {
        for (int i = 0; i < 7; i++)
        {
            var val = hour + i - 3;
            if(val <= 0) val = val + 24;
            if (val > 24) val = val - 24;
            texts[i].Text = val.ToString("D2") + "时";
        }
    }
    private void SetMinute(int minute)
    {
        for (int i = 0; i < 7; i++)
        {
            var val = minute + i - 3;
            if(val <= 0) val = val + 59;
            if (val > 59) val = val - 60;
            texts[i].Text = val.ToString("D2") + "分";
        }
    }
    private void SetSecond(int second)
    {
        for (int i = 0; i < 7; i++)
        {
            var val = second + i - 3;
            if(val <= 0) val = val + 59;
            if (val > 59) val = val - 60;
            texts[i].Text = val.ToString("D2") + "秒";
        }
    }

    private void OnPointerPressed(object? sender, PointerEventArgs e)
    {
        var popup = this.FindAncestorOfType<DateTimeSelectorPopup>();
        popup.setDateTimeByWheel(columnIndex, hoverIndex - 3);
        e.Handled = true;
        var parent = popup.Parent as Popup;
        parent.IsOpen = false;
    }
}