﻿using Requests;
using Responses;
using System.ComponentModel;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using static System.Net.Mime.MediaTypeNames;
using GrapeCity.Documents.Imaging;
using System.Runtime.InteropServices;

using System.Drawing.Text;

namespace Client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Communicator communicator;
        private bool _isClosedByX = true; // we cant know if it will be closed by x, so start value assumes it was.
        public MainWindow()
        {
            /*
            main window C'tor, creates connection with the server.
            in: none.
            */

            bool keepTrying = true;
            communicator = new Communicator();
            while (!(Communicator.isConnected()) && keepTrying)
            {
                MessageBoxResult result = MessageBox.Show(
                "Couldn't connect to server. try again?",
                "Confirmation",
                MessageBoxButton.YesNo,
                MessageBoxImage.Question);
                if(result == MessageBoxResult.No)
                {
                    keepTrying = false;
                }
                else
                {
                    communicator = new Communicator();
                }
            }
            if (keepTrying)
            {
                //means got connected eventually.
                InitializeComponent();
            }
            else
            {
                _isClosedByX = false;//no connection made - so nothing has to be closed.
                this.Close();
            }
        }

        public MainWindow(double left, double top, double width, double height, WindowState windowstate)
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
            communicator = new Communicator();
        }

        private void moveToSignUp_click(object sender, RoutedEventArgs e)
        {
            /*
            event handler to the signup button click - moves to signup window.
            in: the sender, the event arguments.
            out: none.
            */

            Signup sigi = new Signup(Left, Top, Width, Height, WindowState);
            sigi.Show();
            _isClosedByX = false;
            this.Close();
        }
        
        private async void enterLogin_clickAsync(object sender, RoutedEventArgs e)
        {
            /*
            event handler for enter button - tries to log in.
            in: the sender, the event arguments.
            out: none.
            */

            int ok = await Communicator.loginAsync(USERNAME.Text, PASSWORD.Text);
            if (ok == LoginResponse.LOGIN_SUCCESS)
            {
                MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState, "");
                men.Show();
                _isClosedByX = false;
                this.Close();
            }
            else
            {
                if(ok == LoginResponse.LOGIN_F_WRONG_PASS)
                {
                    LOGIN_ERORR.Text = "Wrong Password";
                }
                else if (ok == LoginResponse.LOGIN_F_NO_USER) 
                {
                    LOGIN_ERORR.Text = "No user with given name exists, sign up insted?";
                }
                else if(ok == LoginResponse.LOGIN_F_CONNECTED_ALREADY)
                {
                    LOGIN_ERORR.Text = "User already connected";
                }
                else
                {
                    LOGIN_ERORR.Text = "Connection error";
                }
                USERNAME.Clear();
                PASSWORD.Clear();
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
                int ok = await Communicator.closeConnectionAsync(); 
            }
        }
    }
}
