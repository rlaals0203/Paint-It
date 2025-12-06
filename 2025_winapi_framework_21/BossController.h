#pragma once
#include "Component.h"
class Boss;
class Animator;
class BossModuleBase;

class BossController : public Component
{
public:
	BossController();
	~BossController();
public:
	//void SetOwner(Boss* owner) { m_owner = owner; }
	Boss* GetBoss(){ return m_boss; }
public:
	void SetBoss();
public:
	virtual void Init() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hdc) override;
public:
	BossModuleBase* GetModule(wstring _key);
	void AddModule(wstring _key, BossModuleBase* _module);
	void ChangeModule(wstring _key);
	void ClearModule();
private:
	Boss* m_boss;

	std::map<wstring, BossModuleBase*> m_ModuleMap;
	BossModuleBase* m_CurrentModule;
};

