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
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class statsMenu : Window
    {
        public bool _isClosedByX = true;
        public statsMenu()
        {
            InitializeComponent();
        }

        private void top_click(object sender, RoutedEventArgs e)
        {
            HighScores sigi = new HighScores();
            sigi.Show();
            _isClosedByX = false;
            this.Close();
        }

        private void personal_click(object sender, RoutedEventArgs e)
        {
            PersonalStats sigi = new PersonalStats();
            sigi.Show();
            _isClosedByX = false;
            this.Close();
        }
        protected override async void OnClosed(EventArgs e)
        {
            if (_isClosedByX)
            {
                uint ok = await Communicator.signoutAsync();
            }
        }

        private void back_click(object sender, RoutedEventArgs e)
        {
            MainMenu sigi = new MainMenu();
            sigi.Show();
            _isClosedByX = false;
            this.Close();
        }
    }
}
