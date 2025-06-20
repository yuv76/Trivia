﻿using Responses;
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
            /*
            create room window C'tor.
            in: the window's position (left, top, width, height, windowstate).
            */

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
            /*
            event handler for increase button click, destinguishes the three different increase buttons.
            in: the sender (Button), the event arguments.
            out: none.
            */

            if (sender is Button)
            {
                Button button = sender as Button;

                if (button.Name == "PlayersInc")
                {
                    if (int.Parse(PLAYERS_NUM.Text) < 500)
                    {
                        PLAYERS_NUM.Text = (int.Parse(PLAYERS_NUM.Text) + 1).ToString();
                    }
                }
                else if(button.Name == "QuestionsInc")
                {
                    if (int.Parse(QUESTION_NUM.Text) < 30)
                    {
                        QUESTION_NUM.Text = (int.Parse(QUESTION_NUM.Text) + 1).ToString();
                    }
                }
                else if (button.Name == "TimeInc")
                {
                    if(int.Parse(QUESTION_TIME.Text) <= 300)//five minuetes.
                    {
                        QUESTION_TIME.Text = (int.Parse(QUESTION_TIME.Text) + 5).ToString();
                    }
                }

            }
        }

        private void Dec_click(object sender, RoutedEventArgs e)
        {
            /*
            event handler for decrease button click, destinguishes the three different decrease buttons.
            in: the sender (Button), the event arguments.
            out: none.
            */

            if (sender is Button)
            {
                Button button = sender as Button;

                if (button.Name == "PlayersDec")
                {
                    if (int.Parse(PLAYERS_NUM.Text) > 2)
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
                    if (int.Parse(QUESTION_TIME.Text) > 5)
                    {
                        QUESTION_TIME.Text = (int.Parse(QUESTION_TIME.Text) - 5).ToString();
                    }
                }

            }
        }

        private async void Create_Click(object sender, RoutedEventArgs e)
        {
            /*
            event handler for create room button click, tries to preform the create room action.
            in: the sender (Button), the event arguments.
            out: none.
            */
            if (int.Parse(PLAYERS_NUM.Text) > 1 && int.Parse(QUESTION_NUM.Text) > 0 && double.Parse(QUESTION_TIME.Text) > 0 && ROOMNAME.Text.Length != 0)
            {
                int id = await Communicator.createRoom(ROOMNAME.Text, uint.Parse(PLAYERS_NUM.Text), uint.Parse(QUESTION_NUM.Text), int.Parse(QUESTION_TIME.Text));
                if (id >= CreateRoomResponse.CREATE_ROOM_SUCESS_ID)
                {
                    Room room = new Room(Left, Top, Width, Height, WindowState, ROOMNAME.Text, id.ToString(),PLAYERS_NUM.Text);
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
            /*
            event handler for back to menu button click, returns to the main menu.
            in: the sender (Button), the event arguments.
            out: none.
            */

            MainMenu menu = new MainMenu(Left, Top, Width, Height, WindowState, "");
            menu.Show();
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
            puts connected user's name in the name box.
            in: none.
            out: none.
            */

            string temp = "Hello " + Communicator.getName();
            name.Text = temp;
        }

        private void PLAYERS_NUM_TextChanged(object sender, TextChangedEventArgs e)
        {
            /*
            event handler for text changed in number of players setting, checks change is valid.
            in: the sender (the text box), the event arguments.
            out: none.
            */

            try
            {
                if (int.Parse(PLAYERS_NUM.Text) < 2)
                {
                    PLAYERS_NUM.Text = "2"; //default value.
                    ERRORS.Text = "Illegal Room Settings - Needs At Least 2 For a Game.";
                }
                else if (int.Parse(PLAYERS_NUM.Text) > 500)
                {
                    PLAYERS_NUM.Text = "2"; //default value.
                    ERRORS.Text = "Illegal Room Settings - Too Many Players.";
                }
            }
            catch 
            {
                PLAYERS_NUM.Text = "2"; //default value.
                ERRORS.Text = "Illegal Room Settings";
            }
        }

        private void QUESTION_NUM_TextChanged(object sender, TextChangedEventArgs e)
        {
            /*
            event handler for text changed in number of questions setting, checks change is valid.
            in: the sender (the text box), the event arguments.
            out: none.
            */

            try
            {
                if (int.Parse(QUESTION_NUM.Text) < 1)
                {
                    QUESTION_NUM.Text = "1"; //Default Value.
                    ERRORS.Text = "Illegal Room Settings - Needs At Least One Question For a Game.";
                }
                else if (int.Parse(QUESTION_NUM.Text) > 30)
                {
                    QUESTION_NUM.Text = "1";
                    ERRORS.Text = "Illegal Room Settings - Max Question Number is 30.";
                }
            }
            catch
            {
                QUESTION_NUM.Text = "1";
                ERRORS.Text = "Illegal Room Settings";
            }
        }

        private void QUESTION_TIME_TextChanged(object sender, TextChangedEventArgs e)
        {
            /*
            event handler for text changed in time for question setting, checks change is valid.
            in: the sender (the text box), the event arguments.
            out: none.
            */

            try
            {
                if (int.Parse(QUESTION_TIME.Text) < 1)
                {
                    QUESTION_TIME.Text = "5"; //default
                    ERRORS.Text = "Illegal Room Settings - Minimum one second for question.";
                }
                else if (int.Parse(QUESTION_TIME.Text) > 305) // max question time.
                {
                    QUESTION_TIME.Text = "5";
                    ERRORS.Text = "Illegal Room Settings - max question time is 5:05 minuetes.";
                }
            }
            catch
            {
                QUESTION_TIME.Text = "5";
                ERRORS.Text = "Illegal Room Settings";
            }
        }
    }
}
