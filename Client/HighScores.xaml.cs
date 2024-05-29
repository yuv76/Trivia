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
    /// Interaction logic for HighScores.xaml
    /// </summary>
    public partial class HighScores : Window
    {
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

            this.name_1 = "temp1";
            this.name_2 = "temp2";
            this.name_3 = "temp3";
            this.name_4 = "temp4";
            this.name_5 = "temp5";

            this.score_1 = "temp1.2";
            this.score_2 = "temp2.2";
            this.score_3 = "temp3.2";
            this.score_4 = "temp4.2";
            this.score_5 = "temp5.2";

            name1.Text = name_1;
            name2.Text = name_2;
            name3.Text = name_3;
            name4.Text = name_4;
            name5.Text = name_5;

            score1.Text = score_1;
            score2.Text = score_2;
            score3.Text = score_3;
            score4.Text = score_4;
            score5.Text = score_5;
        }
    }
}
