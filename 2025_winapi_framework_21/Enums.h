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
	RED, GREEN, DANGER, END
};

enum class BrushType
{
	HOLLOW, RED, GREEN, DANGER, END
};

enum class FontType
{
	UI, TITLE, END
};

enum class PlayMode { Once, Loop, Counted };