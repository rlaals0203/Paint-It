#pragma once
#include "Object.h"
#include "Texture.h"
class SpriteObject :
    public Object
{
public:
    SpriteObject(std::wstring _texture, Layer _layer);
    ~SpriteObject();

    void Render(HDC _hdc);
private:
    Texture* m_texture;
};

