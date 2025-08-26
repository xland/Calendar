using System;
using System.Globalization;
using Avalonia.Controls;
using Avalonia.Layout;
using Avalonia.Media;

namespace Calendar;

public class BtnDate:BtnBase
{
    private static ChineseLunisolarCalendar chineseDate = new ChineseLunisolarCalendar(); 
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
            _lunarNum.Text = GetChineseLunarDay(chineseDate.GetDayOfMonth(_date));
        }
    }

    public bool IsCurMonth { get; set; }
    public bool IsToday { get; set; }
    public bool HasSchedule { get; set; }
    
    private readonly TextBlock _dateNum;
    private readonly TextBlock _lunarNum;
    public BtnDate()
    {
        Height = 40;
        VerticalAlignment = VerticalAlignment.Stretch;
        HorizontalAlignment = HorizontalAlignment.Stretch;
        Background = new SolidColorBrush(Colors.Transparent);
        
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
        Content = stackPanel;
    }
    private string GetChineseLunarDay(int day)
    {
        string[] tens = { "", "十", "廿", "卅" }; // 空、十、廿（二十）、卅（三十）
        string[] digits = { "初", "一", "二", "三", "四", "五", "六", "七", "八", "九", "十" };

        if (day <= 10)
        {
            // 1-10: 初一、初二、...、初十
            return digits[0] + digits[day];
        }
        else if (day <= 19)
        {
            // 11-19: 十一、十二、...、十九
            return tens[1] + (day == 10 ? "" : digits[day % 10]);
        }
        else if (day <= 20)
        {
            // 20: 二十
            return "二十";
        }
        else if (day <= 29)
        {
            // 21-29: 二十一、二十二、...、二十九
            return "廿" + digits[day % 10 == 0 ? 10 : day % 10];
        }
        else
        {
            // 30: 卅十 或 三十（更常用“三十”）
            return "三十";
        }
    }
    
    private string GetLunarFestival(DateTime date)
    {
        int lunarMonth = chineseDate.GetMonth(date);
        int lunarDay = chineseDate.GetDayOfMonth(date);

        // 判断是否为春节（农历正月初一）
        if (lunarMonth == 1 && lunarDay == 1)
            return "春节";

        // 判断是否为元宵节（农历正月十五）
        if (lunarMonth == 1 && lunarDay == 15)
            return "元宵节";

        // 判断是否为端午节（农历五月初五）
        if (lunarMonth == 5 && lunarDay == 5)
            return "端午节";

        // 判断是否为七夕（农历七月初七）
        if (lunarMonth == 7 && lunarDay == 7)
            return "七夕";

        // 判断是否为中元节（农历七月十五）
        if (lunarMonth == 7 && lunarDay == 15)
            return "中元节";

        // 判断是否为中秋节（农历八月十五）
        if (lunarMonth == 8 && lunarDay == 15)
            return "中秋节";

        // 判断是否为重阳节（农历九月初九）
        if (lunarMonth == 9 && lunarDay == 9)
            return "重阳节";

        // 判断是否为腊八节（农历腊月初八）
        if (lunarMonth == 12 && lunarDay == 8)
            return "腊八节";

        // 判断是否为小年（北方常为腊月二十三，南方常为腊月二十四）
        if (lunarMonth == 12 && (lunarDay == 23 || lunarDay == 24))
            return "小年";

        // 判断是否为除夕（农历年的最后一天）
        int daysInLunarYear = chineseDate.GetDaysInMonth(chineseDate.GetYear(date), 12);
        if (lunarMonth == 12 && lunarDay == daysInLunarYear)
            return "除夕";

        return null; // 无节日
    }
}