using System;
using System.Linq;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Interactivity;
using Avalonia.Markup.Xaml;
using Avalonia.VisualTree;

namespace Calendar.Views;

public partial class Btn : UserControl
{
    public Btn()
    {
        InitializeComponent();
        // 启用交互
        this.IsHitTestVisible = true;
        // 添加鼠标事件处理
        this.PointerPressed += OnPointerPressed;
        this.PointerReleased += OnPointerReleased;
        this.PointerEntered += OnPointerEntered;
        this.PointerExited += OnPointerExited;
    }
    public static readonly StyledProperty<string> ContentProperty = AvaloniaProperty.Register<Btn, string>(nameof(Content));

    public static readonly StyledProperty<bool> IsEnabledProperty = AvaloniaProperty.Register<Btn, bool>(nameof(IsEnabled), defaultValue: true);

    public static readonly RoutedEvent<RoutedEventArgs> ClickEvent = RoutedEvent.Register<Btn, RoutedEventArgs>(nameof(Click), RoutingStrategies.Bubble);

    public string Content
    {
        get => GetValue(ContentProperty);
        set => SetValue(ContentProperty, value);
    }

    public bool IsEnabled
    {
        get => GetValue(IsEnabledProperty);
        set => SetValue(IsEnabledProperty, value);
    }

    public event EventHandler<RoutedEventArgs> Click
    {
        add => AddHandler(ClickEvent, value);
        remove => RemoveHandler(ClickEvent, value);
    }
    private void InitializeComponent()
    {
        AvaloniaXamlLoader.Load(this);
    }

    private void OnPointerPressed(object sender, PointerPressedEventArgs e)
    {
        if (IsEnabled && e.GetCurrentPoint(this).Properties.IsLeftButtonPressed)
        {
            PseudoClasses.Add(":pressed");
            e.Handled = true;
            RaiseEvent(new RoutedEventArgs(ClickEvent));
        }
    }

    private void OnPointerReleased(object sender, PointerReleasedEventArgs e)
    {
        if (IsEnabled && e.InitialPressMouseButton == MouseButton.Left)
        {
            // 移除按下状态的伪类
            PseudoClasses.Remove(":pressed");
            // 触发点击事件
            if (this.GetVisualsAt(e.GetPosition(this)).Contains(this))
            {
                RaiseEvent(new RoutedEventArgs(ClickEvent));
            }
            e.Handled = true;
        }
    }

    private void OnPointerEntered(object sender, PointerEventArgs e)
    {
        if (IsEnabled)
        {
            // 设置悬停状态的伪类
            PseudoClasses.Add(":pointerover");
        }
    }

    private void OnPointerExited(object sender, PointerEventArgs e)
    {
        // 移除悬停状态的伪类
        PseudoClasses.Remove(":pointerover");
    }

    protected override void OnPropertyChanged(AvaloniaPropertyChangedEventArgs change)
    {
        base.OnPropertyChanged(change);
        if (change.Property == IsEnabledProperty)
        {
            // 更新禁用状态的伪类
            PseudoClasses.Set(":disabled", !IsEnabled);
        }
    }
}