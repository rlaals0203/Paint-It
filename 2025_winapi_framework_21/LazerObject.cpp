#include "pch.h"
#include "LazerObject.h"
#include "Ease.h"
#include "SceneManager.h"
#include "ImpulseManager.h"
#include "DangerGizmo.h"

LazerObject::LazerObject() : m_pos({}), m_isDelay(true)
{
	m_dotweenCompo = AddComponent<DOTweenCompo>();
}

LazerObject::~LazerObject()
{
}

void LazerObject::Update()
{
	m_delay -= fDT;
	if (m_delay < 0.f && m_isDelay)
	{
		if (m_hasAnim == false)
		{
			if (m_isHori)
				m_dotweenCompo->DOScaleY(15.f, 0.3f, EaseOutElastic);
			else
				m_dotweenCompo->DOScaleX(15.f, 0.3f, EaseOutElastic);
		}
		else
			m_dotweenCompo->DOMove(m_target, m_duration, EaseInExpo);

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
	RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);
}

void LazerObject::ShowLine(float _duration, 
	bool _isHori, bool _isPositive, bool _hasAnim)
{
	m_isHori = _isHori;
	m_isPosi = _isPositive;
	m_hasAnim = _hasAnim;
	SetLine(_hasAnim);
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, Layer::EFFECT);

	m_delay = m_hasAnim ? 1.f : 1.15f;
	m_duration = _duration;
}

void LazerObject::HideLine()
{
	if (!m_dotweenCompo)
		m_dotweenCompo = AddComponent<DOTweenCompo>();

	if (m_isHori)
		m_dotweenCompo->DOScaleY(0.f, 0.25f, EaseInBack, [this]() {
				GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(this);
			});
	else
		m_dotweenCompo->DOScaleX(0.f, 0.25f, EaseInBack, [this]() {
				GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(this);
			});
}

void LazerObject::SetLine(bool hasAnim)
{
	if (m_isHori) {
		m_pos.y = (float)(rand() % (int)(WINDOW_HEIGHT * 0.7f));
		m_pos.x = m_isPosi ? 0 - WINDOW_WIDTH : WINDOW_WIDTH * 2.f;
		m_target = { 0.f, m_pos.y };
		SetSize({ (float)WINDOW_WIDTH * 2, 15.f });
		ShowDangerGizmo();

		if (hasAnim == false) {
			m_pos = m_target;
			SetSize({ GetSize().x, 0.f });
		}
	}
	else {
		m_pos.x = (float)(rand() % (int)(WINDOW_WIDTH * 0.7f));
		m_pos.y = m_isPosi ? 0 - WINDOW_HEIGHT : WINDOW_HEIGHT * 2.f;
		m_target = { m_pos.x, 0.f };
		SetSize({ 15.f, (float)WINDOW_HEIGHT * 2 });
		ShowDangerGizmo();

		if (hasAnim == false) {
			m_pos = m_target;
			SetSize({ 0.f, GetSize().y });
		}
	}

	SetPos(m_pos);
}

void LazerObject::ShowDangerGizmo()
{
	auto* dangerGizmo = new DangerGizmo();
	dangerGizmo->SetDangerGizmo(m_target, GetSize(), 1.f);
}
