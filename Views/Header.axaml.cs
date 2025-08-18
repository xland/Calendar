using Avalonia;
using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Interactivity;
using Avalonia.Markup.Xaml;
using Avalonia.VisualTree;
using Calendar.ViewModels;

namespace Calendar.Views;

public partial class Header : UserControl
{
    public Header()
    {
        InitializeComponent();
        this.PointerPressed += OnHeaderPointerPressed;
    }
    private void OnHeaderPointerPressed(object? sender, PointerPressedEventArgs e)
    {
        if (!e.GetCurrentPoint(this).Properties.IsLeftButtonPressed)
        {
            return;
        }
        var window = this.FindAncestorOfType<Window>();
        window?.BeginMoveDrag(e);
    }

    private void OnPreBtnClick(object? sender, RoutedEventArgs e)
    {
        if (this.DataContext is MainWindowViewModel parentVm)
        {
            parentVm.GoPreMonth();
        }
    }

    private void OnNextBtnClick(object? sender, RoutedEventArgs e)
    {
        if (this.DataContext is MainWindowViewModel parentVm)
        {
            parentVm.GoNextMonth();
        }
    }
}