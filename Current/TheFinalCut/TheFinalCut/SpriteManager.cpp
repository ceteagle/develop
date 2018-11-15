#include "SpriteManager.h"



SpriteManager::SpriteManager()
{
}


SpriteManager::~SpriteManager()
{
}

int SpriteManager::AddSprite(std::string filePath, TFC::Math::Vector3<float> pos)
{

    TFC::Graphics::Sprite sprite = TFC::Graphics::Sprite(filePath, pos);
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

TFC::Graphics::Sprite& SpriteManager::GetSprite(int index)
{
    return _sprites[index];
}

int SpriteManager::Count()
{
    return _sprites.size();
}
