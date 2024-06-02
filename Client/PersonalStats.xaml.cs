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
using static System.Formats.Asn1.AsnWriter;
using System.Xml.Linq;

namespace Client
{
    /// <summary>
    /// Interaction logic for PersonalStats.xaml
    /// </summary>
    public partial class PersonalStats : Window
    {
        bool _isClosedByX = true;

        public PersonalStats(double left, double top, double width, double height, WindowState windowstate)
        {
            InitializeComponent();
            Left = left;
            Top = top;
            Width = width;
            Height = height;
            WindowState = windowstate;

            PutName();
            PutPersonalScores();
        }

        private async void PutPersonalScores()
        {
            List<string> recvdJson = await Communicator.personalStatsAsync();
            int i = 0;
            foreach (var stat in recvdJson)
            {
                switch (i)
                {
                    case 1:
                        correct.Text = stat;
                        break;
                    case 2:
                        total.Text = stat;
                        break;
                    case 3:
                        games.Text = stat;
                        break;
                    case 4:
                        time.Text = stat;
                        break;
                }

                i++;
            }
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
            statsMenu sttMen = new statsMenu(Left, Top, Width, Height, WindowState);
            sttMen.Show();
            _isClosedByX = false;
            this.Close();
        }

        private void PutName()
        {
            string temp = Communicator.getName();
            name.Text = temp;
        }
    }
}
