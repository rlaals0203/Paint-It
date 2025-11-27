#pragma once
#include "Scene.h"

class UIPanel;
class GameOverScene :
    public Scene
{
public:
	void Init() override;
private:
	void OverText();
	void ReGameBtn();
	void ExitBtn();
private:
	UIPanel* m_mainPanel;
};

