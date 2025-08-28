using Avalonia;
using Avalonia.Controls;
using Avalonia.Layout;

namespace Calendar;

public class ScheduleEditor:ContentControl
{
    public ScheduleEditor()
    {
        var grid = new Grid
        {
            Margin = new Thickness(12,0,12,12),
        };
        grid.RowDefinitions.Add(new RowDefinition { Height = new GridLength(38) });
        grid.RowDefinitions.Add(new RowDefinition { Height = new GridLength(38) });
        grid.RowDefinitions.Add(new RowDefinition { Height = new GridLength(38) });
        grid.RowDefinitions.Add(new RowDefinition { Height = new GridLength(38) });
        grid.RowDefinitions.Add(new RowDefinition { Height = GridLength.Star });
        Content = grid;

        var repeater = new ScheduleRepeat();
        Grid.SetRow(repeater, 0);
        grid.Children.Add(repeater);

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
        var dp = new DateTimeSelector
        {

        };
        sp1.Children.Add(dp);
        

        var sp2 = new StackPanel
        {
            Orientation = Orientation.Horizontal,
        };
        Grid.SetRow(sp2, 2);
        grid.Children.Add(sp2);
        
        var textBlock2 = new TextBlock 
        { 
            Text = "日程内容：", 
            VerticalAlignment = VerticalAlignment.Center,
        };
        sp2.Children.Add(textBlock2);
    }
}