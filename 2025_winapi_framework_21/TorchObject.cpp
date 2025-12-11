#include "pch.h"
#include "TorchObject.h"
#include "ImpulseManager.h"
#include "ProjectileManager.h"
#include "BossController.h"
#include "EntityHealth.h"
#include "DOTweenCompo.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Collider.h"

TorchObject::TorchObject(int _count, Vec2 _pos, float _offset) :
	m_isDead(false)
{
	m_pos = _pos;
	m_count = _count;
	m_time = _offset;
	m_delay = 3.f;
	m_animName = L"torch";

	auto* texture = GET_SINGLE(ResourceManager)->GetTexture(L"torch");
	m_animator = AddComponent<Animator>();
	m_animator->CreateAnimation(m_animName, texture,
		{ 0.f, 0.f }, { 32.f, 32.f },
		{ 32.f, 0.f }, 10, 0.1f);

	m_animator->Play(m_animName);

	SetSize({ 4, 6 });
	SetPos(m_pos);
	m_dotweenCompo = AddComponent<DOTweenCompo>();
	m_dotweenCompo->DOLocalMoveY(150.f, 1.f, EaseOutBack);
	m_pos.y += 170.f;

	AddComponent<Collider>();
}

TorchObject::~TorchObject()
{
}

void TorchObject::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void TorchObject::Update()
{
	m_time -= fDT;
	m_lifeTime -= fDT;
	if (m_time <= 0.f) {
		m_time = m_delay;
		FireProjectile();
	}

	if (m_lifeTime <= 0.f && m_isDead == false) {
		HandleDead();
	}
}

void TorchObject::HandleDead()
{
	m_isDead = true;
	m_dotweenCompo->DOLocalMoveY(-150.f, 0.5f, EaseInBack, [this]() 
		{ 
			SetDead(); 
			GET_SINGLE(SceneManager)->RequestDestroy(this);
		});
}

void TorchObject::FireProjectile()
{
	float angle = 360.f / (float)m_count;
	for (int i = 0; i < m_count; i++) {
		GET_SINGLE(ProjectileManager)->SpawnProjectile(
			Enemy, 60.f, m_pos,
			angle * i, 10.f);
	}

	GET_SINGLE(ImpulseManager)->ApplyImpulse(20.f, 0.4f);
}
