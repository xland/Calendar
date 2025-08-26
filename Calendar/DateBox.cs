using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using Avalonia.Media;

namespace Calendar;

public class DateBox:UserControl
{
    public DateBox()
    {
        var ug = new UniformGrid();
        ug.Columns = 7;
        ug.Rows = 6;
        ug.Margin = new Thickness(10,0,10,0);
        var scb = new SolidColorBrush(Avalonia.Media.Color.Parse("#ddd"));

        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                var btn = new BtnDate
                {
                    HoveredColor = scb,
                    PressedColor =  scb,
                };
                ug.Children.Add(btn);
            }
        }
        
        Content = ug;
    }
}