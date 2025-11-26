#pragma once
#include "Object.h"
#include "MoveComponent.h"
class LineObject :
    public Object
{
public:
    LineObject();
    ~LineObject();

    virtual void Render(HDC _hdc);
    void SetLine(float _duration, bool _isHori, bool _isPositive);
private:
    MoveComponent* m_moveCompo;
    Vec2 m_pos;
    Vec2 m_target;
};

