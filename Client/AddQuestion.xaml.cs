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
using System.Xml.Linq;

namespace Client
{
    /// <summary>
    /// Interaction logic for Signup.xaml
    /// </summary>
    public partial class AddQuestion : Window
    {
        public bool _isClosedByX = true;

        const string USERNAME_TAKEN = "This Username is already taken.\n";
        const string PASSWORDS_NOT_MATCH = "Passwords dont match.\n";
        const string INVALID_MAIL = "Invalid mail.\n";

        public AddQuestion(double left, double top, double width, double height, WindowState windowstate)
        {
            /*
            signup window C'tor.
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

        private async void enter_click(object sender, RoutedEventArgs e)
        {
            /*
            event handler for the signup enter button, tries to prefom the signup request.
            in: the sender, the event's arguments.
            out: none.
            */

            string temp = QUESTION.Text, temp2;
            int ok = 0;
            string errors = "";

            if (QUESTION.Text.Length == 0)
            {
                ERRORS.Text = "Invalid question";
            }
            else
            {
                if (RIGHTANS.Text.Length == 0)
                {
                    ERRORS.Text = "Invalid right answer";
                }
                else if (WRONG1.Text.Length == 0)
                {
                    ERRORS.Text = "Invalid wrong answer 1";
                }
                else if (WRONG2.Text.Length == 0)
                {
                    ERRORS.Text = "Invalid wrong answer 2";
                }
                else if (WRONG3.Text.Length == 0)
                {
                    ERRORS.Text = "Invalid wrong answer 3";
                }
                else
                {
                    ok = await Communicator.addQuestionAsync(RIGHTANS.Text, WRONG1.Text, WRONG2.Text, WRONG3.Text, QUESTION.Text);
                    if (ok == AddQuestionResponse.ADDED)
                    {
                        MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState, "");
                        men.Show();
                        _isClosedByX = false;
                        this.Close();
                    }
                    else if (ok == AddQuestionResponse.ERROR_ADDING)
                    {
                        ERRORS.Text = "error in adding question";
                    }
                    else
                    {
                        ERRORS.Text = "Connection error.";
                    }
                }

            }
        }

        private async void back_click(object sender, RoutedEventArgs e)
        {
            /*
            event handler for the back button - returns to main menu.
            in: the sender, the event's arguments.
            out: none.
            */

            MainMenu sigi = new MainMenu(Left, Top, Width, Height, WindowState, "");
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
            displays name of connected user in the name textblock.
            in&out: none.
            */

            string temp = "hello " + Communicator.getName();
            name.Text = temp;
        }
    }
}
