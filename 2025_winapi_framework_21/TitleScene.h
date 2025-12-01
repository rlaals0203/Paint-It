#pragma once
#include "Scene.h"

class UIPanel;
class TitleScene : public Scene
{
public:
	void Init() override;
	void Update() override;
	void Release() override;
private:
	void CreatePanel();
	void Title();
	void Start();
	void Setting();
	void Exit();
	void SettingPanel();
private:
	UIPanel* m_mainPanel;
	UIPanel* m_settingPanel;
};

