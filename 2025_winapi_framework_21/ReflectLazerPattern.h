#pragma once
#include "BaseLazerPattern.h"
#include "LaserObject.h"

class ReflectLazerPattern :
    public BaseLazerPattern
{
public:
    ReflectLazerPattern(BossController* _controller, int _count, bool _isAwaken = false, float _delay = 0.1f, float _deleteTime = 0.5f);
    ~ReflectLazerPattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
private:
    float m_startDeleteTime;
    float m_prevAngle;
    bool m_isFirst;
    Vec2 m_prevPos;
};

