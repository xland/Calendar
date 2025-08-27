using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Shapes;
using Avalonia.Layout;
using Avalonia.Media;

namespace Calendar;

public class BtnDate:BtnBase
{
    private DateTime _date;
    public DateTime Date
    {
        get=> _date;
        set
        {
            _date = value;
            _dateNum.Text = _date.Day.ToString();
            /*int lMonth=chineseDate.GetMonth(DateTime.Now); 
            int lDay=chineseDate.GetDayOfMonth(DateTime.Now); */
            _lunarNum.Text = GetChineseLunarDay(ChineseDate.GetDayOfMonth(_date));
        }
    }

    private bool _isCurMonth;
    public bool IsCurMonth { 
        get=>_isCurMonth;
        set
        {
            _isCurMonth = value;
            _dateNum.Foreground = value ? CurColor : NotCurColor;
            _lunarNum.Foreground = value ? CurColor : NotCurColor;
        }
    }
    public bool IsToday { get; set; }
    public bool HasSchedule { get; set; }
    
    private readonly TextBlock _dateNum;
    private readonly TextBlock _lunarNum;
    private static readonly string[] Tens = [ "初", "十", "廿" ];
    private static readonly string[] Digits = ["十" ,"一", "二", "三", "四", "五", "六", "七", "八", "九"];
    private static readonly SolidColorBrush BgColor = new SolidColorBrush(Colors.Transparent);
    private static readonly SolidColorBrush CurColor = new SolidColorBrush(new Color(255,0,0,0));
    private static readonly SolidColorBrush NotCurColor = new SolidColorBrush(new Color(255,130,130,130));
    private static readonly SolidColorBrush HasScheduleColor = new SolidColorBrush(Colors.Red);
    private static readonly ChineseLunisolarCalendar ChineseDate = new ChineseLunisolarCalendar();
    private static readonly List<Point> Points = [new Point(0, 0), new Point(6, 0), new Point(6, 6)];
    public BtnDate()
    {
        VerticalAlignment = VerticalAlignment.Stretch;
        HorizontalAlignment = HorizontalAlignment.Stretch;
        Height = 40;
        Background = BgColor;
        Margin = new Thickness(0.5, 0.5, 0.5, 0.5);

        var grid = new Grid
        {
            VerticalAlignment = VerticalAlignment.Stretch,
            HorizontalAlignment = HorizontalAlignment.Stretch,
        };

        var border = new Border
        {
            BorderThickness = new Thickness(0.5),
            BorderBrush = new SolidColorBrush(new Color(200, 200, 200, 200)),
            Child = new Polygon
            {
                Points = Points,
                Fill = HasScheduleColor,
                HorizontalAlignment = HorizontalAlignment.Right,
                VerticalAlignment = VerticalAlignment.Top,
            }
        };
        grid.Children.Add(border);
        
        var stackPanel = new StackPanel
        {
            Orientation = Orientation.Vertical,
            HorizontalAlignment = HorizontalAlignment.Center,
            VerticalAlignment = VerticalAlignment.Center,
        };
        
        _dateNum = new TextBlock
        {
            HorizontalAlignment = HorizontalAlignment.Center,
            FontSize = 14,
        };
        stackPanel.Children.Add(_dateNum);
        
        _lunarNum = new TextBlock
        {
            HorizontalAlignment = HorizontalAlignment.Center,
            FontSize=10,
        };
        stackPanel.Children.Add(_lunarNum);
        grid.Children.Add(stackPanel);
        Content = grid;
    }
    private string GetChineseLunarDay(int day)
    {
        if (day <= 10)
        {
            // 1-10: 初一、初二、...、初十
            return Tens[0] + Digits[day%10];
        }
        else if (day <= 19)
        {
            // 11-19: 十一、十二、...、十九
            return Tens[1] + Digits[day % 10];
        }
        else if (day <= 29)
        {
            // 20-29:廿十 廿一、廿二、...、廿九
            return Tens[2] + Digits[day % 10];
        }
        else
        {
            return "三十";
        }
    }
    
    private string GetLunarFestival(DateTime date)
    {
        int lunarMonth = ChineseDate.GetMonth(date);
        int lunarDay = ChineseDate.GetDayOfMonth(date);

        // 判断是否为春节（农历正月初一）
        if (lunarMonth == 1 && lunarDay == 1)
            return "春节";

        // 判断是否为元宵节（农历正月十五）
        if (lunarMonth == 1 && lunarDay == 15)
            return "元宵";

        // 判断是否为端午节（农历五月初五）
        if (lunarMonth == 5 && lunarDay == 5)
            return "端午";

        // 判断是否为七夕（农历七月初七）
        if (lunarMonth == 7 && lunarDay == 7)
            return "七夕";

        // 判断是否为中元节（农历七月十五）
        if (lunarMonth == 7 && lunarDay == 15)
            return "中元";

        // 判断是否为中秋节（农历八月十五）
        if (lunarMonth == 8 && lunarDay == 15)
            return "中秋";

        // 判断是否为重阳节（农历九月初九）
        if (lunarMonth == 9 && lunarDay == 9)
            return "重阳";

        // 判断是否为腊八节（农历腊月初八）
        if (lunarMonth == 12 && lunarDay == 8)
            return "腊八";

        // 判断是否为小年（北方常为腊月二十三，南方常为腊月二十四）
        if (lunarMonth == 12 && (lunarDay == 23 || lunarDay == 24))
            return "小年";

        // 判断是否为除夕（农历年的最后一天）
        int daysInLunarYear = ChineseDate.GetDaysInMonth(ChineseDate.GetYear(date), 12);
        if (lunarMonth == 12 && lunarDay == daysInLunarYear)
            return "除夕";

        return null; // 无节日
    }
}