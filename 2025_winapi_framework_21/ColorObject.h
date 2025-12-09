#pragma once
#include "Object.h"
class ColorObject :
    public Object
{
public:
    ColorObject(PenType _penType, BrushType _brushType);
    ~ColorObject();

    void Render(HDC _hdc) override;
private:
    PenType m_penType;
    BrushType m_brushType;
};

