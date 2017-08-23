using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RWLib
{
    public class Character
    {
        private Name _name;
        private Date _dob;

        public Character()
        {
        }

        public string FirstName { get; set; }
        public string MiddleName { get; set; }
        public string LastName { get; set; }

        public string Name
        {
            get
            {
                return string.Format("{0} {1} {2}", FirstName, MiddleName, LastName);
            }
        }
        public int Animals { get; set; }
        public int Artistic { get; set; }
        public int Construction { get; set; }
        public int Cooking { get; set; }
        public int Crafting { get; set; }
        public int Growing { get; set; }
        public int Medicine { get; set; }
        public int Melee { get; set; }
        public int Mining { get; set; }
        public int Intellectual { get; set; }
        public int Shooting { get; set; }
        public int Social { get; set; }
        public int Training { get; set; }
    }
}
