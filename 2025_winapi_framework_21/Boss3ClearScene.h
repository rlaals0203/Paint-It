#pragma once
#include "Scene.h"
class UIPanel;
class Boss3ClearScene :
    public Scene
{
public:
	void Init() override;
private:
	void OverText();
	void NextGameBtn();
private:
	UIPanel* m_mainPanel;
};

