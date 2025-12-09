#include "pch.h"
#include "ColorObject.h"

ColorObject::ColorObject(PenType _penType, BrushType _brushType)
{
	m_penType = _penType;
	m_brushType = _brushType;
}

ColorObject::~ColorObject()
{

}

void ColorObject::Render(HDC _hdc)
{
	GDISelector pen(_hdc, m_penType);
	GDISelector brush(_hdc, m_brushType);
	Object::Render(_hdc);
}
