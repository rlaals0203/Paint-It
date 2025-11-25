#pragma once
#include "Player.h"
class PlayerFindManager
{
	DECLARE_SINGLE(PlayerFindManager);
public:
	void SetPlayer(Player* _player) { m_player = _player; }
	Player* GetPlayer() { return m_player; }
private:
	Player* m_player;
};

