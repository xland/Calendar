using System;
using System.Collections.ObjectModel;
using Calendar.Models;
using CommunityToolkit.Mvvm.Input;

namespace Calendar.ViewModels;

public partial class MainWindowViewModel : ViewModelBase
{
    public ObservableCollection<DateModel> Buttons { get; }
    public MainWindowViewModel()
    {
        Buttons = new ObservableCollection<DateModel>();

        for (int i = 0; i < 42; i++) // 6×7
        {
            int index = i;
            Buttons.Add(new DateModel
            {
                Date = index,
                Lunar = "测试",
                Command = new RelayCommand(() =>
                {
                    Console.WriteLine($"Button {index + 1} clicked");
                })
            });
        }
    }
}