#pragma once
#include"Object.h"

class DamageText : public Object
{
public:
    DamageText();
    ~DamageText();
public:
    void Init(int dmg, Vec2 pos);
    void Update() override;
    void Render(HDC _hdc) override;
private:
    int m_damage;
    float m_lifeTime;
    float m_speed;
};

