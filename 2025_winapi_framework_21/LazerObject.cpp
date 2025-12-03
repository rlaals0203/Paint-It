#include "pch.h"
#include "LazerObject.h"
#include "Ease.h"
#include "SceneManager.h"
#include "ImpulseManager.h"
#include "DangerGizmo.h"
#include "RotateRender.h"
#include "EntityHealth.h"
#include "DamageText.h"

LazerObject::LazerObject() : m_pos({}), m_isDelay(true), m_length(2000.f)
{
	m_dotweenCompo = AddComponent<DOTweenCompo>();
	m_collider = AddComponent<Collider>();
}

LazerObject::~LazerObject()
{
}

void LazerObject::Update()
{
	m_delay -= fDT;
	m_collider->SetSize(GetSize());

	if (m_delay <= 0.f && m_isDelay)
	{
		m_dotweenCompo->DOScaleX(m_length, m_duration, EaseInExpo);

		m_isDelay = false;
		GET_SINGLE(ImpulseManager)->ApplyImpulse(10.f, 0.5f);
	}
}

void LazerObject::Render(HDC _hdc)
{
	GDISelector pen(_hdc, PenType::LAZER);
	GDISelector brush(_hdc, BrushType::LAZER);
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	float halfLen = size.x * 0.5f;
	Vec2 renderOffset = m_dir * halfLen;
	pos = pos + renderOffset;
	RotateRender::RotateRectRender(_hdc, pos, size, m_angle);
	ComponentRender(_hdc);
}

void LazerObject::ShowLine(Vec2 _start, float _angle, float _duration)
{
	m_angle = _angle;
	m_pos = _start;
	m_delay = 1.f;
	m_duration = _duration;

	SetRotation(m_angle);
	SetLine();
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, Layer::ENEMYPROJECTILE);
}

void LazerObject::SetLine()
{
	Vec2 dir = { cosf(m_angle * PI / 180.f), sinf(m_angle * PI / 180.f) };
	m_dir = dir;
	m_dir.Normalize();
	SetSize({ 0.f, 15.f });
	float halfLen = GetSize().x * 0.5f;

	Vec2 rotOffset = {
	rotOffset.x = halfLen * m_dir.x,
	rotOffset.y = halfLen * m_dir.y };
	SetPos(m_pos + rotOffset);

	m_collider->SetOffSetPos(rotOffset);
	m_collider->SetRotation(m_angle);

	Vec2 finalSize = { m_length, 15.f };  // 최종 크기
	float finalHalfLen = finalSize.x * 0.5f;
	Vec2 finalRotOffset = {
		finalRotOffset.x = finalHalfLen * m_dir.x,
		finalRotOffset.y = finalHalfLen * m_dir.y
	};
	Vec2 finalPos = m_pos + finalRotOffset;  // 최종 위치

	ShowDangerGizmo(finalPos, finalSize);
}

void LazerObject::HideLine()
{
	if (!m_dotweenCompo)
		m_dotweenCompo = AddComponent<DOTweenCompo>();

	m_dotweenCompo->DOScaleY(0.f, 0.2f, EaseInBack, [this]() {SetDead(); });
}

void LazerObject::ShowDangerGizmo(Vec2 finalPos, Vec2 finalSize)
{
	auto* dangerGizmo = new DangerGizmo();
	dangerGizmo->SetDangerGizmo(finalPos, finalSize, m_angle, 1.f);
}
