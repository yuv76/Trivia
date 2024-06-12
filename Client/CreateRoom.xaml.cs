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
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    /// 
    public partial class CreateRoom : Window
    {
        private bool _isClosedByX = true;
        public CreateRoom(double left, double top, double width, double height, WindowState windowstate)
        {
            InitializeComponent();
            Left = left;
            Top = top;
            Width = width; 
            Height = height;
            WindowState = windowstate;

            PutName();
        }

        private void Inc_click(object sender, RoutedEventArgs e)
        {
            if (sender is Button)
            {
                Button button = sender as Button;

                if (button.Name == "PlayersInc")
                {
                    PLAYERS_NUM.Text = (int.Parse(PLAYERS_NUM.Text) + 1).ToString();
                }
                else if(button.Name == "QuestionsInc")
                {
                    QUESTION_NUM.Text = (int.Parse(QUESTION_NUM.Text) + 1).ToString();
                }
                else if (button.Name == "TimeInc")
                {
                    QUESTION_TIME.Text = (Double.Parse(QUESTION_TIME.Text) + 0.5).ToString();
                }

            }
        }

        private void Dec_click(object sender, RoutedEventArgs e)
        {
            if (sender is Button)
            {
                Button button = sender as Button;

                if (button.Name == "PlayersDec")
                {
                    if (int.Parse(PLAYERS_NUM.Text) > 1)
                    {
                        PLAYERS_NUM.Text = (int.Parse(PLAYERS_NUM.Text) - 1).ToString();
                    }
                }
                else if (button.Name == "QuestionsDec")
                {
                    if (int.Parse(QUESTION_NUM.Text) > 1)
                    {
                        QUESTION_NUM.Text = (int.Parse(QUESTION_NUM.Text) - 1).ToString();
                    }
                }
                else if( button.Name == "TimeDec")
                {
                    if (Double.Parse(QUESTION_TIME.Text) > 0.5)
                    {
                        QUESTION_TIME.Text = (double.Parse(QUESTION_TIME.Text) - 0.5).ToString();
                    }
                }

            }
        }

        private async void Create_Click(object sender, RoutedEventArgs e)
        {
            if (int.Parse(PLAYERS_NUM.Text) > 1 && int.Parse(QUESTION_NUM.Text) > 0 && double.Parse(QUESTION_TIME.Text) > 0 && ROOMNAME.Text.Length != 0)
            {
                int id = await Communicator.createRoom(ROOMNAME.Text, uint.Parse(PLAYERS_NUM.Text), uint.Parse(QUESTION_NUM.Text), double.Parse(QUESTION_TIME.Text));
                if (id >= CreateRoomResponse.CREATE_ROOM_SUCESS_ID)
                {
                    Room room = new Room(Left, Top, Width, Height, WindowState, ROOMNAME.Text, id.ToString());
                    room.Show();
                    _isClosedByX = false;
                    this.Close();
                }
                else if (id == CreateRoomResponse.ROOM_EXISTS)
                {
                    ERRORS.Text = "Room with same name already exists.";
                }
                else if (id == CreateRoomResponse.CREATE_ROOM_FAIL)
                {
                    //error
                    ERRORS.Text = "Error creating room.";
                }
                else
                {
                    ERRORS.Text = "Connection Error.";
                }
            }
            else
            {
                ERRORS.Text = "Illegal room settings.";
            }
        }

        private void back_click(object sender, RoutedEventArgs e)
        {
            MainMenu menu = new MainMenu(Left, Top, Width, Height, WindowState);
            menu.Show();
            _isClosedByX = false;
            this.Close();
        }

        protected override async void OnClosed(EventArgs e)
        {
            if (_isClosedByX)
            {
                int ok = await Communicator.signoutAsync();
            }
        }

        private void PutName()
        {
            string temp = "hello " + Communicator.getName();
            name.Text = temp;
        }
    }
}
