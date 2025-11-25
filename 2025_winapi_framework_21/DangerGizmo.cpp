#include "pch.h"
#include "DangerGizmo.h"
#include "SceneManager.h"

DangerGizmo::DangerGizmo()
{
}

DangerGizmo::~DangerGizmo()
{
}

void DangerGizmo::Update()
{
	m_lifeTime -= fDT;
	if (m_lifeTime < 0.f)
	{
		m_isPlaying = false;
		SetDead();
	}
}

void DangerGizmo::Render(HDC _hdc)
{
	GDISelector pen(_hdc, PenType::DANGER);
	GDISelector brush(_hdc, BrushType::HOLLOW);
	RECT_RENDER(_hdc, m_pos.x, m_pos.y, m_size.x, m_size.y);
}

void DangerGizmo::SetDangerGizmo(Vec2 _pos, Vec2 _size, float _duration)
{
	SetPos(_pos);
	SetSize(_size);
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, Layer::EFFECT);

	m_pos = _pos;
	m_size = _size;
	m_lifeTime = _duration;
	m_isPlaying = true;
}
