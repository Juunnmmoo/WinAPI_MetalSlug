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
	BG1,
	BG2,
	BG3,
	BG4,
	front,
	EnemyR,
	Enemy,
	EnemyCreator,
	Slave,
	Player,
	BulletBox,
	EnemyBulletR,
	EnemyBullet,
	DropWeapon,
	PlayerKnife,
	PlayerPistol,
	PlayerMachinegun,
	PlayerShotgun,
	PlayerFiregun,
	PlayerBomb,
	Effect,
	UI,
	End,
};

enum class eSfxType {
	PlayerBulletGroundSFX,
	PlayerBombSFX,
	PlayerBulletEnemySFX,
	NomalExplosionM,
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
	Bomb,
};

enum class eBulletType {
	None,
	Bullet,
	knife,
	Bomb,
};

