#pragma once
#include "Scene.h"

class UIPanel;
class TitleScene : public Scene
{
public:
	void Init() override;
	void Update() override;
private:
	void Title();
	void Start();
	void Setting();
	void Exit();
	void SettingSlider();
private:
	UIPanel* m_mainPanel;
};

