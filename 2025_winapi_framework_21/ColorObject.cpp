#include "pch.h"
#include "ColorObject.h"
#include "PlayerFindManager.h"
#include "Collider.h"

ColorObject::ColorObject(PenType _penType, BrushType _brushType)
	: m_dealTime(0.1f)
{
	m_penType = _penType;
	m_brushType = _brushType;
	m_player = GET_SINGLE(PlayerFindManager)->GetPlayer();
	auto* col = AddComponent<Collider>();
	col->SetSize(GetSize());
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

void ColorObject::EnterCollision(Collider* _other)
{
	if (m_player == nullptr) return;

	if (m_penType == PenType::BLUE)
		m_player->SetOiledTime(10.f);
	else if (m_penType == PenType::YELLOW)
		m_player->SetDamageMult(1.5f);
}

void ColorObject::StayCollision(Collider* _other)
{
	if (m_player == nullptr) return;

	m_dealTime -= fDT;
	if (m_dealTime <= 0.f) {
		m_dealTime = 0.1f;
		m_player->ApplyDamage(1);
	}
}

void ColorObject::ExitCollision(Collider* _other)
{
	if (m_player == nullptr) return;

	if (m_penType == PenType::BLUE)
		m_player->SetOiledTime(0.f);
	else if (m_penType == PenType::YELLOW)
		m_player->SetDamageMult(1.f);
}
