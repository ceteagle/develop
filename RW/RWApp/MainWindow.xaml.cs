using RWLib;
using System.Windows;

namespace RWApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            Main.Content = new HomePage();
        }
        
        // PRIVATE

        private void LoadButton_Click(object sender, RoutedEventArgs e)
        {
            Main.Content = new CharacterListPage();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var character = new Character();
            character.Animals = 100;
            character.Artistic = 50;

            this.DataContext = character;
            Main.Content = new CharacterCreationPage();
        }
    }
}
