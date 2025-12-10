#include "pch.h"
#include "DotBombPattern.h"
#include "BlockObject.h"
#include "SceneManager.h"


DotBombPattern::DotBombPattern(BossController* _controller, int count)
	: BossPattern(_controller)
	, m_baseCount(count)
	, m_count(count)
	, m_spawnTime(0.15f)
	, m_timer(0.15f)
	, m_destroyTime(3.5f)
	, m_bombTime(1.f)
	, m_blinkTime(0.1f)
	, m_damageTime(0.5f)
	, m_dotSize({50,50})
	, m_bombSize({100,100})
	, m_damage(5)
{

}

DotBombPattern::~DotBombPattern()
{
}

void DotBombPattern::Update()
{
	m_timer -= fDT;
	if (m_timer <= 0)
	{
		for (int i = 0; i < m_count; ++i)
		{
			MakeDot();
		}
		m_isUsed = false;

	}
}

void DotBombPattern::SetUsed()
{
	m_count = m_baseCount;
	m_timer = m_spawnTime;
	BossPattern::SetUsed();
}

void DotBombPattern::MakeDot()
{
	BlockObject* block = new BlockObject(m_destroyTime,m_bombTime, m_blinkTime, m_damageTime, m_bombSize);

	block->SetDamage(m_damage);
	block->SetSize(m_dotSize);

	POINT spawn;
	spawn.x = (rand() % WINDOW_WIDTH);
	spawn.y = (rand() % WINDOW_HEIGHT);

	Vec2 point = spawn;

	block->SetPos(point);

	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(block, Layer::ENEMYOBSTACLE);
}
