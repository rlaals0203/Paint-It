#pragma once
#include "Object.h"

class Texture;
class BlockObject :
    public Object
{
public:
    BlockObject(float destroyTime, float bombTime, float blink, float damageTime, Vec2 _bombSize);
    ~BlockObject();
public:
    void Update() override;
    void Render(HDC hdc) override;

public:
    void SetDamage(int damage) { m_damage = damage; }

private:
    float m_timer;
    float m_bombTimer;

    float m_damageTime;

    float m_blinkTime;
    float m_blinkTimer;

    bool m_isBomb = false;
    bool m_isBombEnd = false;

    int m_damage = 0;

    int m_nowTexture = 0;

    Vec2 m_bombSize;

    std::vector<Texture*> m_textures;

    Texture* m_bomb;
};

