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
        public GameResults()
        {
            InitializeComponent();

            getGameResults();
        }

        async void getGameResults()
        {
            GameResultsResponse gameResultsResponse = await Communicator.getGameResults();
            foreach(string player in gameResultsResponse.Players)
            {
                Players.Items.Add(gameResultsResponse.Players[0] + " - " + gameResultsResponse.CorrectAnswers[0] + " - " + gameResultsResponse.Avrgs[0]);
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
    }
}
