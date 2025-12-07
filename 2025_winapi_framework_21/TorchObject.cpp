#include "pch.h"
#include "TorchObject.h"
#include "ImpulseManager.h"
#include "ProjectileManager.h"
#include "BossController.h"
#include "EntityHealth.h"
#include "DOTweenCompo.h"
#include "ResourceManager.h"

TorchObject::TorchObject(int _count, Vec2 _pos, float _offset)
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

	auto* healthCompo = new EntityHealth();
	healthCompo->SetDefaultHP(100);
	healthCompo->SubscribeHealthThreshold([this]() {HandleDead(); }, 0.f);

	DOTweenCompo* dotweenCompo = AddComponent<DOTweenCompo>();
	dotweenCompo->DOLocalMoveY(200.f, 1.f);
}

TorchObject::~TorchObject()
{
	m_time -= fDT;
	if (m_time <= 0.f) {
		m_time = m_delay;
		FireProjectile();
	}
}

void TorchObject::HandleDead()
{
	SetDead();
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
