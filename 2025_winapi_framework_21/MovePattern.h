#pragma once
#include "BossPattern.h"
#include "DOTweenCompo.h"
class Boss;
class MovePattern :
    public BossPattern
{
public:
    MovePattern(BossController* _controller
        , Vec2 _movePos, float _speed, float _stopDistance);
    ~MovePattern();

public:
    virtual void Update() override;
    virtual void SetUsed() override;
protected:
    Boss* m_boss;
    DOTweenCompo* m_dotween;
    Vec2  m_startPos;
    Vec2  m_movePos;
    float m_speed;
    float m_t = 0;
    float m_duration = 1.0f;
    Vec2 m_originPos;
};