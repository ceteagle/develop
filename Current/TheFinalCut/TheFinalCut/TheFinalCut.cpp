#include <iostream>
#include "Graphics/Engine.h"
#include "Graphics/Sprite.h"
#include "Graphics/Mouse.h"
#include "Graphics/Keyboard.h"
#include "Graphics/Physics/RigidBody.h"
#include "Math/Vector3.h"

using namespace std;
using namespace TFC::Graphics;
using namespace TFC::Graphics::Physics;
using namespace TFC::Math;

int main()
{
    cout << "Welcome to The Final Cut" << endl;

    Engine engine;
    engine.Initialize("The Final Cut");

    Vector3<float> pos(100., 100., 0.0);

    Sprite sprite = Sprite("D:\\Development\\Thirdparty\\Simple OpenGL Image Library\\img_test.png", pos );
    //Sprite sprite = Sprite("D:\\Development\\develop\\Current\\TheFinalCut\\TheFinalCut\\Assets\\Images\\sprite_base_addon_2012_12_14.png", pos );
    RigidBody rigidBody = RigidBody();
    rigidBody.Initialize(9.8, 0.9, sprite);
        
    sprite.SetScale(0.25f);
    sprite.SpeedTo(300.0);
    
    while (true)
    {
        engine.Update();
        
        {
            rigidBody.Update();
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
                rigidBody.AddForce(Vector3<float>(0.0, 20.0, 0.0));
            }
            if (Keyboard::Key(GLFW_KEY_A))
            {
                rigidBody.AddForce(Vector3<float>(-20.0, 0.0, 0.0));

            }
            if (Keyboard::Key(GLFW_KEY_S))
            {
                rigidBody.AddForce(Vector3<float>(0.0, -20.0, 0.0));

            }
            if (Keyboard::Key(GLFW_KEY_D))
            {
                rigidBody.AddForce(Vector3<float>(20.0, 0.0, 0.0));
            }
        }

        engine.BeginRender();
        {
            rigidBody.Render(Vector3<float>(1.0, 1.0, 1.0));
        }
        engine.EndRender();
    }
    return 0;
}