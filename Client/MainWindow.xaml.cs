using Requests;
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

namespace Client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Communicator communicator;

        public MainWindow()
        {
            InitializeComponent();
            communicator = new Communicator();
        }

        private void moveToSignUp_click(object sender, RoutedEventArgs e)
        {
            Signup sigi = new Signup();
            sigi.Show();
            this.Close();
        }
        
        private async void enterLogin_clickAsync(object sender, RoutedEventArgs e)
        {
            uint ok = await Communicator.loginAsync(USERNAME.Text, PASSWORD.Text);
            if (ok == LoginResponse.LOGIN_SUCCESS)
            {
                MainMenu men = new MainMenu();
                men.Show();
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
                    LOGIN_ERORR.Text = "No user with given name exists, log in insted?";
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
    }
}