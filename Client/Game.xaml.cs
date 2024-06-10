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
using System.Windows.Threading;
using System.Xml.Linq;

namespace Client
{
    /// <summary>
    /// Interaction logic for Game.xaml
    /// </summary>
    public partial class Game : Window
    {
        private bool _isClosedByX = true;
        int totalQ;
        int answeredQ;

        //timer related
        private double time;
        private double tempTime;
        private DispatcherTimer dispatcherTimer;

        public Game(double left, double top, double width, double height, WindowState windowstate, int numOfQuestions, int timeForQuestion)
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
        }

        private void putName()
        {
            USERNAME.Text = Communicator.getName();
        }

        void resetTimer()
        {
            tempTime = time;
            TIME.Text = string.Format("00:{0:D2}:{1:D2}", Convert.ToInt32(time) / 60, Convert.ToInt32(time) % 60);
            dispatcherTimer = new DispatcherTimer();
            dispatcherTimer.Interval = new TimeSpan(0, 0, 0, 1);
            dispatcherTimer.Tick += Timer_tick;
            dispatcherTimer.Start();
        }

        void Timer_tick(object sender, EventArgs e)
        {
            if (time > 0)
            {
                time--;
                TIME.Text = string.Format("00:{0:D2}:{1:D2}", Convert.ToInt32(time) / 60, Convert.ToInt32(time) % 60);
            }
            else
            {
                dispatcherTimer.Stop();
                getNextQuestion();
            }
        }

        async void getNextQuestion()
        {
            resetTimer();
            getQuestionResponse question = await Communicator.getNextQuestion();
            if (question.status != getQuestionResponse.QUESTIONS_OVER)
            {
                QUESTION.Text = question.Question;
                ANS1.Content = question.Answers[0];
                ANS2.Content = question.Answers[1];
                ANS3.Content = question.Answers[2];
                ANS4.Content = question.Answers[3];

                answeredQ++;
                ANSWERED.Text = answeredQ.ToString() + "/" + totalQ.ToString();
                resetTimer();
            }
            else
            {
                GameResults gr = new GameResults();
                gr.Show();
                _isClosedByX = false;
                this.Close();
            }
            
        }

        private async void sendAns_click(object sender, RoutedEventArgs e)
        {
            int resp = 0;
            uint ans = 0;
            Button clicked = sender as Button;
            if(clicked.Name == "ANS1") 
            {
                ans = 1;
            }
            else if(clicked.Name == "ANS2")
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
            resp = await Communicator.SubmitAnswer(ans);
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
            if(ans != resp)
            {
                if(ans == 1)
                {
                    ANS1.Background = Brushes.Firebrick;
                }
                else if (ans == 2)
                {
                    ANS2.Background = Brushes.Firebrick;
                }
                else if (ans == 2)
                {
                    ANS3.Background = Brushes.Firebrick;
                }
                else //4
                {
                    ANS4.Background = Brushes.Firebrick;
                }
            }

            getNextQuestion();
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
