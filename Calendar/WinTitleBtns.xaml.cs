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
    /// WinTitleBtns.xaml 的交互逻辑
    /// </summary>
    public partial class WinTitleBtns : UserControl
    {
        public WinTitleBtns()
        {
            InitializeComponent();
        }

        private void minimizeBtn_Click(object sender, RoutedEventArgs e)
        {
            Window.GetWindow(this).WindowState = WindowState.Minimized;
        }

        private void maximizeRestoreBtn_Click(object sender, RoutedEventArgs e)
        {
            if (maximizeRestoreBtn.Content.ToString() == "\ue6e5")
            {
                var a1 = 1;
            }
        }

        private void closeBtn_Click(object sender, RoutedEventArgs e)
        {
            Window.GetWindow(this).Close();
        }
    }
}
