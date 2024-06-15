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
        int totalQ;
        int answeredQ;

        //timer related
        private int time;
        private int room_id;
        private double tempTime;
        private DispatcherTimer dispatcherTimer;

        public Game(double left, double top, double width, double height, WindowState windowstate, int numOfQuestions, int timeForQuestion, int roomId, int num)
        {
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
        }

        private void putName()
        {
            USERNAME.Text = Communicator.getName();
        }

        void resetTimer()
        {
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
            if (tempTime > 0)
            {
                tempTime--;
                TIME.Text = string.Format("00:{0:D2}:{1:D2}", Convert.ToInt32(tempTime) / 60, Convert.ToInt32(tempTime) % 60);
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
            _answered = false;
            getQuestionResponse question = await Communicator.getNextQuestion();
            if (question.status != getQuestionResponse.QUESTIONS_OVER)
            {
                resetTimer();
                QUESTION.Text = question.Question;
                ANS1.Content = question.Answers[0];
                ANS2.Content = question.Answers[1];
                ANS3.Content = question.Answers[2];
                ANS4.Content = question.Answers[3];

                ANS1.Background = Brushes.LightGray;
                ANS2.Background = Brushes.LightGray;
                ANS3.Background = Brushes.LightGray;
                ANS4.Background = Brushes.LightGray;

                answeredQ++;
                ANSWERED.Text = answeredQ.ToString() + "/" + totalQ.ToString();
            }
            else
            {
                GameResults gr = new GameResults(Left, Top, Width, Height, WindowState, totalQ, time, room_id);
                gr.Show();
                _isClosedByX = false;
                this.Close();
            }
            
        }

        private async void sendAns_click(object sender, RoutedEventArgs e)
        {
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
                }
                else if (resp == 2)
                {
                    ANS2.Background = Brushes.LimeGreen;//correct
                    ANS1.Background = Brushes.DarkRed;
                    ANS3.Background = Brushes.DarkRed;
                    ANS4.Background = Brushes.DarkRed;
                }
                else if (resp == 3)
                {
                    ANS3.Background = Brushes.LimeGreen;//correct
                    ANS2.Background = Brushes.DarkRed;
                    ANS1.Background = Brushes.DarkRed;
                    ANS4.Background = Brushes.DarkRed;
                }
                else //4
                {
                    ANS4.Background = Brushes.LimeGreen;//correct
                    ANS2.Background = Brushes.DarkRed;
                    ANS3.Background = Brushes.DarkRed;
                    ANS1.Background = Brushes.DarkRed;
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
            int res = await Communicator.LeaveGame();
            if(res == 1)
            {
                MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState);
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
            if (_isClosedByX)
            {
                int ok = await Communicator.LeaveGame();
                ok = await Communicator.signoutAsync();
            }
        }
    }
}
