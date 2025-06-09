using Responses;
using System;
using System.Collections.Generic;
using System.Diagnostics;
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
using System.Windows.Media.Media3D;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Xml.Linq;

namespace Client
{
    /// <summary>
    /// Interaction logic for Game.xaml
    /// </summary>
    public partial class Game : Window
    {
        private Stopwatch stopwatch = new Stopwatch();
        private bool _isClosedByX = true;
        private bool _answered = false;
        private bool _leaved = false;
        int totalQ;
        int answeredQ;

        //timer related
        private int time;
        private int room_id;
        private double tempTime;
        private DispatcherTimer dispatcherTimer;
        private int playernum = 0;
        private string name;

        public Game(double left, double top, double width, double height, WindowState windowstate, int numOfQuestions, int timeForQuestion, int roomId, int num, string roomName)
        {
            /*
            game window C'tor.
            in: the window's position (left, top, width, height, windowstate), the number of questions in the game, the time for each question.
            */

            InitializeComponent();
            Left = left;
            Top = top;
            Width = width;
            Height = height;
            WindowState = windowstate;

            answeredQ = 0;
            totalQ = numOfQuestions;
            time = timeForQuestion;

            putName();
            getNextQuestion();
            this.room_id = roomId;
            playernum = num;
            name = roomName;
        }

        private void putName()
        {
            /*
            puts user's name in the name textBlock.
            in&out: none.
            */

            USERNAME.Text = Communicator.getName();
        }

        void resetTimer()
        {
            /*
            resets question's timer with the time for each question in the game and starts it.
            in: none.
            out: none.
            */

            tempTime = time;
            TIME.Text = string.Format("00:{0:D2}:{1:D2}", Convert.ToInt32(tempTime) / 60, Convert.ToInt32(tempTime) % 60);
            dispatcherTimer = new DispatcherTimer();
            dispatcherTimer.Interval = new TimeSpan(0, 0, 0, 1);
            dispatcherTimer.Tick += Timer_tick;
            dispatcherTimer.Start();
            stopwatch.Start();
        }

        void Timer_tick(object sender, EventArgs e)
        {
            /*
            event for each timer's tick, decreases time left for question by one second.
            in: the sender, the event arguments.
            out: none.
            */

            if (tempTime > 0)
            {
                if(_answered)
                {
                    tempTime--;
                    TIME.Text = string.Format("00:00", Convert.ToInt32(tempTime) / 60, Convert.ToInt32(tempTime) % 60);
                    if(tempTime % 2 == 0)
                    {
                        TIME.Visibility = Visibility.Hidden;
                    }
                    else
                    {
                        TIME.Visibility = Visibility.Visible;
                        TIME.Foreground = Brushes.DarkRed;
                    }
                }
                else
                {
                    if (tempTime <= 10)
                    {
                        TIME.Foreground = Brushes.DarkRed;
                        TIME.Visibility = Visibility.Visible;
                        tempTime--;
                        TIME.Text = string.Format("{0:D2}:{1:D2}", Convert.ToInt32(tempTime) / 60, Convert.ToInt32(tempTime) % 60);
                    }
                    else
                    {
                        TIME.Foreground = Brushes.Lime;
                        TIME.Visibility = Visibility.Visible;
                        tempTime--;
                        TIME.Text = string.Format("{0:D2}:{1:D2}", Convert.ToInt32(tempTime) / 60, Convert.ToInt32(tempTime) % 60);
                    }
                }
            }
            else
            {
                dispatcherTimer.Stop();
                getNextQuestion();
                stopwatch.Stop();
            }
        }

        async void getNextQuestion()
        {
            /*
            gets next question in game for user, ends game if no questions left.
            in: none.
            out: none.
            */
            if (!_leaved)
            {
                _answered = false;
                getQuestionResponse question = await Communicator.getNextQuestion();
                if (question.status != getQuestionResponse.QUESTIONS_OVER)
                {
                    resetTimer();
                    QUESTION.Text = question.Question;
                    ANS1.Content = new TextBlock()
                    {
                        Text = question.Answers[0],
                        TextWrapping = TextWrapping.WrapWithOverflow,
                    };
                    ANS2.Content = new TextBlock()
                    {
                        Text = question.Answers[1],
                        TextWrapping = TextWrapping.WrapWithOverflow,
                    };
                    ANS3.Content = new TextBlock()
                    {
                        Text = question.Answers[2],
                        TextWrapping = TextWrapping.WrapWithOverflow,
                    };
                    ANS4.Content = new TextBlock()
                    {
                        Text = question.Answers[3],
                        TextWrapping = TextWrapping.WrapWithOverflow,
                    };

                    ANS1.Background = Brushes.LightBlue;
                    ANS2.Background = Brushes.LightBlue;
                    ANS3.Background = Brushes.LightBlue;
                    ANS4.Background = Brushes.LightBlue;

                    ANS1.BorderBrush = Brushes.LightBlue;
                    ANS2.BorderBrush = Brushes.LightBlue;
                    ANS3.BorderBrush = Brushes.LightBlue;
                    ANS4.BorderBrush = Brushes.LightBlue;

                    ANS1.Opacity = 0.5;
                    ANS2.Opacity = 0.5;
                    ANS3.Opacity = 0.5;
                    ANS4.Opacity = 0.5;

                    answeredQ++;
                    ANSWERED.Text = answeredQ.ToString() + "/" + totalQ.ToString();
                }
                else
                {
                    GameResults gr = new GameResults(Left, Top, Width, Height, WindowState, totalQ, time, room_id, this.playernum, this.name);
                    gr.Show();
                    _isClosedByX = false;
                    this.Close();
                }
            }
            
        }

        private async void sendAns_click(object sender, RoutedEventArgs e)
        {
            /*
            event for answer sending (clicking it) event, seperates the 4 different buttons.
            in: the sender (the clicked button), event arguments.
            */

            if (!_answered)
            {
                int resp = 0;
                uint ans = 0;
                Button clicked = sender as Button;
                if (clicked.Name == "ANS1")
                {
                    ans = 1;
                }
                else if (clicked.Name == "ANS2")
                {
                    ans = 2;
                }
                else if (clicked.Name == "ANS3")
                {
                    ans = 3;
                }
                else // ANS4
                {
                    ans = 4;
                }
                stopwatch.Stop();
                resp = await Communicator.SubmitAnswer(ans, stopwatch.Elapsed.TotalSeconds);
                tempTime = 3;
                _answered = true;

                if (resp == 1)
                {
                    ANS1.Background = Brushes.LimeGreen;//correct
                    ANS2.Background = Brushes.DarkRed;
                    ANS3.Background = Brushes.DarkRed;
                    ANS4.Background = Brushes.DarkRed;

                    ANS1.BorderBrush = Brushes.DarkGreen;
                    ANS2.BorderBrush = Brushes.Brown;
                    ANS3.BorderBrush = Brushes.Brown;
                    ANS4.BorderBrush = Brushes.Brown;
                }
                else if (resp == 2)
                {
                    ANS2.Background = Brushes.LimeGreen;//correct
                    ANS1.Background = Brushes.Brown;
                    ANS3.Background = Brushes.Brown;
                    ANS4.Background = Brushes.Brown;

                    ANS2.BorderBrush = Brushes.LimeGreen;
                    ANS1.BorderBrush = Brushes.Brown;
                    ANS3.BorderBrush = Brushes.Brown;
                    ANS4.BorderBrush = Brushes.Brown;
                }
                else if (resp == 3)
                {
                    ANS3.Background = Brushes.LimeGreen;//correct
                    ANS2.Background = Brushes.Brown;
                    ANS1.Background = Brushes.Brown;
                    ANS4.Background = Brushes.Brown;

                    ANS3.BorderBrush = Brushes.LimeGreen;
                    ANS2.BorderBrush = Brushes.Brown;
                    ANS1.BorderBrush = Brushes.Brown;
                    ANS4.BorderBrush = Brushes.Brown;
                }
                else //4
                {
                    ANS4.Background = Brushes.LimeGreen;//correct
                    ANS2.Background = Brushes.DarkRed;
                    ANS3.Background = Brushes.DarkRed;
                    ANS1.Background = Brushes.DarkRed;

                    ANS4.BorderBrush = Brushes.LimeGreen;
                    ANS2.BorderBrush = Brushes.Brown;
                    ANS3.BorderBrush = Brushes.Brown;
                    ANS1.BorderBrush = Brushes.Brown;
                }
                if (ans != resp)
                {
                    if (ans == 1)
                    {
                        ANS1.Background = Brushes.Firebrick;
                    }
                    else if (ans == 2)
                    {
                        ANS2.Background = Brushes.Firebrick;
                    }
                    else if (ans == 3)
                    {
                        ANS3.Background = Brushes.Firebrick;
                    }
                    else //4
                    {
                        ANS4.Background = Brushes.Firebrick;
                    }
                }
            }
        }

        private async void LeaveGame_click(object sender, RoutedEventArgs e)
        {
            /*
            event for the leave game button click, leaves the game.
            in: the sender, the event arguments.
            out: none.
            */

            int res = await Communicator.LeaveGame();
            if(res == 1)
            {
                _leaved = true;
                MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState, "");
                men.Show();
                _isClosedByX = false;
                this.Close();
            }
            else
            {
                //error
            }

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
                int ok = await Communicator.LeaveGame();
                ok = await Communicator.signoutAsync();
            }
        }
    }
}
