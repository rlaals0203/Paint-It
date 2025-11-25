#pragma once
#include "BossPattern.h"
#include "MoveComponent.h"
class SmashPattern :
    public BossPattern
{
public:
    SmashPattern(BossController* _controller);
    ~SmashPattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
private:
    MoveComponent* m_moveComponent;
    bool m_isPlaying;
    bool m_isPhase1;
    bool m_isPhase2;
    float m_phase1;
    float m_phase2;
};

