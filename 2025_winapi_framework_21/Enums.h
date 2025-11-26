#pragma once
enum class Layer
{
	DEFAULT,
	BACKGROUND,
	PLAYER,
	ENEMY,
	PLAYERPROJECTILE,
	ENEMYPROJECTILE,
	EFFECT,
	END
};

enum class PenType
{
	RED, GREEN, DANGER1, DANGER2, LINE, LAZER, END
};

enum class BrushType
{
	HOLLOW, RED, GREEN, LINE, LAZER, END
};

enum class FontType
{
	UI, TITLE, END
};

enum class PlayMode { Once, Loop, Counted };