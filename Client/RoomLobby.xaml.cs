﻿using Pair;
using Responses;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Runtime.CompilerServices;
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
using static System.Runtime.InteropServices.JavaScript.JSType;
using System.Windows.Threading;
using System.ComponentModel;
using System.Reflection.Emit;

namespace Client
{
    /// <summary>
    /// Interaction logic for Room.xaml
    /// </summary>

    public partial class Room : Window
    {
        private bool _isClosedByX = true;
        private bool _isAdmin = false;
        private int NumOfQuestions = 0;
        private int TimeForQuestion = 0;
        private int playernum = 0;


        private int roomId = 0;
        bool _refreshNotComplete = false;
        private string name;

        private BackgroundWorker background_worker;

        public Room(double left, double top, double width, double height, WindowState windowstate, string roomName, string id, string num)
        {
            /*
            room lobby window C'tor.
            in: the window's position (left, top, width, height, windowstate), room's name and id.
            */

            InitializeComponent();
            Left = left;
            Top = top;
            Width = width;
            Height = height;
            WindowState = windowstate;

            ROOM_NAME.Text = roomName;
            roomId = Int32.Parse(id);
            playernum = Int32.Parse(num);
            name = roomName;


            GetRoomStateResponse state = getStateAsync().Result;
            if(state.isActive == GetRoomStateResponse.CONNECTION_PROBLEM)
            {
                ERROR.Text = "Connection error.";
                MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState, "Connection error.");
                men.Show();
                _isClosedByX = false;
                this.Close();
            }
            else
            {
                updateRoom(state);
                if (state.players[0] == Communicator.getName()) // if the room manager is the current player,
                {
                    // able the close room and start game buttons.
                    LEAVE.Content = "Close Room";
                    START.Visibility = Visibility.Visible;
                    _isAdmin = true;
                }
            }

            background_worker = new BackgroundWorker();
            background_worker.WorkerSupportsCancellation = true;
            background_worker.WorkerReportsProgress = true;
            background_worker.DoWork += refreshRoom;
            background_worker.ProgressChanged += new ProgressChangedEventHandler(background_worker_ProgressChanged);
            background_worker.RunWorkerAsync();
        }

        private void refreshRoom(object? sender, DoWorkEventArgs e)
        {
            /*
            refreshes data in the room's lobby.
            in: the sender (Can be null), the event's arguments.
            out: none.
            */

            var locker = new object();
            while (e.Cancel == false)
            {
                Thread.Sleep(3000);

                if (background_worker.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }
                while(_refreshNotComplete){ } // works like a condition variable, will wait untill finished the lastest update.
                background_worker.ReportProgress(0, 0);
            }
        }

        void background_worker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            /*
            the background worker's gui thread update - updates room's data, starts game if game started or closes room if closed by admin.
            in: the sender, the event arguments.
            out: none.
            */

            _refreshNotComplete = true;
            GetRoomStateResponse state = getStateAsync().Result;
            this.TimeForQuestion = Convert.ToInt32(state.timePerQuestion);//#TODO
            this.NumOfQuestions = Convert.ToInt32(state.numOfQuestionsInGame); //#TODO
            if (state.isActive == GetRoomStateResponse.CONNECTION_PROBLEM)
            {
                background_worker.CancelAsync(); //stop refreshing
                ERROR.Text = "Connection error.";
                MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState, "Connection error.");
                men.Show();
                _isClosedByX = false;
                this.Close();
            }
            else if (state.isActive == GetRoomStateResponse.ROOM_CLOSED)
            {
                background_worker.CancelAsync(); //stop refreshing
                MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState, "Room Closed By Admin.");
                men.Show();
                _isClosedByX = false;
                this.Close();
            }
            else if (state.isActive == GetRoomStateResponse.GAME_IN_PROGRESS)
            {
                background_worker.CancelAsync(); // stop refreshing.
                Game game = new Game(Left, Top, Width, Height, WindowState, this.NumOfQuestions, this.TimeForQuestion, this.roomId, this.playernum, this.name);
                game.Show();
                _isClosedByX = false;
                this.Close();
            }
            else
            {
                updateRoom(state);
            }
            _refreshNotComplete = false;
        }

        private async Task<GetRoomStateResponse> getStateAsync()
        {
            /*
            gets rooms state from server.
            in: none.
            out: the room's state (data) as a GetRoomStateResponse object.
            */

            GetRoomStateResponse state = await Communicator.getRoomState();
            return state;
        }

        private void updateRoom(GetRoomStateResponse roomState)
        {
            /*
            updates room's data disply.
            in: the room state to update to, a GetRoomStateResponse object.
            out: none.
            */

            this.updatePlayers(roomState.players);
            NUM_PLAYERS.Text = roomState.players.Count.ToString() + "/" + roomState.maxPlayers.ToString() + " players";
            QUESTION_TIME.Text = roomState.timePerQuestion.ToString();
            NUM_QUESTIONS.Text = roomState.numOfQuestionsInGame.ToString();
            this.NumOfQuestions = int.Parse(NUM_QUESTIONS.Text);
            this.TimeForQuestion = Convert.ToInt32(roomState.timePerQuestion);
        }

        private void updatePlayers(List<string> players)
        {
            /*
            updates list of players in the room.
            in: the list of players (first index is admin).
            out: none.
            */

            string admin = "";
            if (players.Count > 0)
            {
                PLAYERS.Items.Clear();
                admin = players[0];
                if(admin == Communicator.getName())
                {
                    PLAYERS.Items.Add(admin + " - You, Admin");
                }
                else
                {
                    PLAYERS.Items.Add(admin + " - Admin");
                }
                players.RemoveAt(0);
                foreach (string player in players)
                {
                    if (!(player == admin))
                    {
                        if (player == Communicator.getName())
                        {
                            PLAYERS.Items.Add(player + " - You");
                        }
                        else
                        {
                            PLAYERS.Items.Add(player);
                        }
                    }
                }
            }
            else
            {
                ERROR.Text = "Error loading room players.";
            }
            
        }

        private async void Leave_Click(object sender, RoutedEventArgs e)
        {
            /*
            leave room button click event handler.
            in: the sender, the event's arguments.
            out: none.
            */

            if(_isAdmin) // admin has to close entire room.
            {
                background_worker.CancelAsync(); //stop refreshing
                int close = await Communicator.CloseRoom();
                if(close == CloseRoomResponse.CLOSED)
                {
                    
                    MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState, "Room Closed By Admin.");
                    men.Show();
                    _isClosedByX = false;
                    this.Close();
                    
                }
                else if(close == LoginResponse.LOGIN_F_CONNECTION_ERROR)
                {
                    ERROR.Text = "Error connecting to server.";
                }
                else
                {
                    ERROR.Text = "Problem closing room, try again.";
                }
            }
            else // just a member, leaves by itself.
            {
                background_worker.CancelAsync(); //stop refreshing
                await Communicator.LeaveRoom();
                MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState, "");
                men.Show();
                _isClosedByX = false;
                this.Close();
            }
        }
        
        private async void start_Click(object sender, RoutedEventArgs e)
        {
            /*
            event handler for the start game button - starts game in the room (the button appears only to the manager).
            in: the sender, the event's arguments.
            out: none.
            */

            GetRoomStateResponse state = getStateAsync().Result;
            if (state.players.Count <= 2)
            {
                ERROR.Text = "Error not enough players.";
            }
            else
            {
                int started = await Communicator.StartGame();
                if (started == StartGameResponse.START_GAME)
                {
                    background_worker.CancelAsync();
                    Game game = new Game(Left, Top, Width, Height, WindowState, this.NumOfQuestions, this.TimeForQuestion, this.roomId, this.playernum, this.name);
                    game.Show();
                    _isClosedByX = false;
                    this.Close();
                }
                else
                {
                    ERROR.Text = "Error starting game.";
                }
            }
        }

        protected override async void OnClosed(EventArgs e)
        {
            /*
            event handler for closing window, seperates client closing it from closing it to move to another window.
            in: the sender (Button), the event arguments.
            out: none.
            */

            int ok = 0;
            if (_isClosedByX)
            {
                background_worker.CancelAsync(); //stop refreshing
                if(_isAdmin)
                {
                    ok = await Communicator.CloseRoom();    
                }
                else // member
                {
                    ok = await Communicator.LeaveRoom();
                }
                ok = await Communicator.signoutAsync();
            }
        }
    }
}
