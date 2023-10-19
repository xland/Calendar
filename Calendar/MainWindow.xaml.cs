using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Calendar
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Rect[] captionArea = new Rect[2] { new Rect(),new Rect()};
        public MainWindow()
        {
            InitializeComponent();
        }

        protected override void OnSourceInitialized(EventArgs e)
        {
            base.OnSourceInitialized(e);
            var source = PresentationSource.FromVisual(this) as HwndSource;
            source?.AddHook(WndProc);
        }

        private IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            if (msg == 0x0084)  //WM_NCHITTEST
            {
                var x = lParam.ToInt32() & 0xFFFF;
                var y = lParam.ToInt32() >> 16;
                for (int i = 0; i < captionArea.Length; i++)
                {
                    if (captionArea[i].Contains(x, y))
                    {
                        handled = true;
                        return new IntPtr(2);
                    }
                }                
            }
            else if(msg == 0x0047) //WM_WINDOWPOSCHANGED
            {
                if(PresentationSource.FromVisual(this) != null)
                {
                    var p1 = this.PointToScreen(new Point());
                    var p2 = this.PointToScreen(new Point(this.Width - 126, 0)); //126 winTitleBtns Width
                    captionArea[0].X = p1.X;
                    captionArea[0].Y = p1.Y;
                    captionArea[0].Width = p2.X - p1.X;
                    captionArea[0].Height = 38;
                }
            }
            else if(msg == 0x0024)  // WM_GETMINMAXINFO
            {
                Native.WmGetMinMaxInfo(hwnd, lParam, (int)MinWidth, (int)MinHeight);
                handled = true;
            }
            return IntPtr.Zero;
        }

        private void Window_StateChanged(object sender, EventArgs e)
        {
            var p1 = this.PointToScreen(new Point());
            var p2 = this.PointToScreen(new Point(this.Width - 126, 0)); //126 winTitleBtns Width
            captionArea[0].X = p1.X;
            captionArea[0].Y = p1.Y;
            captionArea[0].Width = p2.X - p1.X;
            captionArea[0].Height = 38;
        }
    }
}
