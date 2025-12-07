#pragma once
#include"Object.h"

class DamageText : public Object
{
public:
    DamageText();
    ~DamageText();
public:
    void Init(wstring dmg, Vec2 pos);
    void Update() override;
    void Render(HDC _hdc) override;
private:
    wstring m_text;
    float m_lifeTime;
    float m_speed;
};

