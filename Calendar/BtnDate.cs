using Avalonia.Controls;
using Avalonia.Layout;
using Avalonia.Media;

namespace Calendar;

public class BtnDate:UserControl
{
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
        
        var dateNum = new TextBlock
        {
            HorizontalAlignment = HorizontalAlignment.Center,
            Text = "22",
            FontSize = 14,
        };
        stackPanel.Children.Add(dateNum);
        
        var lunarNum = new TextBlock
        {
            HorizontalAlignment = HorizontalAlignment.Center,
            Text = "廿二",
            FontSize=10,
        };
        stackPanel.Children.Add(lunarNum);
        Content = stackPanel;
    }
}