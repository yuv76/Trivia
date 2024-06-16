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

namespace Client
{
    /// <summary>
    /// Interaction logic for Signup.xaml
    /// </summary>
    public partial class Signup : Window
    {
        public bool _isClosedByX = true;

        const string USERNAME_TAKEN = "This Username is already taken.\n";
        const string PASSWORDS_NOT_MATCH = "Passwords dont match.\n";
        const string INVALID_MAIL = "Invalid mail.\n";

        public Signup(double left, double top, double width, double height, WindowState windowstate)
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
        }

        private async void signupEnter_click(object sender, RoutedEventArgs e)
        {
            /*
            event handler for the signup enter button, tries to prefom the signup request.
            in: the sender, the event's arguments.
            out: none.
            */

            string temp = NEWMAIL.Text, temp2;
            int ok = 0;
            string errors = "";
            //check username existance with the server.

            if (NEWSERNAME.Text.Length == 0)
            {
                ERRORS.Text = "Invalid username";
            }
            else
            {
                if (NEWPASS.Text != REPASS.Text)
                {
                    errors += PASSWORDS_NOT_MATCH;
                }

                string[] temp1 = temp.Split('@');
                if (!NEWMAIL.Text.Contains('@'))
                {
                    errors += INVALID_MAIL;
                }
                else
                {
                    temp2 = temp1[1];
                    string[] temp3 = temp2.Split('.');
                    if (!temp2.Contains('.'))
                    {
                        errors += INVALID_MAIL;
                    }
                    else if (temp1[0].Length < 1)
                    {
                        errors += INVALID_MAIL;
                    }
                    else if (temp3[0].Length < 1)
                    {
                        errors += INVALID_MAIL;
                    }
                    else if (temp3[1].Length != 3)
                    {
                        errors += INVALID_MAIL;
                    }
                }

            if (errors != "")
            {
                ERRORS.Text = errors;
            }
            else
            {
                ok = await Communicator.signupAsync(NEWSERNAME.Text, NEWPASS.Text, NEWMAIL.Text);
                if(ok == SignupResponse.SIGNUP_SUCCESS)
                {
                    MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState, "");
                    men.Show();
                    _isClosedByX = false;
                    this.Close();
                }
                else if(ok == SignupResponse.SIGNUP_FAIL)
                {
                    ERRORS.Text = "Username already taken";
                }
                else
                {
                    ERRORS.Text = "Connection error.";
                }
            }
        }

        private async void back_click(object sender, RoutedEventArgs e)
        {
            /*
            the back to login button event handler - returns to login.
            in: the sender, the event arguments.
            out: none.
            */

            MainWindow login = new MainWindow(Left, Top, Width, Height, WindowState);
            login.Show();
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
                int ok = await Communicator.closeConnectionAsync();
            }
        }
    }
}
