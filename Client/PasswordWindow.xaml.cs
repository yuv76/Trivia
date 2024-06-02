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
    /// Interaction logic for PasswordWindow.xaml
    /// </summary>
    public partial class PasswordWindow : Window
    {
        private string username;
        public PasswordWindow(string username)
        {
            InitializeComponent();
            this.username = username;

            Welcome.Text = "Welcome " + username + "!";
        }
        private void enterPassword_click(object sender, RoutedEventArgs e)
        {
            MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState);
            men.Show();
            this.Close();
        }
    }
}
