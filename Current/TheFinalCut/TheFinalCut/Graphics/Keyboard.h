#ifndef __KEYBOARD__H__
#define __KEYBOARD__H__

#include "GLFW/glfw3.h"

namespace TFC
{
    namespace Graphics
    {
        class Keyboard
        {
        public:
            static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

            static bool KeyDown(int key);
            static bool KeyUp(int key);
            static bool Key(int key);

        private:
            static bool _keys[];
            static bool _keysDown[];
            static bool _keysUp[];
        };
    }
}

#endif  // __KEYBOARD__H__