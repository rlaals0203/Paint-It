#pragma once
#include "Object.h"
class Animator;
class Texture;
class OriginPoint :
    public Object
{
public:
    OriginPoint(float aniTime,float endTime , float waitTime);
    ~OriginPoint();

public:
    virtual void Update() override;
    virtual void Render(HDC _hdc) override;

private:
    Animator* m_animator;
    Texture* m_pointTex;

    wstring m_originName;
    //wstring m_originEndName;

    float m_waitTime;
    float m_aniTime;
    float m_endTime;
};

