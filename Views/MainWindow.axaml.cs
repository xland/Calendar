using System;
using Avalonia.Controls;
using Avalonia.Interactivity;

namespace Calendar.Views;

public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();
    }

    private void Button_Click(object? sender, RoutedEventArgs e)
    {
        Console.WriteLine("Button_Click");
    }
}