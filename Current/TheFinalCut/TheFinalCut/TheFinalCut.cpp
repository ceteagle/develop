#include <iostream>
#include "Graphics/Engine.h"
#include "Graphics/Sprite.h"
#include "Graphics/Mouse.h"
#include "Graphics/Keyboard.h"
#include "Math/Vector3.h"

using namespace std;
using namespace TFC::Graphics;
using namespace TFC::Math;

int main()
{
    cout << "Welcome to The Final Cut" << endl;

    Engine engine;
    engine.Initialize("The Final Cut");

    Vector3<float> pos(100., 100., 0.0);

    Sprite sprite = Sprite("D:\\Development\\Thirdparty\\Simple OpenGL Image Library\\img_test.png", pos );

    while (true)
    {
        engine.Update();
        
        {
            sprite.Update();
            sprite.SetScale(0.25f);
            sprite.SpeedTo(300.0);
        }

        {   // MOUSE EVENTS
            if (Mouse::ButtonDown(GLFW_MOUSE_BUTTON_LEFT))
            {
                sprite.RotateBy(100.0);
            }
            if (Mouse::ButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
            {
                sprite.RotateBy(-100.0);
            }
            if (Mouse::Button(GLFW_MOUSE_BUTTON_MIDDLE))
            {
                sprite.RotateBy(100.0);
            }
        }

        {   // KEYBOARD EVENTS
            if (Keyboard::Key(GLFW_KEY_W))
            {
                sprite.MoveUp();
            }
            if (Keyboard::Key(GLFW_KEY_A))
            {
                sprite.MoveLeft();
            }
            if (Keyboard::Key(GLFW_KEY_S))
            {
                sprite.MoveDown();
            }
            if (Keyboard::Key(GLFW_KEY_D))
            {
                sprite.MoveRight();
            }
        }

        engine.BeginRender();
        {
            sprite.Render();
        }
        engine.EndRender();
    }
    return 0;
}