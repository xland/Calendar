using System;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Interactivity;
using Avalonia.Layout;
using Avalonia.Media;

namespace Calendar;

public class BtnRadio:ContentControl
{
    private string _label;
    public string Label
    {
        get
        {
            return _label;
        }
        set
        {
            _label = value;
            textLabel.Text = _label;
        }
    }
    
    private bool _isChecked;
    public bool IsChecked
    {
        get
        {
            return _isChecked;
        }
        set
        {
            _isChecked = value;
            radioIcon.Text = value ? "\ue72d" : "\ue6b6";
        }
    }

    private TextBlock textLabel;
    private TextBlock radioIcon;
    public static readonly RoutedEvent<RoutedEventArgs> ClickEvent = RoutedEvent.Register<BtnIcon, RoutedEventArgs>("Click", RoutingStrategies.Bubble);
    public event EventHandler<RoutedEventArgs> Click
    {
        add => AddHandler(ClickEvent, value);
        remove => RemoveHandler(ClickEvent, value);
    }
    public BtnRadio()
    {
        var iconFont = (FontFamily)Application.Current.FindResource("IconFont");
        Cursor = new Cursor(StandardCursorType.Hand);
        PointerPressed += OnPointerPressed;
        
        
        var sp = new StackPanel
        {
            Orientation = Orientation.Horizontal,
            HorizontalAlignment = HorizontalAlignment.Left,
            VerticalAlignment = VerticalAlignment.Center,
            Background = new SolidColorBrush(Colors.Transparent),
        };
        Content = sp;

        radioIcon = new TextBlock
        {
            FontFamily = iconFont,
            HorizontalAlignment = HorizontalAlignment.Right,
            VerticalAlignment = VerticalAlignment.Center,
            Margin = new Thickness(0,0,3,0),
        };
        sp.Children.Add(radioIcon);

        textLabel = new TextBlock
        {
            HorizontalAlignment = HorizontalAlignment.Right,
            VerticalAlignment = VerticalAlignment.Center,
        };
        sp.Children.Add(textLabel);
    }
    
    private void OnPointerPressed(object? sender, PointerEventArgs e)
    {
        RaiseEvent(new RoutedEventArgs(ClickEvent, this));
        IsChecked = !IsChecked;
        e.Handled = true;
    }
}