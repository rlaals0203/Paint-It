#include "pch.h"
#include "PrismObject.h"

PrismObject::PrismObject(Vec2 _pos, std::wstring _texture, 
	Layer _layer, PrismBoss* _boss)
	: SpriteObject(_texture, _layer) {
	m_boss = _boss;
	m_healthCompo = AddComponent<EntityHealth>();
	m_healthCompo->SetDefaultHP(500);
	SetPos(_pos);
}

PrismObject::~PrismObject()
{
}

void PrismObject::Update()
{
	if (m_healthCompo->GetCurrentHp() <= 0) {
		m_boss->RemovePrism();
	}
}

void PrismObject::Render(HDC _hdc)
{
	SpriteObject::Render(_hdc);
}
