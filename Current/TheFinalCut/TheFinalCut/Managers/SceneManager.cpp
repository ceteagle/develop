#include "SceneManager.h"
#include "../Engine/Graphics/Colors.h"

using namespace std;
using namespace TFC::Math;
using namespace TFC::Engine::Graphics;
using namespace TFC::Engine::Physics;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

bool SceneManager::Initialize()
{
    return true;
}

void SceneManager::Update()
{
    map<int, RigidBody>::iterator rbIter;
    for (rbIter = _players.begin(); rbIter != _players.end(); rbIter++)
    {
        rbIter->second.Update();
    }
    for (rbIter = _rigidbodies.begin(); rbIter != _rigidbodies.end(); rbIter++)
    {
        rbIter->second.Update();
    }
    
    map<int, Sprite>::iterator sIter;
    for (sIter = _sprites.begin(); sIter != _sprites.end(); sIter++)
    {
        sIter->second.Update();
    }

    DoCollisionDetection();
}

void SceneManager::Render()
{
    map<int, RigidBody>::iterator rbIter;
    for (rbIter = _rigidbodies.begin(); rbIter != _rigidbodies.end(); rbIter++)
    {
        rbIter->second.Render();
    }

    map<int, Sprite>::iterator sIter;
    for (sIter = _sprites.begin(); sIter != _sprites.end(); sIter++)
    {
        sIter->second.Render();
    }

    // Players last to ensure they are drawn on top
    for (rbIter = _players.begin(); rbIter != _players.end(); rbIter++)
    {
        rbIter->second.Render();
    }

}

int SceneManager::CreatePlayer(string file, Vector3<float> pos)
{
    RigidBody player = RigidBody(file, pos);
    _players[_players.size()] = player;
    return _players.size() - 1;
}

int SceneManager::CreateRigidBody(string file, Vector3<float> pos)
{
    RigidBody rigidbody = RigidBody(file, pos);
    _rigidbodies[_rigidbodies.size()] = rigidbody;
    return _rigidbodies.size() - 1;
}

int SceneManager::CreateSprite(string file, Vector3<float> pos)
{
    Sprite sprite = Sprite(file, pos);
    _sprites[_sprites.size()] = sprite;
    return _sprites.size() - 1;
}

RigidBody& SceneManager::GetPlayer(int index)
{
    return _players[index];
}

RigidBody& SceneManager::GetRigidBody(int index)
{
    return _rigidbodies[index];
}

Sprite& SceneManager::GetSprite(int index)
{
    return _sprites[index];
}

int SceneManager::PlayerCount()
{
    return _players.size();
}

int SceneManager::RigidBodyCount()
{
    return _rigidbodies.size();
}

int SceneManager::SpriteCount()
{
    return _sprites.size();
}

// PRIVATE
//

void SceneManager::DoCollisionDetection()
{
    map<int, RigidBody>::iterator player;
    map<int, RigidBody>::iterator rigidbody;
    map<int, Sprite>::iterator sprite;

    for (player = _players.begin(); player != _players.end(); player++)
    {
        player->second.SetBoundingBoxColor(COLOR_WHITE);
    }
    for (rigidbody = _rigidbodies.begin(); rigidbody != _rigidbodies.end(); rigidbody++)
    {
        rigidbody->second.SetBoundingBoxColor(COLOR_WHITE);
    }
    for (sprite = _sprites.begin(); sprite != _sprites.end(); sprite++)
    {
        sprite->second.SetBoundingBoxColor(COLOR_WHITE);
    }

    // Check each player for collisions with rigid bodies and sprites
    //
    for (player = _players.begin(); player != _players.end(); player++)
    {
        for (rigidbody = _rigidbodies.begin(); rigidbody != _rigidbodies.end(); rigidbody++)
        {
            if (player->second.GetBoundingBox().CollidesWith(rigidbody->second.GetBoundingBox()))
            {
                rigidbody->second.SetBoundingBoxColor(COLOR_RED);
                player->second.SetBoundingBoxColor(COLOR_RED);
            }
        }
        for (sprite = _sprites.begin(); sprite != _sprites.end(); sprite++)
        {
            if (player->second.GetBoundingBox().CollidesWith(sprite->second.GetBoundingBox()))
            {
                sprite->second.SetBoundingBoxColor(COLOR_RED);
                player->second.SetBoundingBoxColor(COLOR_RED);
            }
        }
    }
}