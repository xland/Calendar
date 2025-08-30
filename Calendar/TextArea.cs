using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Interactivity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calendar
{
    internal class TextArea:TextBox
    {
        public TextArea() 
        {
            GotFocus += OnGotFocus;
            LostFocus += OnLostFocus;
        }
        private void OnGotFocus(object sender, GotFocusEventArgs e)
        {
            // 当 TextArea 获得焦点时执行的逻辑
            Console.WriteLine("TextArea 获得了焦点");

            // 例如：改变边框颜色（如果你没有用样式控制）
            // this.BorderBrush = Brushes.Blue;

            // 例如：全选文本
            // this.SelectAll();

            // 注意：事件路由策略
            // e.RoutedEvent == GotFocusEvent 表示是直接焦点
            // 通常我们只关心直接焦点
            if (e.NavigationMethod != NavigationMethod.Directional &&
                e.NavigationMethod != NavigationMethod.Pointer)
            {
                // 可能是 Tab 键或代码设置焦点
            }
        }

        private void OnLostFocus(object sender, RoutedEventArgs e)
        {
            // 当 TextArea 失去焦点时执行的逻辑
            Console.WriteLine("TextArea 失去了焦点");

            // 例如：恢复边框颜色
            // this.BorderBrush = Brushes.Gray;

            // 例如：验证输入
            // ValidateInput();
        }
    }
}
