#include "pch.h"
#include "LaserObject.h"
#include "Ease.h"
#include "SceneManager.h"
#include "ImpulseManager.h"
#include "DangerGizmo.h"
#include "RotateRender.h"
#include "EntityHealth.h"
#include "DamageText.h"

LaserObject::LaserObject() : m_pos({}), m_isDelay(true), m_length(2000.f), m_delay(1.f), m_width(15.f)
{
	m_dotweenCompo = AddComponent<DOTweenCompo>();
	m_collider = AddComponent<Collider>();
}

LaserObject::~LaserObject()
{
}

void LaserObject::Update()
{
	m_delay -= fDT;
	m_collider->SetSize(GetSize());

	if (m_delay <= 0.f && m_isDelay)
	{
		m_dotweenCompo->DOScaleX(m_length, m_duration, EaseInExpo);

		m_isDelay = false;
		GET_SINGLE(ImpulseManager)->ApplyImpulse(8.f, 0.5f);
	}
}

void LaserObject::Render(HDC _hdc)
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

void LaserObject::EnterCollision(Collider* _other)
{
	auto* health = _other->GetOwner()->GetComponent<EntityHealth>();
	health->ApplyDamage(10.f);
}

void LaserObject::InitLaser(Vec2 _start, float _angle, float _duration, float _delay)
{
	m_angle = _angle;
	m_pos = _start;
	m_duration = _duration;
	m_delay = _delay;

	SetRotation(m_angle);
	SetLine();
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, Layer::ENEMYOBSTACLE);
}

void LaserObject::SetLine()
{
	m_dir = Vec2(cosf(m_angle * PI / 180.f), sinf(m_angle * PI / 180.f));
	m_dir.Normalize();
	SetPos(m_pos);

	SetSize({ 0.f, m_width });

	float halfLen = GetSize().x * 0.5f;
	Vec2 offset = m_dir * halfLen;

	m_collider->SetOffSetPos(offset);
	m_collider->SetRotation(m_angle);

	Vec2 finalSize = { m_length, m_width };
	Vec2 finalOffset = m_dir * (finalSize.x * 0.5f);
	Vec2 finalPos = m_pos + finalOffset;
	ShowDangerGizmo(finalPos, finalSize);

	Vec2 pos = GetLaserHitPoint();
}

void LaserObject::HideLine()
{
	if (!m_dotweenCompo)
		m_dotweenCompo = AddComponent<DOTweenCompo>();

	m_collider->SetActive(false);
	m_dotweenCompo->DOScaleY(0.f, 0.2f, EaseInBack, [this]() {SetDead(); });
}

void LaserObject::ShowDangerGizmo(Vec2 finalPos, Vec2 finalSize)
{
	auto* dangerGizmo = new DangerGizmo();
	dangerGizmo->SetDangerGizmo(finalPos, finalSize, m_angle, m_delay);
}

Vec2 LaserObject::GetLaserHitPoint()
{
	Vec2 start = GetPos();
	Vec2 dir = m_dir;

	float tx, ty;

	if (dir.x > 0)
		tx = (WINDOW_WIDTH - start.x) / dir.x;
	else
		tx = (0 - start.x) / dir.x;

	if (dir.y > 0)
		ty = (WINDOW_HEIGHT - start.y) / dir.y;
	else
		ty = (0 - start.y) / dir.y;

	float t = (tx < ty) ? tx : ty;
	return start + dir * t;
}
