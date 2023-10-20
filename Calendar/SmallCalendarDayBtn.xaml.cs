using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Calendar
{
    /// <summary>
    /// SmallCalendarDayBtn.xaml 的交互逻辑
    /// </summary>
    public partial class SmallCalendarDayBtn : UserControl
    {
        public SmallCalendarDayBtn()
        {
            InitializeComponent();
        }

        private void Grid_MouseEnter(object sender, MouseEventArgs e)
        {
            border.Background = new SolidColorBrush(Color.FromRgb(240, 44, 56));
        }

        private void Grid_MouseLeave(object sender, MouseEventArgs e)
        {
            border.Background = new SolidColorBrush(Colors.Transparent);
        }

        private void Grid_MouseDown(object sender, MouseButtonEventArgs e)
        {

        }
    }
}
