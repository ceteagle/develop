#include "RigidBody.h"
#include "../Engine.h"

using namespace TFC::Graphics;
using namespace TFC::Graphics::Physics;

RigidBody::RigidBody()
{
    _gravity = 0.0;
    _friction = 1.0;
}

RigidBody::~RigidBody()
{
}

bool RigidBody::Initialize(float gravity, float friction, Sprite & sprite)
{
    _gravity = gravity;
    _friction = friction;
    _sprite = &sprite;
    return true;
}

void RigidBody::Update()
{
    _sprite->Update();

    _sprite->_pos += (_velocity * Engine::GetDeltaTime());

    _velocity.x *= _friction;
    _velocity.y -= _gravity;

    if (_sprite->_pos.y < 0.0)
    {
        _sprite->_pos.y = 0.0;
        _velocity = 0.0;
    }
}

void RigidBody::Render(TFC::Math::Vector3<float> color)
{
    _sprite->Render();

    glLoadIdentity();
    glTranslatef(_sprite->_pos.x, _sprite->_pos.y, _sprite->_pos.z);
    glRotatef(_sprite->_rotation, 0, 0, 1);
    glScalef(_sprite->_scale.x, _sprite->_scale.y, _sprite->_scale.z);

    glColor4f(color.x, color.y, color.z, 1);

    glBegin(GL_LINE_LOOP);
    {
        glVertex2i(0, 0);
        glVertex2i(_sprite->_texture.GetWidth(), 0);
        glVertex2i(_sprite->_texture.GetWidth(), _sprite->_texture.GetHeight());
        glVertex2i(0, _sprite->_texture.GetHeight());
    }
    glEnd();
}

void RigidBody::AddForce(TFC::Math::Vector3<float> force)
{
    _velocity += force;
}
