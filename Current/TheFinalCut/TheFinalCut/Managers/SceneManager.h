#ifndef __SCENEMANAGER__H__
#define __SCENEMANAGER__H__

#include <string>
#include <map>
#include "../Engine/Engine.h"

class SceneManager
{
public:
    SceneManager();
    ~SceneManager();

    bool Initialize();

    void Update();
    void Render();

    int CreatePlayer(std::string file, TFC::Math::Vector3<float> pos);
    int CreateRigidBody(std::string file, TFC::Math::Vector3<float> pos);
    int CreateSprite(std::string file, TFC::Math::Vector3<float> pos);

    TFC::Engine::Physics::RigidBody & GetPlayer(int index);
    TFC::Engine::Physics::RigidBody & GetRigidBody(int index);
    TFC::Engine::Graphics::Sprite & GetSprite(int index);

    int PlayerCount();
    int RigidBodyCount();
    int SpriteCount();

private:
    std::map<int, TFC::Engine::Physics::RigidBody> _players;
    std::map<int, TFC::Engine::Physics::RigidBody> _rigidbodies;
    std::map<int, TFC::Engine::Graphics::Sprite> _sprites;

    void DoCollisionDetection();
};

#endif  // __SCENEMANAGER__H__