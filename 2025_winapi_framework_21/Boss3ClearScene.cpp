#include "pch.h"
#include "Boss3ClearScene.h"
#include "UIPanel.h"
#include "UIText.h"
#include "UIButton.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Texture.h"

void Boss3ClearScene::Init()
{
	m_mainPanel = new UIPanel();

	m_mainPanel->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });

	AddObject(m_mainPanel, Layer::UI);

	OverText();
	NextGameBtn();
}

void Boss3ClearScene::OverText()
{
	UIText* title = m_mainPanel->AddUIElement<UIText>();

	title->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3 });
	title->SetText(L"게임 클리어");
	title->SetSize({ 300, 150 });
}

void Boss3ClearScene::NextGameBtn()
{
	UIButton* start = m_mainPanel->AddUIElement<UIButton>();
	start->SetPos({ WINDOW_WIDTH / 2, 500 });
	start->SetText(L"타이틀로");
	start->SetCallback([=]()
		{
			GET_SINGLE(SceneManager)->LoadScene(L"Title");
		});
	start->SetSize({ 160, 64 });

	Texture* button = GET_SINGLE(ResourceManager)
		->GetTexture(L"button");

	Texture* buttonHover = GET_SINGLE(ResourceManager)
		->GetTexture(L"buttonhover");

	start->SetAllTexture(button, buttonHover, nullptr);
}