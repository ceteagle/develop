using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RWLib
{
    public enum SkillType
    {
        Animals,
        Artistic,
        Construction,
        Cooking,
        Crafting,
        Growing,
        Medicine,
        Melee,
        Mining,
        Intellectual,
        Shooting,
        Social,
        Training
    }

    public class Skill
    {
        private Skill() { }

        public Skill(SkillType type, int level)
        {
            Type = type;
            Level = level;
        }

        public SkillType Type { get; set; }
        public int Level { get; set; }
    }
}
