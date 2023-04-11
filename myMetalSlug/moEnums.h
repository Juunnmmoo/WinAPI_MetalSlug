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
	Enemy,
	EnemyCreator,
	Player,
	EnemyBulletR,
	EnemyBullet,
	DropWeapon,
	PlayerKnife,
	PlayerPistol,
	PlayerMachinegun,
	PlayerBomb,
	Effect,
	UI,
	End,
};

enum class eComponentType
{
	Transform,
	SpriteRenderer,
	Animator,
	Rigidbody,
	Collider,
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

enum class eBulletType {
	None,
	Bullet,
	knife,
	Bomb,
};