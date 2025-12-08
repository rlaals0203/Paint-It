#pragma once
#include "SpriteObject.h"
#include "Player.h"

class OilObject :
    public SpriteObject
{
public:
    OilObject(std::wstring _texture, Layer _layer);
    ~OilObject();

    void Render(HDC _hdc) override;
    void Update() override;
    void EnterCollision(Collider* _other);

private:
    float m_lifeTime;
    Texture* m_textures[];
};

