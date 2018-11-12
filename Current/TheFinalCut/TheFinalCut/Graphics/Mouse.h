#ifndef __MOUSE__H__
#define __MOUSE__H__

#include "GLFW/glfw3.h"

namespace TFC
{
    namespace Graphics
    {
        class Mouse
        {
        public:
            static void MousePosCallback(GLFWwindow* window, double x, double y);
            static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
            static double GetX();
            static double GetY();
            static bool ButtonDown(int button);
            static bool ButtonUp(int button);
            static bool Button(int button);

        private:
            static double _x;
            static double _y;

            static bool _buttons[];
            static bool _buttonsDown[];
            static bool _buttonsUp[];
        };
    }
}

#endif  // __MOUSE__H__