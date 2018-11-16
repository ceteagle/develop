#include "Sprite.h"
#include "../Engine.h"

using namespace TFC::Math;
using namespace TFC::Engine::Graphics;

Sprite::Sprite() :
    _rotation(0.0), _speed(100.0)
{
    _scale = Vector3<float>(1.0);
    _texture = Texture();
}

Sprite::Sprite(std::string imagePath) : Sprite()
{
    _texture = Texture(imagePath);
    _boundingBox.SetSize(GetSize());
}

Sprite::Sprite(std::string imagePath, Vector3<float>& pos) : Sprite(imagePath)
{
    _boundingBox._position = pos;
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
    _boundingBox.Update();
    _boundingBox.Rotate(_rotation);
}

void Sprite::Render()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture.GetID());
    glLoadIdentity();

    // Translate -> Rotate -> Scale
    //
    glTranslatef(_boundingBox._position.x, _boundingBox._position.y, _boundingBox._position.z);
    glRotatef(_rotation, 0.0, 0.0, 1.0);
    glScalef(_scale.x, _scale.y, _scale.z);

    // Render
    //
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.0f, 0.0f);    glVertex2f(-(float)_texture.GetWidth() * .5f, -(float)_texture.GetHeight() * .5f);
        glTexCoord2f(1.0f, 0.0f);    glVertex2f( (float)_texture.GetWidth() * .5f, -(float)_texture.GetHeight() * .5f);
        glTexCoord2f(1.0f, 1.0f);    glVertex2f( (float)_texture.GetWidth() * .5f,  (float)_texture.GetHeight() * .5f);
        glTexCoord2f(0.0f, 1.0f);    glVertex2f(-(float)_texture.GetWidth() * .5f,  (float)_texture.GetHeight() * .5f);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);

    _boundingBox.Render();
}

void Sprite::SpeedTo(float speed)
{
    _speed = speed;
}

void Sprite::SpeedBy(float speed)
{
    _speed += speed;
}

void Sprite::MoveTo(Vector3<float> v)
{
    _boundingBox._position = v;
}

void Sprite::MoveBy(Vector3<float> v)
{
    _boundingBox._position += Vector3<float>(v*Engine::GetDeltaTime());
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
    _scale = Vector3<float>(x, x, 0.0f);
    _boundingBox.SetScale(x*1.1f);
}

void Sprite::SetScale(Vector3<float> v)
{
    _scale = v;
    _boundingBox.SetScale(v);
}

void Sprite::MoveLeft()
{
    _boundingBox._position.x -= (_speed * Engine::GetDeltaTime());
}

void Sprite::MoveRight()
{
    _boundingBox._position.x += (_speed* Engine::GetDeltaTime());
}

void Sprite::MoveUp()
{
    _boundingBox._position.y += (_speed * Engine::GetDeltaTime());
}

void Sprite::MoveDown()
{
    _boundingBox._position.y -= (_speed * Engine::GetDeltaTime());
}

Vector3<float> Sprite::GetSize()
{
    return Vector3<float>((float)_texture.GetWidth(), (float)_texture.GetHeight(), 0.0f);
}

void Sprite::SetBoundingBoxColor(Vector3<float>& color)
{
    _boundingBox._color = color;
}

Rectangle & Sprite::GetBoundingBox()
{
    return _boundingBox;
}
