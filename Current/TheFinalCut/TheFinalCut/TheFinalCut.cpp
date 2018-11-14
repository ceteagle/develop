#include <iostream>
#include "Graphics/Engine.h"
#include "Graphics/Sprite.h"
#include "Graphics/Mouse.h"
#include "Graphics/Keyboard.h"
#include "Graphics/Physics/RigidBody.h"
#include "Math/Vector3.h"
#include "InputManager.h"

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
    Vector3<float> staticpos(220., 220., 0.0);

    Sprite sprite = Sprite("D:\\Development\\Thirdparty\\Simple OpenGL Image Library\\img_test.png", staticpos);
    sprite.SetScale(0.5f);
    sprite.RotateTo(45.0f);
    
    RigidBody rigidBody = RigidBody("D:\\Development\\Thirdparty\\Simple OpenGL Image Library\\img_test.png", pos);
    rigidBody.Initialize(9.8, 0.9);
    rigidBody.SetScale(0.25f);
    rigidBody.SpeedTo(300.0);

    InputManager inputManager(&rigidBody);

    Vector3<float> red(1.0, 0.0, 0.0);
    Vector3<float> white(1.0, 1.0, 1.0);

    while (true)
    {
        sprite.RotateBy(5.0);
        engine.Update();
        rigidBody.Update();
        sprite.Update();
        if (rigidBody.CollidesWith(sprite))
        {
            sprite.SetBoundingBoxColor(red);
            rigidBody.SetBoundingBoxColor(red);
        }
        else
        {
            sprite.SetBoundingBoxColor(white);
            rigidBody.SetBoundingBoxColor(white);
        }

        inputManager.Update();

        engine.BeginRender();
        {
            sprite.Render();
            rigidBody.Render(Vector3<float>(1.0, 1.0, 1.0));
        }
        engine.EndRender();

        if (inputManager.CanExit())
            break;
    }
    return 0;
}