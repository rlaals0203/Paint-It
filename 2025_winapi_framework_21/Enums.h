#pragma once
enum class Layer
{
	BACKGROUND,
	DEFAULT,
	PLAYER,
	ENEMY,
	PLAYERPROJECTILE,
	ENEMYOBSTACLE,
	OIL,
	EFFECT,
	UI,
	END
};

enum class PenType
{
	RED, GREEN, DANGER1, DANGER2, LIGHTRED, LAZER, END
};

enum class BrushType
{
	HOLLOW, RED, GREEN, LIGHTRED, LAZER, END
};

enum class FontType
{
	UI, TITLE, END
};

enum class PlayMode { Once, Loop, Counted };