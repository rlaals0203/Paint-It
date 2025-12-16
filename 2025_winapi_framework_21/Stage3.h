#pragma once
#include "Scene.h"
class UIPanel;
class Stage3 :
    public Scene
{
public:
	Stage3();
	~Stage3();
public:
	void Init() override;
	void Update() override;
private:
	UIPanel* m_mainPanel;
};

