#ifndef __SPRITEMANAGER__H__
#define __SPRITEMANAGER__H__

#include <string>
#include "Graphics/Sprite.h"

class SpriteManager
{
public:
    SpriteManager();
    ~SpriteManager();

    int AddSprite(std::string filePath, TFC::Math::Vector3<float> pos);
    TFC::Graphics::Sprite& GetSprite(int index);
    int Count();

    void Update();
    void Render();

private:
    std::vector<TFC::Graphics::Sprite> _sprites;

};

#endif  // __SPRITEMANAGER__H__
