#pragma once
class GameSaveManager
{
	DECLARE_SINGLE(GameSaveManager);
public:
	int GetStage() { return m_nowStage; }
	void SetStage(int stage) { m_nowStage = stage; }
private:
	int m_nowStage = 1;
};

