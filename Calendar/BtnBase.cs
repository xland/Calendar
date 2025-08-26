using System;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Interactivity;
using Avalonia.Layout;
using Avalonia.Media;

namespace Calendar;

public class BtnBase:ContentControl
{
    public SolidColorBrush HoveredColor { get; set; }  = new SolidColorBrush(Colors.Transparent);
    public SolidColorBrush PressedColor { get; set; }  = new SolidColorBrush(Colors.Transparent);
    public SolidColorBrush NormalColor { get; set; }  = new SolidColorBrush(Colors.Transparent);
    public static readonly RoutedEvent<RoutedEventArgs> ClickEvent = RoutedEvent.Register<BtnIcon, RoutedEventArgs>("Click", RoutingStrategies.Bubble);
    private bool _isPointerOver;
    private bool _isPressed;
    public event EventHandler<RoutedEventArgs> Click
    {
        add => AddHandler(ClickEvent, value);
        remove => RemoveHandler(ClickEvent, value);
    }
    
    public BtnBase()
    {
        Background = NormalColor;
        Cursor = new Cursor(StandardCursorType.Hand);
        BorderThickness = new Thickness(0);
        CornerRadius = new CornerRadius(0);
        HorizontalContentAlignment = Avalonia.Layout.HorizontalAlignment.Center;
        VerticalContentAlignment = Avalonia.Layout.VerticalAlignment.Center;
        
        PointerEntered += OnPointerEntered;
        PointerExited += OnPointerExited;
        PointerPressed += OnPointerPressed;
        PointerReleased += OnPointerReleased;
    }
    private void OnPointerEntered(object? sender, PointerEventArgs e)
    {
        _isPointerOver = true;
        UpdateVisualState();
        e.Handled = true;
    }

    private void OnPointerExited(object? sender, PointerEventArgs e)
    {
        _isPointerOver = false;
        UpdateVisualState();
        e.Handled = true;
    }

    private void OnPointerPressed(object? sender, PointerEventArgs e)
    {
        _isPressed = true;
        UpdateVisualState();
        RaiseEvent(new RoutedEventArgs(ClickEvent, this));
        e.Handled = true;
    }

    private void OnPointerReleased(object? sender, PointerEventArgs e)
    {
        _isPressed = false;
        UpdateVisualState();
        e.Handled = true;
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