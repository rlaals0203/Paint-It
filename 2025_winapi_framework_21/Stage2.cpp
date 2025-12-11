#include "pch.h"
#include "Stage2.h"
#include "PrismBoss.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "Floor.h"
#include "PlayerFindManager.h"
#include "SpriteObject.h"
#include "UIPanel.h"
#include "UIBossHP.h"
#include "EntityHealth.h"
#include "ColorObject.h"
#include "GameSaveManager.h"

void Stage2::Init()
{
	GET_SINGLE(GameSaveManager)->SetStage(2);
	ColorObject* obj1 = new ColorObject(PenType::BLACK, BrushType::BLACK);
	ColorObject* obj2 = new ColorObject(PenType::BLACK, BrushType::BLACK);

	obj1->SetSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
	obj1->SetPos({WINDOW_WIDTH / 2, 0});
	obj2->SetSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
	obj2->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT });

	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(obj1, Layer::LOADINGSCREEN);
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(obj2, Layer::LOADINGSCREEN);

	auto* tween1 = obj1->AddComponent<DOTweenCompo>();
	auto* tween2 = obj2->AddComponent<DOTweenCompo>();

	tween1->DOMoveY(-WINDOW_HEIGHT / 2, 3.f, EaseOutCubic);
	tween2->DOMoveY(WINDOW_HEIGHT * 1.5f, 3.f, EaseOutCubic, [=]()
		{
			GET_SINGLE(SceneManager)->RequestDestroy(obj1);
			GET_SINGLE(SceneManager)->RequestDestroy(obj2);
		});
		
	m_mainPanel = new UIPanel();
	m_mainPanel->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
	AddObject(m_mainPanel, Layer::UI);

	UIBossHP* bossHP = m_mainPanel->AddUIElement<UIBossHP>();
	bossHP->SetText(L"보스 [프리즘]");
	bossHP->SetPos({ WINDOW_WIDTH / 2 , 35 });
	bossHP->SetSize({ WINDOW_WIDTH / 2 , 30 });

	PrismBoss* boss = new PrismBoss();
	boss->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 });
	boss->SetSize({ 5.f, 5.f });
	boss->SetCanOutofBounds(false);
	AddObject(boss, Layer::ENEMY);
	bossHP->SetHealthCompo(boss->GetComponent<EntityHealth>());

	Player* player = new Player();
	player->SetPos({ WINDOW_WIDTH / 2, 550 });
	player->SetSize({ 1.25f, 1.25f });
	AddObject(player, Layer::PLAYER);

	SpriteObject* bg = new SpriteObject(L"bluebackground", Layer::BACKGROUND, false);
	bg->SetSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
	bg->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
	Spawn<Floor>(Layer::PLATFORM, { WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50 }, { 2000.f, 100.f });

	SpriteObject* floor = new SpriteObject(L"floor2", Layer::BACKGROUND, false);
	floor->SetSize({ WINDOW_WIDTH, 100 });
	floor->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50 });

	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYERPROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYERPROJECTILE, Layer::SHIELD);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ENEMYOBSTACLE);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::OIL);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::BACKDAMAGEABLE);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::GROUNDCHECKER, Layer::PLATFORM);
	GET_SINGLE(PlayerFindManager)->SetPlayer(player);
}

void Stage2::Update()
{
	Scene::Update();
}
