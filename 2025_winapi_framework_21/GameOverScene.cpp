#include "pch.h"
#include "GameOverScene.h"
#include "SceneManager.h"
#include "UIPanel.h"
#include "UIText.h"
#include "UIButton.h"

void GameOverScene::Init()
{
	m_mainPanel = new UIPanel();

	m_mainPanel->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });

	AddObject(m_mainPanel, Layer::UI);

	OverText();
	ReGameBtn();
	ExitBtn();
}

void GameOverScene::OverText()
{
	UIText* title = m_mainPanel->AddUIElement<UIText>();

	title->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3 });
	title->SetText(L"대충 너 죽음");
	title->SetSize({ 300, 150 });
}

void GameOverScene::ReGameBtn()
{
	UIButton* start = m_mainPanel->AddUIElement<UIButton>();
	start->SetPos({ WINDOW_WIDTH / 2, 500 });
	start->SetText(L"다시");
	start->SetSize({ 100, 50 });
	start->SetCallback([=]()
		{
			GET_SINGLE(SceneManager)->LoadScene(L"DevScene");
		});
}

void GameOverScene::ExitBtn()
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
