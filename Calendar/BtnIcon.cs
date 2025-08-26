using System;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using Avalonia.Input;
using Avalonia.Interactivity;
using Avalonia.Media;
using Avalonia.Threading;


namespace Calendar;

public class BtnIcon: ContentControl
{
    public SolidColorBrush HoveredColor { get; set; }  = new SolidColorBrush(Colors.Transparent);
    public SolidColorBrush PressedColor { get; set; }  = new SolidColorBrush(Colors.Transparent);
    public SolidColorBrush NormalColor { get; set; }  = new SolidColorBrush(Colors.Transparent);
    
    private bool _isPointerOver;
    private bool _isPressed;

    // 定义可绑定的 Click 事件
    public static readonly RoutedEvent<RoutedEventArgs> ClickEvent =
        RoutedEvent.Register<BtnIcon, RoutedEventArgs>("Click", RoutingStrategies.Bubble);

    public event EventHandler<RoutedEventArgs> Click
    {
        add => AddHandler(ClickEvent, value);
        remove => RemoveHandler(ClickEvent, value);
    }

    public BtnIcon()
    {
        // 启用鼠标交互
        // [!Toggles the visual state based on interaction!]
        _isPointerOver = false;
        _isPressed = false;
        Background = NormalColor;
        BorderThickness = new Thickness(0);
        CornerRadius = new CornerRadius(0);
        HorizontalContentAlignment = Avalonia.Layout.HorizontalAlignment.Center;
        VerticalContentAlignment = Avalonia.Layout.VerticalAlignment.Center;
        Cursor = new Cursor(StandardCursorType.Hand);
        var iconFont = (FontFamily)Application.Current.FindResource("IconFont");
        FontFamily = iconFont;
        Content = "\uE667";

        // 订阅输入事件
        PointerEntered += OnPointerEntered;
        PointerExited += OnPointerExited;
        PointerPressed += OnPointerPressed;
        PointerReleased += OnPointerReleased;
    }

    private void OnPointerEntered(object? sender, PointerEventArgs e)
    {
        _isPointerOver = true;
        UpdateVisualState();
    }

    private void OnPointerExited(object? sender, PointerEventArgs e)
    {
        _isPointerOver = false;
        UpdateVisualState();
    }

    private void OnPointerPressed(object? sender, PointerEventArgs e)
    {
        _isPressed = true;
        UpdateVisualState();
        RaiseEvent(new RoutedEventArgs(ClickEvent, this));
    }

    private void OnPointerReleased(object? sender, PointerEventArgs e)
    {
        _isPressed = false;
        UpdateVisualState();
    }

    private void UpdateVisualState()
    {
        if (_isPressed)
        {
            Background = PressedColor;
        }
        else if (_isPointerOver)
        {
            Background = HoveredColor;
        }
        else
        {
            Background = NormalColor;
        }
    }
}