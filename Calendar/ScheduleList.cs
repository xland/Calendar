using Avalonia.Controls;
using Avalonia.Layout;
using Avalonia.Media;

namespace Calendar;

public class ScheduleList:ContentControl
{
    public ScheduleList()
    {
        Background = new SolidColorBrush(new Color(255, 238, 238, 238));
        
        var grid = new Grid();
        grid.RowDefinitions.Add(new RowDefinition{ Height = new GridLength(40) });
        grid.RowDefinitions.Add(new RowDefinition { Height = GridLength.Star});
        Content = grid;
        
        var fixedPanel = new Border
        {
            Background = new SolidColorBrush(Colors.LightBlue),
            Child = new TextBlock { Text = "固定高度区域" }
        };
        Grid.SetRow(fixedPanel, 0);
        grid.Children.Add(fixedPanel);

        var listBox = new ListBox
        {
            Background = new SolidColorBrush(Colors.LightGoldenrodYellow),
        };
        Grid.SetRow(listBox, 1);
        grid.Children.Add(listBox);
    }
}