#pragma once
#include "Object.h"
#include "Animator.h"
class Effect :
    public Object
{
public:
    Effect();
    ~Effect();
public:
private:
    Animator* m_animator;
};

