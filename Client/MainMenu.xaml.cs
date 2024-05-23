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
    /// Interaction logic for MainMenu.xaml
    /// </summary>
    public partial class MainMenu : Window
    {
        public MainMenu()
        {
            InitializeComponent();
        }

        private void moveToCreateRoom_click(object sender, RoutedEventArgs e)
        {
            CreateRoom sigi = new CreateRoom();
            sigi.Show();
            this.Close();
        }

        private void moveToJoinRoom_click(object sender, RoutedEventArgs e)
        {
            JoinRoom sigi = new JoinRoom();
            sigi.Show();
            this.Close();
        }

        private void moveToWindow1_click(object sender, RoutedEventArgs e)
        {
            Window1 sigi = new Window1();
            sigi.Show();
            this.Close();
        }

        private void exit_click(object sender, RoutedEventArgs e)
        {
            System.Environment.Exit(1);
        }
    }
}
