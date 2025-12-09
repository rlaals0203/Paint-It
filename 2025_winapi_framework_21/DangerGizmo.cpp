#include "pch.h"
#include "DangerGizmo.h"
#include "SceneManager.h"
#include "RotateRender.h"
#include "ResourceManager.h"

DangerGizmo::DangerGizmo() : m_isPlaying(false), m_angle(0.f)
{
	m_texture1 = GET_SINGLE(ResourceManager)->GetTexture(L"dangermark1");
	m_texture2 = GET_SINGLE(ResourceManager)->GetTexture(L"dangermark2");
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
			return;
	}

	m_lifeTime -= fDT;
	m_colorTime -= fDT;

	if (m_lifeTime <= 0.f)
	{
		m_isPlaying = false;
		GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(this);
	}

	if (m_colorTime <= 0.f)
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

	Vec2 size = GetSize();
	if (size.x > 50 && size.y > 50) {
		Vec2 pos = GetPos();
		auto* tex = m_isRed ? m_texture1 : m_texture2;

		::TransparentBlt(
			_hdc, pos.x, pos.y, size.x, size.y,
			tex->GetTextureDC(), 0, 0,
			30, 30, RGB(255, 0, 255));
	}
	

	RotateRender::RotateRectRender(_hdc, GetPos(), GetSize(), m_angle);
}

void DangerGizmo::SetDangerGizmo(Vec2 _pos, Vec2 _size, float _angle, float _duration, float _delay)
{
	SetPos(_pos);
	SetSize(_size);
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, Layer::GIZMO);

	m_isDelay = _delay > 0.f;
	m_isPlaying = !m_isDelay;
	m_delay = _delay;
	m_angle = _angle;
	m_pos = _pos;
	m_size = _size;
	m_lifeTime = _duration;
}
