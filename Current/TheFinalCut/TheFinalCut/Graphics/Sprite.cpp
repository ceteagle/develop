#include "Sprite.h"
#include "Engine.h"

using namespace TFC::Math;

TFC::Graphics::Sprite::Sprite() :
    _rotation(0.0), _speed(100.0)
{
    _pos = Vector3<float>(0.0);
    _scale = Vector3<float>(1.0);

    _texture = Texture();
}

TFC::Graphics::Sprite::Sprite(std::string imagePath) : Sprite()
{
    _texture = Texture(imagePath);
}

TFC::Graphics::Sprite::Sprite(std::string imagePath, TFC::Math::Vector3<float>& pos) : Sprite(imagePath)
{
    _pos = pos;
}

TFC::Graphics::Sprite::~Sprite()
{
}

void TFC::Graphics::Sprite::Update()
{

}

void TFC::Graphics::Sprite::Render()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture.GetID());
    glLoadIdentity();

    // Translate -> Rotate -> Scale
    //
    glTranslatef(_pos.x, _pos.y, _pos.z);
    glRotatef(_rotation, 0.0, 0.0, 1.0);
    glScalef(_scale.x, _scale.y, _scale.z);

    // Render
    //
    glColor4f(1, 1, 1, 1);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.0, 0.0);    glVertex2f(0.0, 0.0);
        glTexCoord2f(1.0, 0.0);    glVertex2f(_texture.GetWidth(), 0.0);
        glTexCoord2f(1.0, 1.0);    glVertex2f(_texture.GetWidth(), _texture.GetHeight());
        glTexCoord2f(0.0, 1.0);    glVertex2f(0.0, _texture.GetHeight());
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void TFC::Graphics::Sprite::SpeedTo(float speed)
{
    _speed = speed;
}

void TFC::Graphics::Sprite::SpeedBy(float speed)
{
    _speed += speed;
}

void TFC::Graphics::Sprite::MoveTo(Vector3<float>& v)
{
    _pos = v;
}

void TFC::Graphics::Sprite::MoveBy(Vector3<float>& v)
{
    _pos += Vector3<float>(v*Engine::GetDeltaTime());
}

void TFC::Graphics::Sprite::RotateTo(float rotation)
{
    _rotation = rotation;
}

void TFC::Graphics::Sprite::RotateBy(float rotation)
{
    _rotation += (rotation*Engine::GetDeltaTime());
}

void TFC::Graphics::Sprite::SetScale(float x)
{
    _scale = x;
}

void TFC::Graphics::Sprite::SetScale(Vector3<float>& v)
{
    _scale = v;
}

void TFC::Graphics::Sprite::MoveLeft()
{
    _pos.x -= (_speed * Engine::GetDeltaTime());
}

void TFC::Graphics::Sprite::MoveRight()
{
    _pos.x += (_speed* Engine::GetDeltaTime());
}

void TFC::Graphics::Sprite::MoveUp()
{
    _pos.y += (_speed * Engine::GetDeltaTime());
}

void TFC::Graphics::Sprite::MoveDown()
{
    _pos.y -= (_speed * Engine::GetDeltaTime());
}
