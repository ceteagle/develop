#include <iostream>
#include "Graphics/Engine.h"
#include "Graphics/Sprite.h"
#include "Graphics/Mouse.h"
#include "Graphics/Keyboard.h"
#include "Graphics/Physics/RigidBody.h"
#include "Math/Vector3.h"
#include "InputManager.h"
#include "SpriteManager.h"
#include "SceneManager.h"

#include <stdio.h>  /* defines FILENAME_MAX */
#include <direct.h>
#define GetCurrentDir _getcwd

using namespace std;
using namespace TFC::Graphics;
using namespace TFC::Graphics::Physics;
using namespace TFC::Math;

int main()
{
    cout << "Welcome to The Final Cut" << endl;
    char cCurrentPath[FILENAME_MAX];

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        return errno;
    }

    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

    cout << "The current working directory is " << cCurrentPath << endl;



    Engine engine;
    engine.Initialize("The Final Cut");

    SceneManager scene = SceneManager();
    if (!scene.Initialize())
    {
        cout << "ERROR!  Failed to initialize scene!" << endl;
        return 1;
    }

    Vector3<float> pos(100., 100., 0.0);
    Vector3<float> staticpos(220., 220., 0.0);

    RigidBody rigidBody = RigidBody(".\\Assets\\Images\\img_test.png", pos);
    rigidBody.SetGravity(9.8f);
    rigidBody.SetFriction(0.9f);
    rigidBody.SetScale(0.25f);
    rigidBody.SpeedTo(300.0);
        
    InputManager inputManager(&rigidBody);
    SpriteManager spriteManager;

    int idx = spriteManager.AddSprite(".\\Assets\\Images\\img_test.png", staticpos);
    Sprite& sprite1 = spriteManager.GetSprite(idx);
    sprite1.SetScale(0.5f);
    sprite1.RotateTo(45.0f);

    staticpos += Vector3<float>(400., 0.0, 0.0);
    
    idx = spriteManager.AddSprite(".\\Assets\\Images\\artificialPlanet.png", staticpos);
    Sprite& sprite = spriteManager.GetSprite(idx);
    sprite.SetScale(0.10f);
    sprite.RotateTo(30.0f);

    Vector3<float> red(1.0, 0.0, 0.0);
    Vector3<float> white(1.0, 1.0, 1.0);

    while (true)
    {
        engine.Update();
        scene.Update();

        rigidBody.Update();
        spriteManager.Update();
        rigidBody.SetBoundingBoxColor(white);

        for (int i = 0; i < spriteManager.Count(); i++)
        {
            if (rigidBody.GetBoundingBox().CollidesWith(spriteManager.GetSprite(i).GetBoundingBox()))
            {
                spriteManager.GetSprite(i).SetBoundingBoxColor(red);
                rigidBody.SetBoundingBoxColor(red);
            }
            else
            {
                spriteManager.GetSprite(i).SetBoundingBoxColor(white);
            }
        }

        inputManager.Update();

        engine.BeginRender();
        {
            scene.Render();

            spriteManager.Render();
            rigidBody.Render(Vector3<float>(1.0, 1.0, 1.0));
        }
        engine.EndRender();

        if (inputManager.CanExit())
            break;
    }
    return 0;
}