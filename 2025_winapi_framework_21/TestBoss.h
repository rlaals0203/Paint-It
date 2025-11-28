#pragma once
#include "Boss.h"
#include "Animator.h"
class TestBoss :
    public Boss
{
public:
    TestBoss();
    ~TestBoss();
    void Update() override;
    void Render(HDC _hdc) override;
private:
    Texture* m_texture;
};

