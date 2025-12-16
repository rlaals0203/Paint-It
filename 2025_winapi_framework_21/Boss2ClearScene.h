#pragma once
#include "Scene.h"
class UIPanel;
class Boss2ClearScene :
    public Scene
{
public:
	Boss2ClearScene();
	~Boss2ClearScene();
public:
	void Init() override;
private:
	void OverText();
	void NextGameBtn();
private:
	UIPanel* m_mainPanel;
};

