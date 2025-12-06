#pragma once
#include "BossPattern.h"
#include "LaserObject.h"
#include <queue>

class BaseLazerPattern :
    public BossPattern
{
public:
    BaseLazerPattern(BossController* _controller, int _count, bool _isAwaken, float _delay, float _deleteTime);
    ~BaseLazerPattern();
public:
    void Update() override;
    void SetUsed() override;
protected:
    void SetDeleteTime(float _time) { m_deleteTime = _time; }
protected:
    std::queue<LaserObject*> m_lasers;
    PenType m_penType;
    BrushType m_brushType;
    float m_remainDeleteTime;
    int m_remainCount;
    float m_remainTime;
    float m_delay;
    int m_count;
    float m_deleteTime;
private:
};

