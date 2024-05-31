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
        const string USERNAME_TAKEN = "This Username is already taken.\n";
        const string PASSWORDS_NOT_MATCH = "Passwords dont match.\n";
        const string INVALID_MAIL = "Invalid mail.\n";

        public Signup()
        {
            InitializeComponent();
        }

        private async void signupEnter_click(object sender, RoutedEventArgs e)
        {
            uint ok = 0;
            string errors = "";
            //check username existance with the server.
            
            if(NEWPASS.Text != REPASS.Text)
            {
                errors += PASSWORDS_NOT_MATCH;
            }
            if(!NEWMAIL.Text.Contains('@'))
            {
                errors += INVALID_MAIL; // will maybe add better check further on.
            }

            if(errors != "")
            {
                ERRORS.Text = errors;
            }
            else
            {
                ok = await Communicator.signupAsync(NEWSERNAME.Text, NEWPASS.Text, NEWMAIL.Text);
                if(ok == SignupResponse.SIGNUP_SUCCESS)
                {
                    MainMenu men = new MainMenu();
                    men.Show();
                    this.Close();
                }
                else
                {
                    ERRORS.Text = "Username already taken";
                }
            }
        }
    }
}
