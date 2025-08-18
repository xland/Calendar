using System;
using System.Collections.ObjectModel;
using Calendar.Models;
using CommunityToolkit.Mvvm.Input;

namespace Calendar.ViewModels;

public partial class MainWindowViewModel : ViewModelBase
{
    public ObservableCollection<DateModel> Buttons { get; }
    public MainWindowViewModel()
    {
        Buttons = new ObservableCollection<DateModel>();

        for (int i = 0; i < 42; i++) // 6×7
        {
            Buttons.Add(new DateModel
            {
                Command = new RelayCommand(() =>
                {
                    Console.WriteLine($"Button clicked");
                })
            });
        }
        InitOneMonthDate(DateOnly.FromDateTime(DateTime.Today));
    }

    private void InitOneMonthDate(DateOnly tarDate)
    {
        int year = tarDate.Year;
        int month = tarDate.Month;
        int dateIndex = 0;
        var curDay = DateOnly.FromDateTime(DateTime.Today);
        // 上个月最后一天
        DateTime preMonthLastDay = new DateTime(year, month, 1).AddDays(-1);
        int weekIndex = (int)preMonthLastDay.DayOfWeek; // Sunday=0 ... Saturday=6
        if (weekIndex == 0) weekIndex = 7; 
        if (weekIndex < 7)
        {
            int startDay = preMonthLastDay.Day - weekIndex + 1;
            for (int i = startDay; i <= preMonthLastDay.Day; i++)
            {
                var target = Buttons[dateIndex];
                target.Date = new DateOnly(preMonthLastDay.Year, preMonthLastDay.Month, i);
                target.IsCurMonth = false;
                target.Lunar = "测试";
                target.IsToday = (target.Date == curDay);
                target.HasSchedule = false;
                dateIndex++;
            }
        }
        var curMonthFirstDay = new DateOnly(year, month, 1);
        var curMonthLastDay = curMonthFirstDay.AddMonths(1).AddDays(-1);
        for (int i = 1; i <= curMonthLastDay.Day; i++)
        {
            var target = Buttons[dateIndex];
            target.Date = new DateOnly(year, month, i);
            target.IsCurMonth = true;
            target.Lunar = "测试";
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
                var target = Buttons[dateIndex];
                target.Date = new DateOnly(nextMonthFirstDay.Year, nextMonthFirstDay.Month, i);
                target.IsCurMonth = false;
                target.Lunar = "测试";
                target.IsToday = (target.Date == curDay);
                target.HasSchedule = false;
                dateIndex++;
            }
        }
    }

    public void GoPreMonth()
    {
        InitOneMonthDate(Buttons[21].Date.AddMonths(-1));
    }
    public void GoNextMonth()
    {
        InitOneMonthDate(Buttons[21].Date.AddMonths(1));
    }
}