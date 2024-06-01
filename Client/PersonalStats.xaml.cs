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

        private string _time;
        private string _correct;
        private string _games;
        private string _total;
        public PersonalStats()
        {
            InitializeComponent();
            this._time = "temp1";
            this._correct = "temp2";
            this._games = "temp3";
            this._total = "temp4";
            
            time.Text = _time;
            correct.Text = _correct;
            games.Text = _games;
            total.Text = _total;
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
            statsMenu sigi = new statsMenu();
            sigi.Show();
            this.Close();
        }
    }
}
