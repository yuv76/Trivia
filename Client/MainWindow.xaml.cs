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
        
        private void enterUsername_click(object sender, RoutedEventArgs e)
        {
            bool ok = communicator.login(USERNAME.Text, PASSWORD.Text);
            if (ok)
            {
                MainMenu men = new MainMenu();
                men.Show();
                this.Close();
            }
            else
            {
                USERNAME.Clear();
                PASSWORD.Clear();
            }
        }
    }
}