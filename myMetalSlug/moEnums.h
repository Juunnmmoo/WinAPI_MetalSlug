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
	Test,
	Effect,
	UI,
	End,
};

enum class eComponentType
{
	Transform,
	Collider,
	SpriteRenderer,
	Animator,
	Audio,
	End,
};