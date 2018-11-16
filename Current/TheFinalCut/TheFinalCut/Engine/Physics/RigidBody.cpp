#include "RigidBody.h"
#include "../Engine.h"
#include <iostream>

using namespace std;
using namespace TFC::Engine::Graphics;
using namespace TFC::Engine::Physics;
using namespace TFC::Math;

RigidBody::RigidBody()
{
    Initialize();
}

RigidBody::RigidBody(std::string imagePath) : Sprite(imagePath)
{
    Initialize();
}

RigidBody::RigidBody(std::string imagePath, Vector3<float>& pos) : Sprite(imagePath, pos)
{
    Initialize();
}

void RigidBody::Initialize()
{
    _gravity = 0.0;
    _friction = 1.0;
    _velocity = Vector3<float>(0.0);
}

RigidBody::~RigidBody()
{
}

// Graphics
void RigidBody::Update()
{
    Sprite::Update();

    _boundingBox._position += (_velocity * Engine::GetDeltaTime());

    _velocity.x *= _friction;
    _velocity.y -= _gravity;

    if (_boundingBox._position.y < 0.0)
    {
        _boundingBox._position.y = 0.0;
        _velocity = 0.0;
    }

    RotateTo((45.f / 750.f) * _velocity.y);
}

void RigidBody::Render()
{
    Sprite::Render();
}

// Properties
void RigidBody::SetGravity(float gravity)
{
    _gravity = gravity;
}

void RigidBody::SetFriction(float friction)
{
    _friction = friction;
}

void RigidBody::AddForce(Vector3<float> force)
{
    _velocity += force;
}
    