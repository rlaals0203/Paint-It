#pragma once
#include "Scene.h"

class UIPanel;
class Stage1 : public Scene
{
public:
	Stage1();
	~Stage1();
public:
	void Init() override;
	void Update() override;

private:
	UIPanel* m_mainPanel;
};

