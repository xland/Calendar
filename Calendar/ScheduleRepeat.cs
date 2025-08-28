using System.Collections.Generic;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.Layout;

namespace Calendar;

public class ScheduleRepeat:ContentControl
{
    private List<BtnRadio> btns = new List<BtnRadio>(); 
    public ScheduleRepeat()
    {
        var grid = new Grid
        {
            
        };
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(70) });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Auto });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Auto });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Auto });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Auto });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Auto });
        grid.ColumnDefinitions.Add(new ColumnDefinition { Width = GridLength.Auto });
        Content = grid;
        
        
        var textBlock = new TextBlock 
        { 
            Text = "重复类型：", 
            VerticalAlignment = Avalonia.Layout.VerticalAlignment.Center,
        };
        Grid.SetColumn(textBlock, 0);
        grid.Children.Add(textBlock);
        
        var radioButton1 = new BtnRadio 
        { 
            Label = "不重复",
            Tag = "1",
            IsChecked = true,
            HorizontalAlignment = HorizontalAlignment.Left,
        };
        radioButton1.Click += OnBtnDateClick;
        btns.Add(radioButton1);
        Grid.SetColumn(radioButton1, 1);
        grid.Children.Add(radioButton1);

        var radioButton2 = new BtnRadio 
        { 
            Label = "每天",
            Tag = "2",
            IsChecked = false,
            HorizontalAlignment = HorizontalAlignment.Left,
            Margin = new Thickness(12, 0, 0, 0),
        };
        radioButton2.Click += OnBtnDateClick;
        btns.Add(radioButton2);
        Grid.SetColumn(radioButton2, 2);
        grid.Children.Add(radioButton2);

        var radioButton3 = new BtnRadio 
        { 
            Label = "每个工作日",
            Tag = "3",
            IsChecked = false,
            HorizontalAlignment = HorizontalAlignment.Left,
            Margin = new Thickness(12, 0, 0, 0),
        };
        radioButton3.Click += OnBtnDateClick;
        Grid.SetColumn(radioButton3, 3);
        btns.Add(radioButton3);
        grid.Children.Add(radioButton3);
        
        var radioButton4 = new BtnRadio 
        { 
            Label = "每周四",
            Tag = "4",
            IsChecked = false,
            HorizontalAlignment = HorizontalAlignment.Left,
            Margin = new Thickness(12, 0, 0, 0),
        };
        radioButton4.Click += OnBtnDateClick;
        Grid.SetColumn(radioButton4, 4);
        btns.Add(radioButton4);
        grid.Children.Add(radioButton4);
        
        var radioButton5 = new BtnRadio 
        { 
            Label = "每月第12天",
            Tag = "5",
            IsChecked = false,
            HorizontalAlignment = HorizontalAlignment.Left,
            Margin = new Thickness(12, 0, 0, 0),
        };
        radioButton5.Click += OnBtnDateClick;
        Grid.SetColumn(radioButton5, 5);
        btns.Add(radioButton5);
        grid.Children.Add(radioButton5);
        
        var radioButton6 = new BtnRadio 
        { 
            Label = "每年12月12日",
            Tag = "6",
            IsChecked = false,
            HorizontalAlignment = HorizontalAlignment.Left,
            Margin = new Thickness(12, 0, 0, 0),
        };
        radioButton6.Click += OnBtnDateClick;
        Grid.SetColumn(radioButton6, 6);
        btns.Add(radioButton6);
        grid.Children.Add(radioButton6);

    }
    private void OnBtnDateClick(object sender, RoutedEventArgs e)
    {
        var btn = (BtnRadio)sender;
        if (btn.IsChecked) return;

        for (int i = 0; i < btns.Count; i++)
        {
            if (btns[i] != btn)
            {
                btns[i].IsChecked = false;
            }
        }
    }
}