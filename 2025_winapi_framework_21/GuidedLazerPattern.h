#pragma once
#include "BossPattern.h"
#include "LazerObject.h"
#include "Player.h"
#include <stack>
class GuidedLazerPattern :
    public BossPattern
{
public:
    GuidedLazerPattern(BossController* _controller, int _count, float _duration);
    ~GuidedLazerPattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
private:
    Player* m_target;
    int m_count;
    float m_duration;
    float m_time;
    float m_deleteTime;
    std::stack<LazerObject*> m_lazers;
};

