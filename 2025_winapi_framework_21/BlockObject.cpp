#include "pch.h"
#include "BlockObject.h"
#include "Collider.h"
#include "Texture.h"
#include "BombObject.h"
#include "SceneManager.h"
#include "Scene.h"

BlockObject::BlockObject(float destroyTime, float bombTime, float blink,float damageTime , Vec2 _bombSize)
	:m_timer(destroyTime)
	, m_bombSize(_bombSize)
	, m_bombTimer(bombTime)
	, m_blinkTimer(blink)
	, m_blinkTime(0)
	, m_damageTime(damageTime)
	, m_bomb(nullptr)
{
	//텍스처 가져오기
	auto* col = AddComponent<Collider>();
	col->SetName(L"Wall");
	col->SetTrigger(false);
}

BlockObject::~BlockObject()
{
}

void BlockObject::Update()
{
	if (m_timer > 0)
	{
		m_timer -= fDT;
	}
	else if (m_bombTimer > 0)
	{
		m_bombTimer -= fDT;
		m_blinkTimer -= fDT;
		if (m_blinkTimer <= 0)
		{
			m_blinkTimer = m_blinkTime;
			m_nowTexture = (m_nowTexture + 1) % 2;
		}
	}
	else
	{
		BombObject* bomb = new BombObject(m_damage, m_damageTime);
		bomb->SetPos(GetPos());
		bomb->SetSize(m_bombSize);
		bomb->SetTexture(m_bomb);
		bomb->SetDamage(m_damage);
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bomb, Layer::ENEMYOBSTACLE);
		SetDead();
	}
}

void BlockObject::Render(HDC hdc)
{
	if (!m_isBomb)
	{
		Texture* tex = m_textures[m_nowTexture];

		LONG width = tex->GetWidth();
		LONG height = tex->GetHeight();

		Vec2 pos = GetPos();
		Vec2 size = GetSize();

		::TransparentBlt(hdc
			, pos.x
			, pos.y
			, size.x
			, size.y
			, tex->GetTextureDC(),
			0, 0, width, height, RGB(255, 0, 255));
	}
}
