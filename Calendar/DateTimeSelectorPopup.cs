using System;
using Avalonia;
using Avalonia.Controls;
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
    private Grid grid;
    public DateTimeSelectorPopup(DateTime selectedTime)
    {
        _selectedTime = selectedTime;
        Width = 280;
        Height = 250;
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
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(68) });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Star });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Star });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Star });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Star });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Star });
        border.Child = grid;
    }

    
    private void initItem()
    {
        for (int i = 0; i < 6; i++)
        {
            var dtspc = new DateTimeSelectorPopupColumn(i);
            dtspc.SetDateTime(_selectedTime);
            Grid.SetColumn(dtspc, i);
            grid.Children.Add(dtspc);
        }
    }
    public void setDateTimeByWheel(int columnIndex,int addVal)
    {
        if (columnIndex == 0)
        {
            SetYear(addVal);
        }
        else if (columnIndex == 1)
        {
            SetMonth(addVal);  
        }
        else if (columnIndex == 2)
        {
            SetDay(addVal);
        }
        else if (columnIndex == 3)
        {
            SelectedTime = SelectedTime.AddHours(addVal);
        }
        else if (columnIndex == 4)
        {
            SelectedTime = SelectedTime.AddMinutes(addVal);
        }
        else if (columnIndex == 5)
        {
            SelectedTime = SelectedTime.AddSeconds(addVal);
        }
        if(columnIndex < 3)
        {
            for(var i = 0; i < 3; i++)
            {
                var column = grid.Children[i] as DateTimeSelectorPopupColumn;
                column.SetDateTime(SelectedTime);
            }
        }
        else
        {
            var column = grid.Children[columnIndex] as DateTimeSelectorPopupColumn;
            column.SetDateTime(SelectedTime);
        }
    }

    public void SetYear(int addVal)
    {
        if (SelectedTime.Year == 1970 && addVal == -1) return;
        if (SelectedTime.Year == 2999 && addVal == 1) return;
        SelectedTime = SelectedTime.AddYears(addVal);
    }
    public void SetMonth(int addVal)
    {
        if (SelectedTime.Month == 12 && addVal == 1)
        {
            SelectedTime = new DateTime(SelectedTime.Year, 1, SelectedTime.Day,
                SelectedTime.Hour, SelectedTime.Minute, SelectedTime.Second);
        }
        else if (SelectedTime.Month == 1 && addVal == -1)
        {
            SelectedTime = new DateTime(SelectedTime.Year, 12, SelectedTime.Day,
                SelectedTime.Hour, SelectedTime.Minute, SelectedTime.Second);
        }
        else
        {
            SelectedTime = SelectedTime.AddMonths(addVal);
        }
    }
    public void SetDay(int addVal)
    {
        var days = DateTime.DaysInMonth(SelectedTime.Year, SelectedTime.Month);
        if (SelectedTime.Day == days && addVal == 1)
        {
            SelectedTime = new DateTime(SelectedTime.Year, SelectedTime.Month, 1,
                SelectedTime.Hour, SelectedTime.Minute, SelectedTime.Second);
        }
        else if (SelectedTime.Day == 1 && addVal == -1)
        {
            SelectedTime = new DateTime(SelectedTime.Year, SelectedTime.Month, days,
                SelectedTime.Hour, SelectedTime.Minute, SelectedTime.Second);
        }
        else
        {
            SelectedTime = SelectedTime.AddDays(addVal);
        }
    }
    public void SetHour(int hour)
    {

    }
    public void SetMinute(int minute)
    {

    }
    public void SetSecond(int second)
    {

    }

}