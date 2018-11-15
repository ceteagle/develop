#include "SpriteManager.h"

using namespace TFC::Engine::Graphics;
using namespace TFC::Math;

using namespace std;

SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
}

void SpriteManager::Update()
{
    vector<Sprite>::iterator iter;
    for (iter = _sprites.begin(); iter != _sprites.end(); iter++)
    {
        iter->Update();
    }
}

void SpriteManager::Render()
{
    vector<Sprite>::iterator iter;
    for (iter = _sprites.begin(); iter != _sprites.end(); iter++)
    {
        iter->Render();
    }
}

int SpriteManager::AddSprite(std::string filePath, Vector3<float> pos)
{
    Sprite sprite = Sprite(filePath, pos);
    _sprites.push_back(sprite);
    return _sprites.size()-1;
}

Sprite& SpriteManager::GetSprite(int index)
{
    return _sprites[index];
}

int SpriteManager::Count()
{
    return _sprites.size();
}
