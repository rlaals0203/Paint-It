#include "pch.h"
#include "TitleScene.h"
#include "InputManager.h"
#include "SceneManager.h"

void TitleScene::Init()
{
}

void TitleScene::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::SPACE))
	{
		GET_SINGLE(SceneManager)->LoadScene(L"DevScene");
	}
}
