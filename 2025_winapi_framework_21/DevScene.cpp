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
void DevScene::Init()
{
	TestBoss* boss = new TestBoss();
	boss->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 });
	boss->SetSize({ 100, 100 });
	AddObject(boss, Layer::ENEMY);

	Spawn<Player>(Layer::PLAYER, { WINDOW_WIDTH / 2, 550}, { 100,100 });
	Spawn<Floor>(Layer::DEFAULT, { WINDOW_WIDTH / 2, 600 }, { 100,100 });
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYERPROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ENEMYPROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
	//GET_SINGLE(ResourceManager)->Play(L"BGM");
}

void DevScene::Update()
{
	Scene::Update();

}

