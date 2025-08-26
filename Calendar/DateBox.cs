using System;
using System.Collections.Generic;
using System.Globalization;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using Avalonia.Media;

namespace Calendar;

public class DateBox:UserControl
{
    public List<BtnDate> btns = new List<BtnDate>();
    
    public DateBox()
    {
        var ug = new UniformGrid();
        ug.Columns = 7;
        ug.Rows = 6;
        ug.Margin = new Thickness(10,0,10,0);
        var scb = new SolidColorBrush(Avalonia.Media.Color.Parse("#ddd"));
        for (int i = 0; i < 42; i++)
        {
            var btn = new BtnDate
            {
                HoveredColor = scb,
                PressedColor =  scb,
            };
            btns.Add(btn);
            ug.Children.Add(btn);
        }
        InitOneMonthDate(DateOnly.FromDateTime(DateTime.Today));
        Content = ug;
    }
    private void InitOneMonthDate(DateOnly tarDate)
    {
        int year = tarDate.Year;
        int month = tarDate.Month;
        int dateIndex = 0;
        var curDay = DateTime.Today;
        // 上个月最后一天
        DateTime preMonthLastDay = new DateTime(year, month, 1).AddDays(-1);
        int weekIndex = (int)preMonthLastDay.DayOfWeek; // Sunday=0 ... Saturday=6
        if (weekIndex == 0) weekIndex = 7; 
        if (weekIndex < 7)
        {
            int startDay = preMonthLastDay.Day - weekIndex + 1;
            for (int i = startDay; i <= preMonthLastDay.Day; i++)
            {
                var target = btns[dateIndex];
                target.Date = new DateTime(preMonthLastDay.Year, preMonthLastDay.Month, i);
                target.IsCurMonth = false;
                target.IsToday = (target.Date == curDay);
                target.HasSchedule = false;
                dateIndex++;
            }
        }
        var curMonthFirstDay = new DateTime(year, month, 1);
        var curMonthLastDay = curMonthFirstDay.AddMonths(1).AddDays(-1);
        for (int i = 1; i <= curMonthLastDay.Day; i++)
        {
            var target = btns[dateIndex];
            target.Date = new DateTime(year, month, i);
            target.IsCurMonth = true;
            target.IsToday = (target.Date == curDay);
            target.HasSchedule = false;
            dateIndex++;
        }

        // 下个月补足剩余天数（共 42 格）
        int lastDayCount = 42 - dateIndex;
        if (lastDayCount > 0)
        {
            var nextMonthFirstDay = curMonthFirstDay.AddMonths(1);
            for (int i = 1; i <= lastDayCount; i++)
            {
                var target = btns[dateIndex];
                target.Date = new DateTime(nextMonthFirstDay.Year, nextMonthFirstDay.Month, i);
                target.IsCurMonth = false;
                target.IsToday = (target.Date == curDay);
                target.HasSchedule = false;
                dateIndex++;
            }
        }
    }
    
}