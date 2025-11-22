#pragma once
#include "BossModuleBase.h"
class BossController;
class BossIdleModule :
    public BossModuleBase
{
public:
	BossIdleModule(BossController* controller);
	~BossIdleModule();

public:
	virtual void EnterModule() override;
	virtual void UpdateModule()override;
	virtual void ExitModule()  override;

private:
	float m_cooldownTimer;
	float m_cooldown;

	int m_minCooldown;
	int m_maxCooldown;
};

