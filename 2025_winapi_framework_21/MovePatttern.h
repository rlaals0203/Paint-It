#pragma once
#include "BossPattern.h"
class Boss;
class MovePatttern :
    public BossPattern
{
public:
    MovePatttern(BossController* _controller
        , Vec2 _movePos, float _speed, float _stopDistance);
    ~MovePatttern();

public:
    virtual void Update() override;
    virtual void SetUsed() override;
protected:
    Boss* m_boss;
    
    Vec2  m_startPos;
    Vec2  m_movePos;

    Vec2  m_moveDir;
    
    float m_speed;
    float m_stopDistance;
};