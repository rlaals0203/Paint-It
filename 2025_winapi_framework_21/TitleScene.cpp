#include "pch.h"
#include "TitleScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "UIPanel.h"
#include "UIText.h"
#include "UIButton.h"
#include "UISlider.h"
#include "UIImage.h"

void TitleScene::Init()
{
	panel = GET_SINGLE(ResourceManager)
		->GetTexture(L"panel");

	button = GET_SINGLE(ResourceManager)
		->GetTexture(L"button");

	buttonHover = GET_SINGLE(ResourceManager)
		->GetTexture(L"buttonhover");

	slider = GET_SINGLE(ResourceManager)
		->GetTexture(L"slider");

	sliderFill = GET_SINGLE(ResourceManager)
		->GetTexture(L"sliderfill");

	sliderHandle = GET_SINGLE(ResourceManager)
		->GetTexture(L"slidericon");


	CreatePanel();

	Title();

	SettingPanel();

	Start();
	Setting();
	Exit();

	GET_SINGLE(ResourceManager)
		->Play(L"BGM");
}

void TitleScene::Release()
{
	GET_SINGLE(ResourceManager)
		->Stop(SOUND_CHANNEL::BGM);
}

void TitleScene::CreatePanel()
{
	m_mainPanel = new UIPanel();

	m_mainPanel->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });

	AddObject(m_mainPanel, Layer::UI);

	m_settingPanel = new UIPanel();

	m_settingPanel->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });

	AddObject(m_settingPanel, Layer::UI);

	UIImage* settingImage = m_settingPanel->AddUIElement<UIImage>();

	settingImage->SetSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
	settingImage->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
	settingImage->SetImage(panel);
	
	m_settingPanel->SetActive(false);
}

void TitleScene::Title()
{
	UIImage* title = m_mainPanel->AddUIElement<UIImage>();
	
	title->SetPos({ WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 3  });
	title->SetSize({ 300, 300 });

	Texture* titleImage = GET_SINGLE(ResourceManager)->GetTexture(L"brush");

	title->SetImage(titleImage);
	Vec2 size = title->GetSize();

}

void TitleScene::Start()
{
	UIButton* start = m_mainPanel->AddUIElement<UIButton>();
	start->SetPos({ WINDOW_WIDTH / 2, 500 });
	start->SetText(L"start");
	start->SetSize({ 160, 64 });

	start->SetAllTexture(button , buttonHover, nullptr);
	start->SetCallback([=]()
		{
			GET_SINGLE(SceneManager)->LoadScene(L"Stage2");
		});
}

void TitleScene::Setting()
{
	UIButton* setting = m_mainPanel->AddUIElement<UIButton>();
	setting->SetPos({ WINDOW_WIDTH / 2, 570 });
	setting->SetText(L"setting");
	setting->SetSize({ 160, 64 });

	setting->SetAllTexture(button, buttonHover, nullptr);

	setting->SetCallback([=]()
		{
			m_mainPanel->SetActive(false);
			m_settingPanel->SetActive(true);
		});
}

void TitleScene::Exit()
{
	UIButton* exit = m_mainPanel->AddUIElement<UIButton>();
	
	exit->SetPos({ WINDOW_WIDTH / 2, 640 });

	exit->SetSize({ 160, 64	 });

	exit->SetAllTexture(button, buttonHover, nullptr);

	exit->SetText(L"exit");
	
	exit->SetCallback([=]()
		{
			::PostQuitMessage(0);
		});
}

void TitleScene::SettingPanel()
{
	//slider
	UISlider* BGMslider = m_settingPanel->AddUIElement<UISlider>();
	BGMslider->SetPos(
		{
			WINDOW_WIDTH / 2
			, WINDOW_HEIGHT / 3
		});
	BGMslider->SetTrackTexture(GET_SINGLE(ResourceManager)
		->GetTexture(L"floor"));
	BGMslider->SetThumbTexture(GET_SINGLE(ResourceManager)
		->GetTexture(L"brush"));
	BGMslider->SetFillTexture(GET_SINGLE(ResourceManager)
		->GetTexture(L"background1"));

	BGMslider->SetThunbRadius(25);

	BGMslider->SetSize({ 324, 108 });

	BGMslider->SetCallback([=](float value)
		{
			GET_SINGLE(ResourceManager)
				->Volume(SOUND_CHANNEL::BGM, value);
		}); 

	BGMslider->SetRange(0,1);
	
	BGMslider->SetValue(1);

	BGMslider->SetFillTexture(sliderFill);
	BGMslider->SetThumbTexture(sliderHandle);
	BGMslider->SetTrackTexture(slider);


	UISlider* EFFECTslider = m_settingPanel->AddUIElement<UISlider>();
	
	EFFECTslider->SetPos(
		{
			WINDOW_WIDTH / 2
			, WINDOW_HEIGHT / 2
		});

	EFFECTslider->SetSize({ 324, 108 });

	EFFECTslider->SetCallback([=](float value)
		{
			GET_SINGLE(ResourceManager)
				->Volume(SOUND_CHANNEL::EFFECT, value);
		});

	EFFECTslider->SetRange(0, 1);
	
	EFFECTslider->SetValue(1);

	EFFECTslider->SetFillTexture(sliderFill);
	EFFECTslider->SetThumbTexture(sliderHandle);
	EFFECTslider->SetTrackTexture(slider);

	EFFECTslider->SetThunbRadius(25);


	UIText* Settingtext = m_settingPanel->AddUIElement<UIText>();

	Settingtext->SetPos(
		{
			WINDOW_WIDTH / 2
			, WINDOW_HEIGHT / 5
		});

	Settingtext->SetSize({ 280,40 });

	Settingtext->SetText(L"Setting");
	Settingtext->SetTextColor(RGB(255, 255, 255));

	UIText* BGMtext = m_settingPanel->AddUIElement<UIText>();
	
	BGMtext->SetPos(
		{
			(LONG)(WINDOW_WIDTH / 3.5f)
			, WINDOW_HEIGHT / 3
		});

	BGMtext->SetSize({ 120,40 });

	BGMtext->SetText(L"BGM");
	BGMtext->SetTextColor(RGB(255, 255, 255));
	
	UIText* EFFECTText = m_settingPanel->AddUIElement<UIText>();

	EFFECTText->SetPos(
		{
			(LONG)(WINDOW_WIDTH / 3.5f)
			, WINDOW_HEIGHT / 2
		});

	EFFECTText->SetSize({ 120,40 });

	EFFECTText->SetText(L"SFX");
	EFFECTText->SetTextColor(RGB(255,255,255));

	//close Btn
	UIButton* exit = m_settingPanel->AddUIElement<UIButton>();

	exit->SetPos({ WINDOW_WIDTH - 150, 160 });

	Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"xbutton");
	exit->SetAllTexture(tex, tex, nullptr);

	exit->SetSize({ 80, 80 });

	exit->SetCallback([=]()
		{
			m_mainPanel->SetActive(true);
			m_settingPanel->SetActive(false);
		});
}
