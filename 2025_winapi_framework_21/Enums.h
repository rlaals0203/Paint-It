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
	UI,
	END
};

enum class PenType
{
	RED, GREEN, DANGER1, DANGER2, END
};

enum class BrushType
{
	HOLLOW, RED, GREEN, END
};

enum class FontType
{
	UI, TITLE, END
};

enum class PlayMode { Once, Loop, Counted };