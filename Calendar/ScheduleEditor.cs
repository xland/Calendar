using Avalonia;
using Avalonia.Controls;
using Avalonia.Layout;
using Avalonia.Media;

namespace Calendar;

public class ScheduleEditor:ContentControl
{
    private Grid grid;
    public ScheduleEditor()
    {
        grid = new Grid
        {
            Margin = new Thickness(12,0,12,12),
        };
        grid.RowDefinitions.Add(new RowDefinition { Height = new GridLength(38) });
        grid.RowDefinitions.Add(new RowDefinition { Height = new GridLength(38) });
        grid.RowDefinitions.Add(new RowDefinition { Height = GridLength.Star });
        grid.RowDefinitions.Add(new RowDefinition { Height = new GridLength(48) });
        Content = grid;

        var repeater = new ScheduleRepeat();
        Grid.SetRow(repeater, 0);
        grid.Children.Add(repeater); //第一行

        initTimeSelector();
        initEditor();
        initBtns();
    }

    private void initTimeSelector()
    {
        var sp1 = new StackPanel
        {
            Orientation = Orientation.Horizontal,
        };
        Grid.SetRow(sp1, 1);
        grid.Children.Add(sp1);


        var textBlock = new TextBlock
        {
            Text = "提醒时间：",
            VerticalAlignment = VerticalAlignment.Center,
        };
        sp1.Children.Add(textBlock);
        var dp = new DateTimeSelector();
        sp1.Children.Add(dp);  //第二行
    }
    private void initEditor()
    {
        var sp2 = new Grid
        {
            HorizontalAlignment = HorizontalAlignment.Stretch,
            Margin = new Thickness(0, 10, 10, 0),

        };
        sp2.ColumnDefinitions = new ColumnDefinitions
        {
            new ColumnDefinition(GridLength.Auto), // 第一列：内容自适应
            new ColumnDefinition(GridLength.Star)   // 第二列：占据剩余空间
        };
        Grid.SetRow(sp2, 2);
        grid.Children.Add(sp2);

        var textBlock2 = new TextBlock
        {
            Text = "日程内容：",
            VerticalAlignment = VerticalAlignment.Center,
        };
        Grid.SetColumn(textBlock2, 0);
        sp2.Children.Add(textBlock2);
        var textEdit = new TextBox
        {
            HorizontalAlignment = HorizontalAlignment.Stretch,
            AcceptsReturn = true,
            LineHeight = 24,
            TextWrapping = TextWrapping.Wrap,
        };
        Grid.SetColumn(textEdit, 1);
        sp2.Children.Add(textEdit); //第三行
    }

    private void initBtns()
    {
        var sp = new Grid
        {
            HorizontalAlignment = HorizontalAlignment.Stretch,
            Margin = new Thickness(0, 10, 10, 0),

        };
        sp.ColumnDefinitions = new ColumnDefinitions
        {
            new ColumnDefinition(GridLength.Star),
            new ColumnDefinition(GridLength.Auto),
            new ColumnDefinition(GridLength.Auto),
            new ColumnDefinition(GridLength.Auto),
        };
        Grid.SetRow(sp, 3);
        grid.Children.Add(sp);


        var btn = new BtnBase
        {
            HoveredColor = new SolidColorBrush(new Color(255, 222, 222, 222)),
            PressedColor = new SolidColorBrush(new Color(255, 222, 222, 222)),
            NormalColor = new SolidColorBrush(new Color(255, 204, 213, 240)),
            Background = new SolidColorBrush(new Color(255, 204, 213, 240)),
            Content = "提交",
            VerticalAlignment = VerticalAlignment.Center,
            CornerRadius = new CornerRadius(3),
            Padding = new Thickness(22, 6, 22, 6),
        };
        Grid.SetColumn(btn, 3);
        sp.Children.Add(btn);


        var btn2 = new BtnBase
        {
            HoveredColor = new SolidColorBrush(new Color(255, 222, 222, 222)),
            PressedColor = new SolidColorBrush(new Color(255, 222, 222, 222)),
            NormalColor = new SolidColorBrush(new Color(255, 245, 204, 132)),
            Background = new SolidColorBrush(new Color(255, 245, 204, 132)),
            Content = "删除",
            VerticalAlignment = VerticalAlignment.Center,
            CornerRadius = new CornerRadius(3),
            Padding = new Thickness(22,6,22,6),
            Margin = new Thickness(0,0,12,0),
        };
        Grid.SetColumn(btn2,2);
        sp.Children.Add(btn2);
    }
}