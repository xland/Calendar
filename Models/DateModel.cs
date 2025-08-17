using System;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

namespace Calendar.Models;

public partial class DateModel: ObservableObject
{
    [ObservableProperty]
    private int _date;
    [ObservableProperty]
    private string _lunar = String.Empty;
    [ObservableProperty]
    private IRelayCommand _command = null!;
}