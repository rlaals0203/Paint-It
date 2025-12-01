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
	void SetImage(wstring imageName);

private:
	Texture* m_image;

	LONG m_width ;
	LONG m_height;
};

