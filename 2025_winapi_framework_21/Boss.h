#pragma once
#include "Object.h"
#include "MovePattern.h"

class BossController;
class BossPattern;
class Animator;
class Boss :
    public Object
{
public:
    Boss();
    ~Boss();

    void Update() override;
public:
    void MoveTransPos(Vec2 _delta)
    {
        Translate(_delta);
    }
public:
    void SetAnimation(wstring animationKey);
    void StopAnimation();
    void BossReset();
    void AddModule(BossPattern* addedPattern);
    void AddMoveModule(MovePattern* addedPattern);
    void ClearModule();
protected:
    void GoStage(int stage);
    void GoTitle();
protected:
    BossController* m_controller;
    Animator* m_animator;

    bool m_isBlinking;
    std::wstring m_animName;
    std::wstring m_blinkName;
};

 