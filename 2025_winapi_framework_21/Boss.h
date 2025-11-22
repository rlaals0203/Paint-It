#pragma once
#include "Object.h"
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
    void SetAnimation(wstring animationKey);
    void StopAnimation();
public:
    void AddModule(BossPattern* addedPattern);
protected:
    BossController* m_Controller;
    Animator* m_Animator;
};

 