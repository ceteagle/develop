#ifndef __ENGINE__H__
#define __ENGINE__H__

#include "GLFW/glfw3.h"
#pragma comment(lib, "opengl32.lib")

namespace TFC
{
    namespace Graphics
    {
        class Engine
        {
        public:
            Engine();
            ~Engine();

            bool Initialize(const char * title);

            void Update();
            void BeginRender();
            void EndRender();

            static int SCREEN_WIDTH;
            static int SCREEN_HEIGHT;

            static double GetDeltaTime() { return _deltaTime; }

        private:
            static GLFWwindow * _window;
            static double _deltaTime;
            double _lastTime;
        };

    }
}

#endif	// __ENGINE__H__

