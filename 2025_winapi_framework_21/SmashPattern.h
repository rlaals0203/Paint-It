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
    void UpState();
    void WaitState();
    void FallState();
private:
    enum class State
    {
        Up,
        Wait,
        Fall,
    };
    State m_state;
    MoveComponent* m_moveComponent;
    bool m_isPlaying;
    float m_delay;
};

