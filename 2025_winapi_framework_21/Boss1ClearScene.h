#pragma once
#include "Scene.h"
class UIPanel;
class Boss1ClearScene :
    public Scene
{
public:
	Boss1ClearScene();
	~Boss1ClearScene();
public:
	void Init() override;
private:
	void OverText();
	void NextGameBtn();
private:
	UIPanel* m_mainPanel;
};

