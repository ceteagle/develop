#include "Sprite.h"
#include "Engine.h"

using namespace TFC::Math;
using namespace TFC::Graphics;

Sprite::Sprite() :
    _rotation(0.0), _speed(100.0)
{
    _scale = Vector3<float>(1.0);
    _color = Vector3<float>(1.0);
    _texture = Texture();
}

Sprite::Sprite(std::string imagePath) : Sprite()
{
    _texture = Texture(imagePath);
    Rectangle::SetSize(GetSize());
}

Sprite::Sprite(std::string imagePath, TFC::Math::Vector3<float>& pos) : Sprite(imagePath)
{
    _position = pos;
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
    Rectangle::UpdateVertices();
    Rectangle::Rotate(_rotation);
}

void Sprite::Render()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture.GetID());
    glLoadIdentity();

    // Translate -> Rotate -> Scale
    //
    glTranslatef(_position.x, _position.y, _position.z);
    glRotatef(_rotation, 0.0, 0.0, 1.0);
    glScalef(_scale.x, _scale.y, _scale.z);

    // Render
    //
    glColor4f(1, 1, 1, 1);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.0, 0.0);    glVertex2f(-(float)_texture.GetWidth() * .5, -(float)_texture.GetHeight() * .5);
        glTexCoord2f(1.0, 0.0);    glVertex2f( (float)_texture.GetWidth() * .5, -(float)_texture.GetHeight() * .5);
        glTexCoord2f(1.0, 1.0);    glVertex2f( (float)_texture.GetWidth() * .5,  (float)_texture.GetHeight() * .5);
        glTexCoord2f(0.0, 1.0);    glVertex2f(-(float)_texture.GetWidth() * .5,  (float)_texture.GetHeight() * .5);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);

    Rectangle::Render(_color);
}

void Sprite::SpeedTo(float speed)
{
    _speed = speed;
}

void Sprite::SpeedBy(float speed)
{
    _speed += speed;
}

void Sprite::MoveTo(Vector3<float>& v)
{
    _position = v;
}

void Sprite::MoveBy(Vector3<float>& v)
{
    _position += Vector3<float>(v*Engine::GetDeltaTime());
}

void Sprite::RotateTo(float rotation)
{
    _rotation = rotation;
}

void Sprite::RotateBy(float rotation)
{
    _rotation += (rotation*Engine::GetDeltaTime());
}

void Sprite::SetScale(float x)
{
    _scale = Vector3<float>(x, x, 0.0);
    Rectangle::SetScale(x*1.1);
}

void Sprite::SetScale(Vector3<float>& v)
{
    _scale = v;
    Rectangle::SetScale(v);
}

void Sprite::MoveLeft()
{
    _position.x -= (_speed * Engine::GetDeltaTime());
}

void Sprite::MoveRight()
{
    _position.x += (_speed* Engine::GetDeltaTime());
}

void Sprite::MoveUp()
{
    _position.y += (_speed * Engine::GetDeltaTime());
}

void Sprite::MoveDown()
{
    _position.y -= (_speed * Engine::GetDeltaTime());
}

Vector3<float> Sprite::GetSize()
{
    return Vector3<float>(_texture.GetWidth(), _texture.GetHeight(), 0.0);
}

void TFC::Graphics::Sprite::SetBoundingBoxColor(TFC::Math::Vector3<float>& color)
{
    _color = color;
}
