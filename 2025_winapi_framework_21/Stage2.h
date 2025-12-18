#pragma once
#include "Scene.h"
class UIPanel;
class Stage2 :
    public Scene
{
public:
	Stage2();
	~Stage2();
public:
	void Init() override;
	void Update() override;
private:
	UIPanel* m_mainPanel;
};

