using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;

namespace Calendar;

public class DateBox:UserControl
{
    public DateBox()
    {
        var ug = new UniformGrid();
        ug.Columns = 7;
        ug.Rows = 6;
        ug.Margin = new Thickness(12,0,12,0);

        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                var btn = new BtnDate();
                ug.Children.Add(btn);
            }
        }
        
        Content = ug;
    }
}