#pragma once
enum class Layer
{
	BACKGROUND,
	DEFAULT,
	PLAYER,
	PLATFORM,
	ENEMYOBSTACLE,
	GIZMO,
	ENEMY,
	PLAYERPROJECTILE,
	OIL,
	EFFECT,
	SHIELD,
	UI,
	END
};

enum class PenType
{
	RED, GREEN, DANGER1, DANGER2, LIGHTRED, LAZER, LAZER2, END
};

enum class BrushType
{
	HOLLOW, RED, GREEN, LIGHTRED, LAZER, LAZER2, END
};

enum class FontType
{
	UI, TITLE, END
};

enum class PlayMode { Once, Loop, Counted };