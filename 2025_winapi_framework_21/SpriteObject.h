#pragma once
#include "Object.h"
#include "Texture.h"
class SpriteObject :
    public Object
{
public:
    SpriteObject(std::wstring _texture, Layer _layer, bool _isTrans = true);
    ~SpriteObject();

    void Render(HDC _hdc);
private:
    Texture* m_texture;
    bool _isTrans;
};

