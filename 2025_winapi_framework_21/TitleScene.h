#pragma once
#include "Scene.h"
class Texture;
class UIPanel;
class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();
public:
	void Init() override;
	void Release() override;
private:
	void CreatePanel();
	void Title();
	void Start();
	void Setting();
	void Exit();
	void SettingPanel();
private:
	Texture* panel;
	Texture* button;
	Texture* buttonHover;

	Texture* slider;
	Texture* sliderHandle;
	Texture* sliderFill;

	UIPanel* m_mainPanel;
	UIPanel* m_settingPanel;
};

