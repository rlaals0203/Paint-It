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
#include "TestBoss.h"
#include "PlayerFindManager.h"
void DevScene::Init()
{
	TestBoss* boss = new TestBoss();
	boss->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 });
	boss->SetSize({ 100, 100 });
	AddObject(boss, Layer::ENEMY);

	Player* player = new Player();
	player->SetPos({ WINDOW_WIDTH / 2, 550 });
	player->SetSize({ 1.25f, 1.25f });
	AddObject(player, Layer::PLAYER);

	Spawn<Floor>(Layer::DEFAULT, { WINDOW_WIDTH / 2, 600 }, { 100,100 });
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

