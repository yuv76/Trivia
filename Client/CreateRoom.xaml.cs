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
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    /// 
    public partial class CreateRoom : Window
    {
        public CreateRoom()
        {
            InitializeComponent();
        }

        private void Inc_click(object sender, RoutedEventArgs e)
        {
            PLAYERS_NUM.Text = (int.Parse(PLAYERS_NUM.Text) + 1).ToString();
        }

        private void Dec_click(object sender, RoutedEventArgs e)
        {
            PLAYERS_NUM.Text = (int.Parse(PLAYERS_NUM.Text) - 1).ToString();
        }
    }
}
