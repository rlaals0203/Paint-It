#pragma once
#include "UIElement.h"
#include "Texture.h"
class UIImage :
    public UIElement
{
public:
	UIImage();
	virtual ~UIImage();

public:
	virtual void Render(HDC _hdc) override;

public:
	void SetPos(Vec2 pos) override;
	void SetSize(Vec2 size) override;

public:
	void SetImage(Texture* image);

private:
	Texture* m_image;

	Vec2 m_pos;

	LONG m_width ;
	LONG m_height;
};

