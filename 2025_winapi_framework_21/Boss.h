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
public:
    void MoveTransPos(Vec2 _delta)
    {
        Translate(_delta);
    }
public:
    void SetAnimation(wstring animationKey);
    void StopAnimation();
    void ResetPattern();
    void AddModule(BossPattern* addedPattern);
    void AddMoveModule(MovePattern* addedPattern);
protected:
    BossController* m_Controller;
    Animator* m_Animator;
};

 