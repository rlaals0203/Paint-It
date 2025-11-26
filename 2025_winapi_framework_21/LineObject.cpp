#include "pch.h"
#include "LineObject.h"
#include "Ease.h"
#include "SceneManager.h"

LineObject::LineObject() : m_pos({})
{
}

LineObject::~LineObject()
{
}

void LineObject::Render(HDC _hdc)
{
	GDISelector pen(_hdc, PenType::LINE);
	GDISelector brush(_hdc, BrushType::LINE);
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);
}

void LineObject::SetLine(float _duration, 
	bool _isHori, bool _isPositive)
{
	if (_isHori) {
		m_pos.y = (rand() % WINDOW_HEIGHT * 0.7f);
		m_pos.x = _isPositive ? 0 - WINDOW_WIDTH / 2 : WINDOW_WIDTH * 2.f;
		m_target = { 0.f, m_pos.y };
		SetSize({ (float)WINDOW_WIDTH * 2, 15.f });
	}
	else {
		m_pos.x = (rand() % WINDOW_WIDTH * 0.7f);
		m_pos.y = _isPositive ? 0 - WINDOW_HEIGHT / 2 : WINDOW_HEIGHT * 2.f;
		m_target = { m_pos.x, 0.f };
		SetSize({ 15.f, (float)WINDOW_HEIGHT * 2 });
	}

	SetPos(m_pos);
	m_moveCompo = AddComponent<MoveComponent>();
	m_moveCompo->SetMove(m_pos, m_target, _duration, EaseInExpo);
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, Layer::EFFECT);
}
