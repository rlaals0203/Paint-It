#include "pch.h"
#include "MakePrismPattern.h"
#include "PrismObject.h"
#include "PrismBoss.h"
#include "BossController.h"

MakePrismPattern::MakePrismPattern(BossController* _controller) : BossPattern(_controller)
{
}

MakePrismPattern::~MakePrismPattern()
{
}

void MakePrismPattern::Update()
{
}

void MakePrismPattern::SetUsed()
{
	float x = WINDOW_WIDTH * 0.05f + (rand() % (int)(WINDOW_WIDTH * 0.9f));
	float y = WINDOW_HEIGHT * 0.05f + (rand() % (int)(WINDOW_HEIGHT * 0.9f));
	PrismBoss* boss = dynamic_cast<PrismBoss*>(m_Controller->GetBoss());
	auto* prism = new PrismObject({x, y}, boss);
	boss->AddPrism(prism);
	cout << "SDf";
	m_isUsed = false;
}
