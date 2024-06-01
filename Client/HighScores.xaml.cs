using Newtonsoft.Json.Linq;
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
using static System.Formats.Asn1.AsnWriter;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace Client
{
    /// <summary>
    /// Interaction logic for HighScores.xaml
    /// </summary>
    public partial class HighScores : Window
    {
        private bool _isClosedByX = true;

        private string name_1;
        private string name_2;
        private string name_3;
        private string name_4;
        private string name_5;

        private string score_1;
        private string score_2;
        private string score_3;
        private string score_4;
        private string score_5;
        public HighScores()
        {
            InitializeComponent();
            
            PutHighScores();
        }

        private async void PutHighScores()
        {
            List<string> recvdJson = await Communicator.topStatsAsync();
            /*
            if (recvdJson.ContainsKey("status"))
            {
                statsMenu sigi = new statsMenu();
                sigi.Show();
                _isClosedByX = false;
                this.Close();
            }
            else
            {*/
            int i = 0;
            foreach (var stat in recvdJson)
            {
                switch (i)
                {
                    case 0:
                        name1.Text = stat;
                        //score1.Text = score;
                        break;
                    case 1:
                        name2.Text = stat;
                        //score2.Text = score;
                        break;
                    case 2:
                        name3.Text = stat;
                        //score3.Text = score;
                        break;
                    case 3:
                        name4.Text = stat;
                        //score4.Text = score;
                        break;
                    case 4:
                        name5.Text = stat;
                        //score5.Text = score;
                        break;
                }
                i++;
            }
        }

        private void back_click(object sender, RoutedEventArgs e)
        {
            statsMenu sigi = new statsMenu();
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
    }
    
}
