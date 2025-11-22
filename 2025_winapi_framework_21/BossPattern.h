#pragma once
class BossController;
class BossPattern
{

public:
	BossPattern(BossController* _controller);
	virtual ~BossPattern();

public:
	virtual void Update() abstract;

public:
	bool IsUsed()  { return m_isUsed; }

public:
	virtual void SetUsed() { m_isUsed = true; }

protected:
	BossController* m_Controller;
	bool m_isUsed;

};

