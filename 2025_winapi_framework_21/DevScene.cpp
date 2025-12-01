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
void DevScene::Init()
{
	FireBoss* boss = new FireBoss();
	boss->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 });
	boss->SetSize({ 5.f, 5.f });
	boss->SetCanOutofBounds(false);
	AddObject(boss, Layer::ENEMY);

	Player* player = new Player();
	player->SetPos({ WINDOW_WIDTH / 2, 550 });
	player->SetSize({ 1.25f, 1.25f });
	AddObject(player, Layer::PLAYER);

	SpriteObject* bg = new SpriteObject(L"background1", Layer::BACKGROUND, false);
	bg->SetSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
	bg->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
	Spawn<Floor>(Layer::DEFAULT, { WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50 }, { 2000.f, 100.f });

	SpriteObject* floor = new SpriteObject(L"floor", Layer::BACKGROUND, false);
	floor->SetSize({ WINDOW_WIDTH, 100 });
	floor->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50 });

	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYERPROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ENEMYPROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
	GET_SINGLE(PlayerFindManager)->SetPlayer(player);

	//GET_SINGLE(ResourceManager)->Play(L"BGM");
}

void DevScene::Update()
{
	Scene::Update();

}

