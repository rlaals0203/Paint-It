#pragma once
#include "BossPattern.h"
#include "BossController.h"
#include "DOTweenCompo.h"

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
    void GroundState();
    Vec2 GetOwnerPos() { return m_Controller->GetOwner()->GetPos(); }
private:
    enum class State
    {
        Up,
        Wait,
        Fall,
        Ground
    };
    State m_state;
    DOTweenCompo* m_dotween;
    bool m_isPlaying;
    float m_delay;
    int m_count;
};