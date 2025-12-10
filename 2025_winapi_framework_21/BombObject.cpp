#include "pch.h"
#include "BombObject.h"
#include "Collider.h"
#include "EntityHealth.h"
#include "DamageText.h"
#include "Texture.h"
#include "SceneManager.h"
#include "Animator.h"

BombObject::BombObject(int damage, float endtime , Texture* tex)
	: m_damage(damage)
	, m_damageTime(endtime)
	, m_bombTex(tex)
{
	Animator* ani = AddComponent<Animator>();
	ani->CreateAnimation(
		L"ani", m_bombTex,
		{ 0.f,0.f }, { 32.f, 32.f },
		{ 32.f,0.f }, 6, m_damageTime / 6
	);

	ani->Play(L"ani");

	auto* col = AddComponent<Collider>();
	col->SetSize({ 90,90 });
	col->SetTrigger(true);
}

BombObject::~BombObject()
{
}

void BombObject::Render(HDC _hdc)
{
	ComponentRender(_hdc);
	/*LONG width = m_bombTex->GetWidth();
	LONG height = m_bombTex->GetHeight();

	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	::TransparentBlt(_hdc
		, pos.x - size.x / 2
		, pos.y - size.y / 2
		, size.x
		, size.y
		, m_bombTex->GetTextureDC(),
		0, 0, width, height, RGB(255, 0, 255));*/
}

void BombObject::Update()
{
	m_damageTime -= fDT;
	if (m_damageTime < 0)
	{
		GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(this);
	}
}

void BombObject::EnterCollision(Collider* _other)
{
	if (_other->GetName() == L"Player")
	{
		auto* healthCompo = _other->GetOwner()->GetComponent<EntityHealth>();
		if (healthCompo)
		{
			healthCompo->ApplyDamage(m_damage, true);
		}
	}
}
