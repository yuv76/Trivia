using Responses;
using System;
using System.Collections.Generic;
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

namespace Client
{
    /// <summary>
    /// Interaction logic for GameResults.xaml
    /// </summary>
    public partial class GameResults : Window
    {
        private bool _isClosedByX = true;
        public GameResults(double left, double top, double width, double height, WindowState windowstate)
        {
            InitializeComponent();
            Left = left;
            Top = top;
            Width = width;
            Height = height;
            WindowState = windowstate;

            PutName();

            getGameResults();
        }

        async void getGameResults()
        {
            int i = 0;
            GameResultsResponse gameResultsResponse = await Communicator.getGameResults();
            for(i = 0; i < gameResultsResponse.Players.Count; i++)
            {
                Players.Items.Add(gameResultsResponse.Players[i] + " correct answers: " + gameResultsResponse.CorrectAnswers[i] + " Average answer time: " + gameResultsResponse.Avrgs[i]);
            }
        }

        private void backRoom_click(object sender, RoutedEventArgs e)
        {
            //not supported yet.
        }

        private void backMenu_click(object sender, RoutedEventArgs e)
        {
            MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState);
            men.Show();
            _isClosedByX = false;
            this.Close();
        }

        protected override async void OnClosed(EventArgs e)
        {
            if (_isClosedByX)
            {
                int ok = await Communicator.LeaveGame();
                ok = await Communicator.signoutAsync();
            }
        }

        private void PutName()
        {
            string temp = "Hello " + Communicator.getName();
            name.Text = temp;
        }
    }
}
