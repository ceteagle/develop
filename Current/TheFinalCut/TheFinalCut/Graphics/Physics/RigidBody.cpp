#include "RigidBody.h"
#include "../Engine.h"
#include <iostream>

using namespace std;
using namespace TFC::Graphics;
using namespace TFC::Graphics::Physics;

RigidBody::RigidBody()
{
    Initialize();
}

RigidBody::RigidBody(std::string imagePath) : Sprite(imagePath)
{
    Initialize();
}

RigidBody::RigidBody(std::string imagePath, TFC::Math::Vector3<float>& pos) : Sprite(imagePath, pos)
{
    Initialize();
}

void TFC::Graphics::Physics::RigidBody::Initialize()
{
    _gravity = 0.0;
    _friction = 1.0;
    _velocity = TFC::Math::Vector3<float>(0.0);
}

RigidBody::~RigidBody()
{
}

bool RigidBody::Initialize(float gravity, float friction)
{
    _gravity = gravity;
    _friction = friction;
    return true;
}

void RigidBody::Update()
{
    Sprite::Update();

    _position += (_velocity * Engine::GetDeltaTime());

    _velocity.x *= _friction;
    _velocity.y -= _gravity;

    if (_position.y < 0.0)
    {
        _position.y = 0.0;
        _velocity = 0.0;
    }

    RotateTo((45. / 750.) * _velocity.y);

#ifdef _DEBUG
    //cout << "Rigid Body Position " << _position.x << " " << _position.y << " " << _position.z << " velocity = " << _velocity.x << " " << _velocity.y << endl;
#endif
}

void RigidBody::Render(TFC::Math::Vector3<float> color)
{
    Sprite::Render();
}

void RigidBody::AddForce(TFC::Math::Vector3<float> force)
{
    _velocity += force;
}
