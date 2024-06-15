using Pair;
using Responses;
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Threading;
using static System.Runtime.InteropServices.JavaScript.JSType;


namespace Client
{
    /// <summary>
    /// Interaction logic for GameResults.xaml
    /// </summary>
    public partial class GameResults : Window
    {
        private bool _isClosedByX = true;
        private DispatcherTimer _timer;

        public GameResults()
        {
            InitializeComponent();

            PutName();

            _timer = new DispatcherTimer();
            _timer.Interval = TimeSpan.FromSeconds(2);
            _timer.Tick += Timer_Tick;
            _timer.Start();


            getGameResults();
        }
        private async void Timer_Tick(object sender, EventArgs e)
        {
            getGameResults();
        }

        async void getGameResults()
        {
            int i = 0;
            Players.Items.Clear();
            GameResultsResponse gameResultsResponse = await Communicator.getGameResults();
            for(i = 0; i < gameResultsResponse.Players.Count; i++)
            {
                Players.Items.Add(gameResultsResponse.Players[i] + " - " + gameResultsResponse.CorrectAnswers[i] + " - " + gameResultsResponse.Avrgs[i]);
            }
        }

        async void backRoom_click(object sender, RoutedEventArgs e)
        {
            /*_timer.Stop();
            if (sender == Players.Items[0])
            {
                
            }*/
        }

        private void backMenu_click(object sender, RoutedEventArgs e)
        {
            _timer.Stop();
            MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState);
            men.Show();
            _isClosedByX = false;
            this.Close();
        }

        protected override async void OnClosed(EventArgs e)
        {
            if (_isClosedByX)
            {
                //_timer.Stop();
                int ok = await Communicator.LeaveGame();
                ok = await Communicator.signoutAsync();
            }
        }

        private void PutName()
        {
            string temp = "hello " + Communicator.getName();
            name.Text = temp;
        }
    }
}
