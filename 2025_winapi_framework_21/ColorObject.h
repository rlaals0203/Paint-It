#pragma once
#include "Object.h"
#include "Player.h"
class ColorObject :
    public Object
{
public:
    ColorObject(PenType _penType, BrushType _brushType);
    ~ColorObject();

    void Render(HDC _hdc) override;
    void EnterCollision(Collider* _other) override;
    void StayCollision(Collider* _other) override;
    void ExitCollision(Collider* _other) override;
private:
    Player* m_player;
    PenType m_penType;
    BrushType m_brushType;
    float m_dealTime;
};

