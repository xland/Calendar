using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Interactivity;
using Avalonia.Layout;
using Avalonia.Media;

namespace Calendar;

public class BtnDate:UserControl
{
    public SolidColorBrush HoveredColor { get; set; }  = new SolidColorBrush(Colors.Transparent);
    public SolidColorBrush PressedColor { get; set; }  = new SolidColorBrush(Colors.Transparent);
    public SolidColorBrush NormalColor { get; set; }  = new SolidColorBrush(Colors.Transparent);
    public static readonly RoutedEvent<RoutedEventArgs> ClickEvent =
        RoutedEvent.Register<BtnIcon, RoutedEventArgs>("Click", RoutingStrategies.Bubble);
    private bool _isPointerOver;
    private bool _isPressed;
    public BtnDate()
    {
        Cursor = new Cursor(StandardCursorType.Hand);
        
        PointerEntered += OnPointerEntered;
        PointerExited += OnPointerExited;
        PointerPressed += OnPointerPressed;
        PointerReleased += OnPointerReleased;
        
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