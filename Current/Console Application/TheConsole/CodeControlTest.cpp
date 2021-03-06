#include "stdafx.h"
#include "CodeControlTest.h"
#include "Timer.h"
#include "TimerManager.h"

#include <random>

CodeControlTest::CodeControlTest()
{
}

CodeControlTest::~CodeControlTest()
{
}

void CodeControlTest::SwitchControlTest()
{
	int key = 0;

	int mapsize = 200;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, mapsize);
	int dice_roll = distribution(generator);  // generates number in the range 1..6 

	::std::string info = "CodeControlTest::SwitchControlTest";

	for (size_t i = 0; i < 10; i++)
	{
		dice_roll = distribution(generator);
		Timer t(info + " " + std::to_string(dice_roll), kTimerNoOutput);

		switch (key)
		{
		case 0:	break;
		case 1:	break;
		case 2: break;
		case 3:	break;
		case 4:	break;
		case 5: break;
		case 6:	break;
		case 7:	break;
		case 8: break;
		case 9:	break;
		case 10:	break;
		case 11:	break;
		case 12:	break;
		case 13:	break;
		case 14:	break;
		case 15:	break;
		case 16:	break;
		case 17:	break;
		case 18:	break;
		case 19:	break;
		case 20:	break;
		case 21:	break;
		case 22:	break;
		case 23:	break;
		case 24:	break;
		case 25:	break;
		case 26:	break;
		case 27:	break;
		case 28:	break;
		case 29:	break;
		case 30:	break;
		case 31:	break;
		case 32:	break;
		case 33:	break;
		case 34:	break;
		case 35:	break;
		case 36:	break;
		case 37:	break;
		case 38:	break;
		case 39:	break;
		case 40:	break;
		case 41:	break;
		case 42:	break;
		case 43:	break;
		case 44:	break;
		case 45:	break;
		case 46:	break;
		case 47:	break;
		case 48:	break;
		case 49:	break;
		case 50:	break;
		case 51:	break;
		case 52:	break;
		case 53:	break;
		case 54:	break;
		case 55:	break;
		case 56:	break;
		case 57:	break;
		case 58:	break;
		case 59:	break;
		case 60:	break;
		case 61:	break;
		case 62:	break;
		case 63:	break;
		case 64:	break;
		case 65:	break;
		case 66:	break;
		case 67:	break;
		case 68:	break;
		case 69:	break;
		case 70:	break;
		case 71:	break;
		case 72:	break;
		case 73:	break;
		case 74:	break;
		case 75:	break;
		case 76:	break;
		case 77:	break;
		case 78:	break;
		case 79:	break;
		case 80:	break;
		case 81:	break;
		case 82:	break;
		case 83:	break;
		case 84:	break;
		case 85:	break;
		case 86:	break;
		case 87:	break;
		case 88:	break;
		case 89:	break;
		case 90:	break;
		case 91:	break;
		case 92:	break;
		case 93:	break;
		case 94:	break;
		case 95:	break;
		case 96:	break;
		case 97:	break;
		case 98:	break;
		case 99:	break;
		case 100:	break;
		case 101:	break;
		case 102:	break;
		case 103:	break;
		case 104:	break;
		case 105:	break;
		case 106:	break;
		case 107:	break;
		case 108:	break;
		case 109:	break;
		case 110:	break;
		case 111:	break;
		case 112:	break;
		case 113:	break;
		case 114:	break;
		case 115:	break;
		case 116:	break;
		case 117:	break;
		case 118:	break;
		case 119:	break;
		case 120:	break;
		case 121:	break;
		case 122:	break;
		case 123:	break;
		case 124:	break;
		case 125:	break;
		case 126:	break;
		case 127:	break;
		case 128:	break;
		case 129:	break;
		case 130:	break;
		case 131:	break;
		case 132:	break;
		case 133:	break;
		case 134:	break;
		case 135:	break;
		case 136:	break;
		case 137:	break;
		case 138:	break;
		case 139:	break;
		case 140:	break;
		case 141:	break;
		case 142:	break;
		case 143:	break;
		case 144:	break;
		case 145:	break;
		case 146:	break;
		case 147:	break;
		case 148:	break;
		case 149:	break;
		case 150:	break;
		case 151:	break;
		case 152:	break;
		case 153:	break;
		case 154:	break;
		case 155:	break;
		case 156:	break;
		case 157:	break;
		case 158:	break;
		case 159:	break;
		case 160:	break;
		case 161:	break;
		case 162:	break;
		case 163:	break;
		case 164:	break;
		case 165:	break;
		case 166:	break;
		case 167:	break;
		case 168:	break;
		case 169:	break;
		case 170:	break;
		case 171:	break;
		case 172:	break;
		case 173:	break;
		case 174:	break;
		case 175:	break;
		case 176:	break;
		case 177:	break;
		case 178:	break;
		case 179:	break;
		case 180:	break;
		case 181:	break;
		case 182:	break;
		case 183:	break;
		case 184:	break;
		case 185:	break;
		case 186:	break;
		case 187:	break;
		case 188:	break;
		case 189:	break;
		case 190:	break;
		case 191:	break;
		case 192:	break;
		case 193:	break;
		case 194:	break;
		case 195:	break;
		case 196:	break;
		case 197:	break;
		case 198:	break;
		case 199:	break;
		case 200:	break;

		default:break;
		}
	}

	TimerManager::Instance().Average(info);
}
