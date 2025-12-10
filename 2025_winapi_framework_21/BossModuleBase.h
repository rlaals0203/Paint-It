#pragma once
class Animator;
class Rigidbody;
class BossController;
class BossModuleBase
{
public:
	BossModuleBase(BossController* _controller);
	virtual ~BossModuleBase();

public:
	virtual void EnterModule();
	virtual void UpdateModule();
	virtual void ExitModule();

public:
	bool GetActive() { return m_Active; }
protected:
	bool m_Active;
protected:
	BossController* m_Controller;
};

