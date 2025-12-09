#pragma once
#include "Object.h"
class GroundChecker :
    public Object
{
public:
    GroundChecker();
    ~GroundChecker();

    virtual void EnterCollision(Collider* _other) override;
    virtual void ExitCollision(Collider* _other) override;
public:
    void SetIsGround(bool _isGround) { m_isGround = _isGround; }
    bool GetIsGround() { return m_isGround; }
    void SubscribeGroundChange(std::function<void(bool m_isGround)> _callback) { m_callback = _callback; }
private:
    bool m_isGround;
    std::function<void(bool m_isGround)> m_callback;
};

