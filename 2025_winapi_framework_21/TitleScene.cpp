#include "pch.h"
#include "TitleScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIPanel.h"
#include "UIText.h"
#include "UIButton.h"
#include "UISlider.h"

void TitleScene::Init()
{
	m_mainPanel = new UIPanel();

	m_mainPanel->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });

	AddObject(m_mainPanel, Layer::UI);

	Title();

	SettingSlider();

	Start();
	Exit();
}

void TitleScene::Update()
{
	Scene::Update();
	/*if (GET_KEYDOWN(KEY_TYPE::P))
	{
		GET_SINGLE(SceneManager)->LoadScene(L"DevScene");
	}*/
}

void TitleScene::Title()
{
	UIText* title = m_mainPanel->AddUIElement<UIText>();
	
	title->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3 });
	title->SetText(L"대충 타이틀");
	title->SetSize({ 300, 150 });
}

void TitleScene::Start()
{
	UIButton* start = m_mainPanel->AddUIElement<UIButton>();
	start->SetPos({ WINDOW_WIDTH / 2, 500 });
	start->SetText(L"시작");
	start->SetSize({ 100, 50 });
	start->SetCallback([=]()
		{
			GET_SINGLE(SceneManager)->LoadScene(L"DevScene");
		});

}

void TitleScene::Setting()
{
}

void TitleScene::Exit()
{
	UIButton* exit = m_mainPanel->AddUIElement<UIButton>();
	
	exit->SetPos({ WINDOW_WIDTH / 2, 600 });

	exit->SetSize({ 100, 50 });

	exit->SetText(L"나가다");
	
	exit->SetCallback([=]()
		{
			::PostQuitMessage(0);
		});
}

void TitleScene::SettingSlider()
{
	UISlider* uislider = m_mainPanel->AddUIElement<UISlider>();

}
