#pragma once
#include "Object.h"
#include "MoveComponent.h"
#include "ScaleComponent.h"
class LineObject :
    public Object
{
public:
    LineObject();
    ~LineObject();

    virtual void Render(HDC _hdc);
    void SetLine(float _duration, bool _isHori, bool _isPositive);
    void KillLine();
private:
    MoveComponent* m_moveCompo;
    ScaleComponent* m_scaleCompo;
    Vec2 m_pos;
    Vec2 m_target;
    bool m_isHori;
};

