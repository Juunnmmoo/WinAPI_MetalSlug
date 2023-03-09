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
	Monster,
	Player,
	Bullet,
	Test,
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
	Audio,
	End,
};

enum class eDirection
{
	LTop,
	RTop,
	Top,
	LBottom,
	RBottom,
	Left,
	Right,
	End,
};