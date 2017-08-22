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
        private List<Skill> _skills;

        public Character()
        {
            _skills = new List<Skill>();
        }

        public List<Skill> Skills
        {
            get
            {
                return _skills;
            }
        }
    }
}
