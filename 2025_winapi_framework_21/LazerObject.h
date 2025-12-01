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
    void ShowLine(float _duration, bool _isHori, bool _isPositive, bool hasAnim = false);
    void HideLine();
    void SetLine(bool hasAnim);
    void ShowDangerGizmo();
private:
    DOTweenCompo* m_dotweenCompo;
    Vec2 m_pos;
    Vec2 m_target;
    bool m_isHori;
    bool m_isDelay;
    bool m_isPosi;
    bool m_hasAnim;
    float m_delay;
    float m_duration;
};

