#include "pch.h"
#include "DevScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "Floor.h"
#include "FireBoss.h"
#include "PlayerFindManager.h"
#include "SpriteObject.h"
#include "UIPanel.h"
#include "UIBossHP.h"
#include "EntityHealth.h"
#include "HealPackSpawner.h"
#include "GameSaveManager.h"


void Stage1::Init()
{

	GET_SINGLE(GameSaveManager)->SetStage(1);
	m_mainPanel = new UIPanel();
	m_mainPanel->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
	AddObject(m_mainPanel, Layer::UI);

	UIBossHP* bossHP = m_mainPanel->AddUIElement<UIBossHP>();
	bossHP->SetText(L"보스 [유화]");
	bossHP->SetPos({ WINDOW_WIDTH / 2 , 35 });
	bossHP->SetSize({ WINDOW_WIDTH / 2 , 30 });

	FireBoss* boss = new FireBoss();
	boss->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 });
	boss->SetSize({ 5.f, 5.f });
	boss->SetCanOutofBounds(false);
	AddObject(boss, Layer::ENEMY);

	bossHP->SetHealthCompo(boss->GetComponent<EntityHealth>());

	Player* player = new Player();
	player->SetPos({ WINDOW_WIDTH / 2, 550 });
	player->SetSize({ 1.25f, 1.25f });
	AddObject(player, Layer::PLAYER);

	SpriteObject* bg = new SpriteObject(L"background1", Layer::BACKGROUND, false);
	bg->SetSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
	bg->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
	Spawn<Floor>(Layer::PLATFORM, { WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50 }, { 2000.f, 100.f });

	SpriteObject* floor = new SpriteObject(L"floor", Layer::BACKGROUND, false);
	floor->SetSize({ WINDOW_WIDTH, 100 });
	floor->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50 });

	//auto* healpack = new HealPackSpawner();
	//GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(healpack, Layer::HEALPACK);

	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYERPROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ENEMYOBSTACLE);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::OIL);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::GROUNDCHECKER, Layer::PLATFORM);

	GET_SINGLE(PlayerFindManager)->SetPlayer(player);
	
	//GET_SINGLE(ResourceManager)->Play(L"BGM");
}

void Stage1::Update()
{
	Scene::Update();

}

