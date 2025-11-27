#pragma once
#include "Object.h"
#include "DOTweenCompo.h"

class LazerObject :
    public Object
{
public:
    LazerObject();
    ~LazerObject();

    virtual void Update() override;
    virtual void Render(HDC _hdc) override;
    void ShowLine(float _duration, bool _isHori, bool _isPositive);
    void HideLine();
private:
    DOTweenCompo* m_dotweenCompo;
    Vec2 m_pos;
    Vec2 m_target;
    bool m_isHori;
    bool m_isDelay;
    float m_delay;
    float m_duration;
};

