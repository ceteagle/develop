#include "SpriteManager.h"

using namespace TFC::Engine::Graphics;

SpriteManager::SpriteManager()
{
}


SpriteManager::~SpriteManager()
{
}

int SpriteManager::AddSprite(std::string filePath, TFC::Math::Vector3<float> pos)
{

    Sprite sprite = Sprite(filePath, pos);
    _sprites.push_back(sprite);
    return _sprites.size()-1;
}

void SpriteManager::Update()
{
    for (size_t i = 0; i < _sprites.size(); i++)
    {
        _sprites[i].Update();
    }
}

void SpriteManager::Render()
{
    for (size_t i = 0; i < _sprites.size(); i++)
    {
        _sprites[i].Render();
    }
}

Sprite& SpriteManager::GetSprite(int index)
{
    return _sprites[index];
}

int SpriteManager::Count()
{
    return _sprites.size();
}
