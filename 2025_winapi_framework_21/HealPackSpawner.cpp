#include "pch.h"
#include "HealPackSpawner.h"

HealPackSpawner::HealPackSpawner() : m_delay(21.5f)
{
	m_currentTime = m_delay;
}

HealPackSpawner::~HealPackSpawner()
{
}

void HealPackSpawner::Update()
{
	m_currentTime -= fDT;
	if (m_currentTime <= 0.f) {
		m_currentTime = m_delay;
		SpawnHealPack();
	}
}

void HealPackSpawner::SpawnHealPack()
{
	Vec2 pos = {
		Random::Range(0, WINDOW_WIDTH),
		Random::Range(425, 600) };
	auto* healpack = new HealPack(L"healpack", Layer::HEALPACK);
	healpack->SetPos(pos);
}
