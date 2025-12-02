#pragma once
#include "Object.h"
#include "Texture.h"
class SpriteObject :
    public Object
{
public:
    SpriteObject(std::wstring _texture, Layer _layer, bool _isTrans = true);
    ~SpriteObject();

    void virtual Render(HDC _hdc);
protected:
    Texture* m_texture;
    bool m_isTrans;
};

