#pragma once
#include "Scene.h"

class UIPanel;
class Stage1 : public Scene
{
public:
	void Init() override;
	void Update() override;

private:
	UIPanel* m_mainPanel;
};

