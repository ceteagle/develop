using RWLib;
using System.Collections.ObjectModel;
using System.Windows;

namespace RWApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Manager _manager;
        public MainWindow()
        {
            InitializeComponent();

            SaveCharacterButton.Visibility = Visibility.Hidden;

            _manager = new Manager();

            Main.Content = new HomePage();
        }
        
        // PRIVATE

        private void LoadButton_Click(object sender, RoutedEventArgs e)
        {
            SaveCharacterButton.Visibility = Visibility.Hidden;

            Main.Content = new CharacterListPage();
        }

        private void AddCharacterButton_Click(object sender, RoutedEventArgs e)
        {
            var character = _manager.CreateCharacter();
            character.Animals = 100;
            character.Artistic = 50;

            SaveCharacterButton.Visibility = Visibility.Visible;

            this.DataContext = character;
            Main.Content = new CharacterCreationPage();
        }

        private void SaveCharacterButton_Click(object sender, RoutedEventArgs e)
        {
            SaveCharacterButton.Visibility = Visibility.Hidden;

            var page = new CharacterDataPage();
            var characterNames = new ObservableCollection<string>();
            foreach (var character in _manager.Characters)
            {
                characterNames.Add(character.Name);
            }
            page.CharactersListBox.ItemsSource = characterNames;
            Main.Content = page;
        }
    }
}
