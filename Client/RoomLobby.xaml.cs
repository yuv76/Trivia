using Pair;
using Responses;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
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
    /// Interaction logic for Room.xaml
    /// </summary>

    public partial class Room : Window
    {
        private bool _isClosedByX = true;
        private bool _isAdmin = false;

        public Room(double left, double top, double width, double height, WindowState windowstate, string roomName, string id)
        {
            InitializeComponent();
            Left = left;
            Top = top;
            Width = width;
            Height = height;
            WindowState = windowstate;

            ROOM_NAME.Text = roomName;
            GetRoomStateResponse state = getStateAsync().Result;
            if(state.isActive == GetRoomStateResponse.CONNECTION_PROBLEM)
            {
                ERROR.Text = "Couldnt connect to room.";
                MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState);
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
        }

        private async Task<GetRoomStateResponse> getStateAsync()
        {
            GetRoomStateResponse state = await Communicator.getRoomState();
            return state;
        }

        private void updateRoom(GetRoomStateResponse roomState)
        {
            this.updatePlayers(roomState.players);
            NUM_PLAYERS.Text = roomState.players.Count.ToString() + "/" + roomState.maxPlayers.ToString() + " players";
            QUESTION_TIME.Text = roomState.timePerQuestion.ToString();
            NUM_QUESTIONS.Text = roomState.numOfQuestionsInGame.ToString();
        }

        private void updatePlayers(List<string> players)
        {
            string admin = "";
            if (players.Count > 0)
            {
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
            if(_isAdmin) // admin has to close entire room.
            {
                int close = await Communicator.CloseRoom();
                if(close == CloseRoomResponse.CLOSED)
                {
                    MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState);
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
                await Communicator.LeaveRoom();
                MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState);
                men.Show();
                _isClosedByX = false;
                this.Close();
            }
        }
        
        private async void start_Click(object sender, RoutedEventArgs e)
        {
            int started = await Communicator.StartGame();
            if(started == StartGameResponse.START_GAME)
            {
                Game game = new Game();
                game.Show();
                _isClosedByX = false;
                this.Close();
            }
            else
            {
                ERROR.Text = "Error starting game.";
            }
        }

        protected override async void OnClosed(EventArgs e)
        {
            int ok = 0;
            if (_isClosedByX)
            {
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
