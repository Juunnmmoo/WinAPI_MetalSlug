#pragma once


enum class eSceneType
{
	Title,
	SelectPlayer,
	Mission1,
	Mission2,
	Mission3,
	End,
	Max
};

enum class eLayerType
{
	BG,
	BulletBox,
	Monster,
	Player,
	Bullet,
	Effect,
	UI,
	End,
};

enum class eComponentType
{
	Transform,
	SpriteRenderer,
	Animator,
	Collider,
	Rigidbody,
	Audio,
	End,
};

enum class eDirection
{
	LTop,
	RTop,
	Top,
	LSit,
	RSit,
	LBottom,
	RBottom,
	Bottom,
	Left,
	Right,
	End,
};

enum class eMarcoWeapon {
	Pistol,
	Machinegun,
	Shotgun,
	Firegun,
};