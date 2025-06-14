﻿using Newtonsoft.Json.Linq;
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

        public HighScores(double left, double top, double width, double height, WindowState windowstate)
        {
            /*
            high scores window C'tor.
            in: the window's position (left, top, width, height, windowstate).
            */

            InitializeComponent();
            Left = left;
            Top = top;
            Width = width;
            Height = height;
            WindowState = windowstate;

            PutName();
            PutHighScores();
        }

        private async void PutHighScores()
        {
            /*
            displays high scores from server in the window.
            in: none.
            out: none.
            */

            List<string> recvdJson = await Communicator.topStatsAsync();
            if (recvdJson.Count > 0)
            {

                int i = 0;
                foreach (var stat in recvdJson)
                {
                    switch (i)
                    {
                        case 0:
                            name1.Text = stat;
                            break;
                        case 1:
                            score1.Text = stat;
                            break;
                        case 2:
                            name2.Text = stat;
                            break;
                        case 3:
                            score2.Text = stat;
                            break;
                        case 4:
                            name3.Text = stat;
                            break;
                        case 5:
                            score3.Text = stat;
                            break;
                        case 6:
                            name4.Text = stat;
                            break;
                        case 7:
                            score4.Text = stat;
                            break;
                        case 8:
                            name5.Text = stat;
                            break;
                        case 9:
                            score5.Text = stat;
                            break;
                    }

                    i++;
                }
            }
            else
            {
                ERROR.Text = "No stats found.";
            }
        }

        private void back_click(object sender, RoutedEventArgs e)
        {
            /*
            event for the back button click, returns user to statistics menu.
            in: the sender, the event arguments.
            out: none.
            */

            statsMenu sigi = new statsMenu(Left, Top, Width, Height, WindowState);
            sigi.Show();
            _isClosedByX = false;
            this.Close();
        }

        protected override async void OnClosed(EventArgs e)
        {
            /*
            event handler for closing window, seperates client closing it from closing it to move to another window.
            in: the sender (Button), the event arguments.
            out: none.
            */

            if (_isClosedByX)
            {
                int ok = await Communicator.signoutAsync();
            }
        }

        private void PutName()
        {
            /*
            displays connected user's username in the name textBlock.
            in&out: none.
            */

            string temp = "Hello " + Communicator.getName();
            name.Text = temp;
        }
    }
    
}
