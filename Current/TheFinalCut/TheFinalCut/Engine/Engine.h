#ifndef __ENGINE__H__
#define __ENGINE__H__

#include "GLFW/glfw3.h"
#pragma comment(lib, "opengl32.lib")

#include "Graphics/Sprite.h"
#include "Inputs/Mouse.h"
#include "Inputs/Keyboard.h"
#include "Physics/RigidBody.h"

namespace TFC
{
    namespace Engine
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

            static float GetDeltaTime() { return _deltaTime; }

        private:
            static GLFWwindow * _window;
            static float _deltaTime;
            float _lastTime;
        };
    }
}

#endif	// __ENGINE__H__

