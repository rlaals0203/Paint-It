#include "pch.h"
#include "DangerGizmo.h"
#include "SceneManager.h"

DangerGizmo::DangerGizmo() : m_isPlaying(false)
{
}

DangerGizmo::~DangerGizmo()
{
}

void DangerGizmo::Update()
{
	if (m_isDelay)
	{
		m_delay -= fDT;
		if (m_delay < 0.f)
		{
			m_isDelay = false;
			m_isPlaying = true;
		}
		else
		{
			return;
		}
	}

	m_lifeTime -= fDT;
	m_colorTime -= fDT;

	if (m_lifeTime < 0.f)
	{
		m_isPlaying = false;
		GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(this);
	}

	if (m_colorTime < 0.f)
	{
		m_isRed = !m_isRed;
		m_colorTime = 0.1f;
	}
}

void DangerGizmo::Render(HDC _hdc)
{
	if (m_isPlaying == false) return;
	GDISelector pen(_hdc, m_isRed ? PenType::DANGER1 : PenType::DANGER2);
	GDISelector brush(_hdc, BrushType::HOLLOW);
	RECT_RENDER(_hdc, m_pos.x, m_pos.y, m_size.x, m_size.y);
}

void DangerGizmo::SetDangerGizmo(Vec2 _pos, Vec2 _size, float _duration, float _delay)
{
	SetPos(_pos);
	SetSize(_size);
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, Layer::EFFECT);

	m_isDelay = _delay > 0.f;
	m_delay = _delay;
	m_pos = _pos;
	m_size = _size;
	m_lifeTime = _duration;
}
