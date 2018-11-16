#include <iostream>
#include "Engine/Engine.h"
#include "Managers/Managers.h"

#include "Math/Vector3.h"

#include <stdio.h>  /* defines FILENAME_MAX */
#include <direct.h>
#define GetCurrentDir _getcwd

using namespace std;
using namespace TFC::Engine;
using namespace TFC::Engine::Graphics;
using namespace TFC::Engine::Physics;
using namespace TFC::Math;

int main()
{
    /*===============================================================================*/
    /*===============================================================================*/

    cout << "Welcome to The Final Cut" << endl;
    char cCurrentPath[FILENAME_MAX];

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        cout << "ERROR!  Failed to get current directory" << endl;
        return errno;
    }

    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
    cout << "The current working directory is " << cCurrentPath << endl;
    /*===============================================================================*/
    
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

    auto playerIndex = scene.CreatePlayer(".\\Assets\\Images\\img_test.png", pos);
    pos += Vector3<float>(100.0, 0.0, 0.0);
    auto playerIndex2 = scene.CreatePlayer(".\\Assets\\Images\\img_test.png", pos);

    auto spriteIndex1 = scene.CreateSprite(".\\Assets\\Images\\img_test.png", staticpos);
    staticpos += Vector3<float>(400., 0.0, 0.0);
    auto spriteIndex2 = scene.CreateSprite(".\\Assets\\Images\\artificialPlanet.png", staticpos);

    RigidBody& player = scene.GetPlayer(playerIndex);
    player.SetGravity(9.8f);
    player.SetFriction(0.9f);
    player.SetScale(0.25f);
    player.SpeedTo(300.0);
        
    RigidBody& player2 = scene.GetPlayer(playerIndex2);
    player2.SetGravity(9.8f);
    player2.SetFriction(0.9f);
    player2.SetScale(0.25f);
    player2.SpeedTo(300.0);

    Sprite& sprite1 = scene.GetSprite(spriteIndex1);
    sprite1.SetScale(0.5f);
    sprite1.RotateTo(45.0f);
    
    Sprite& sprite = scene.GetSprite(spriteIndex2);
    sprite.SetScale(0.10f);
    sprite.RotateTo(30.0f);

    auto inputManager = InputManager(&player, WASD_PLAYER);
    auto inputManager2 = InputManager(&player2, IJKL_PLAYER);

    while (!inputManager.CanExit())
    {
        engine.Update();
        scene.Update();

        inputManager.Update();
        inputManager2.Update();

        engine.BeginRender();
        {
            scene.Render();
        }
        engine.EndRender();

    }

    return 0;
}