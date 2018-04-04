using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RWLib
{
    public class Manager
    {
        List<Character> _characters;

        public Manager()
        {
            _characters = new List<Character>();
        }

        public IEnumerable<string> CharactersNames
        {
            get
            {
                foreach (var character in Characters)
                {
                    yield return character.Name;
                }
            }
        }

        public IReadOnlyCollection<Character> Characters
        {
            get
            {
                return _characters.AsReadOnly();
            }
        }

        public Character CreateCharacter()
        {
            var character = new Character();
            _characters.Add(character);
            return character;
        }

        public void DeleteCharacter(Character character)
        {
            if (_characters.Contains(character))
                _characters.Remove(character);
        }
    }
}
