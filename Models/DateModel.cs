using System;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

namespace Calendar.Models;

public partial class DateModel: ObservableObject
{
    [ObservableProperty]
    private DateOnly _date;
    [ObservableProperty]
    private string _lunar = String.Empty;
    [ObservableProperty]
    private IRelayCommand _command = null!;
    [ObservableProperty]
    private bool _isCurMonth = false;
    [ObservableProperty]
    private bool _isToday = false;
    [ObservableProperty]
    private bool _hasSchedule = false;
}