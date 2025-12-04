#pragma once
#include "BossPattern.h"
#include "LaserObject.h"
#include  <queue>

class ReflectLazerPattern :
    public BossPattern
{
public:
    ReflectLazerPattern(BossController* _controller, int _count);
    ~ReflectLazerPattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
private:
    void SetReflect(float _angle, Vec2 _dir);
private:
    std::queue<LaserObject*> m_lasers;
    int m_count;
    int m_originCount;
    float m_time;
    float m_duration = 0.1f;
    float m_deleteTime;

    float m_prevAngle;
    bool m_isFirst;
    Vec2 m_prevPos;
};

