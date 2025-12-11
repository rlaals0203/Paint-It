#pragma once
enum class Layer
{
	BACKGROUND,
	DEFAULT,
	BACKDAMAGEABLE,
	PLAYER,
	PLATFORM,
	HEALPACK,
	GROUNDCHECKER,
	ENEMYOBSTACLE,
	GIZMO,
	ENEMY,
	PLAYERPROJECTILE,
	OIL,
	EFFECT,
	SHIELD,
	UI,
	LOADINGSCREEN,
	END
};

enum class PenType
{
	RED, 
	GREEN, 
	DANGER1, 
	DANGER2, 
	LIGHTRED, 
	LAZER, 
	LAZER2,
	BLACK,
	YELLOW,
	BLUE,
	WHITE,
	END
};

enum class BrushType
{
	HOLLOW, 
	RED, 
	GREEN, 
	LIGHTRED, 
	LAZER, 
	LAZER2, 
	BLACK,
	YELLOW,
	BLUE,
	WHITE,
	END
};

enum class FontType
{
	UI, TITLE, END
};

enum class PlayMode { Once, Loop, Counted };