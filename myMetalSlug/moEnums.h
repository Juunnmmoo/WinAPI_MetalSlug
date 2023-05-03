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
	front,
	Slave,
	EnemyR,
	Enemy,
	EnemyR_F,
	Enemy_F,
	EnemyCreator,
	Player,
	BulletBox,
	PlayerPistol,
	EnemyBulletR,
	EnemyBullet,
	DropWeapon,
	PlayerKnife,
	PlayerMachinegun,
	PlayerShotgun,
	PlayerFiregun,
	PlayerBomb,
	Effect,
	UI,
	UI2,
	End,
};

enum class eSfxType {
	PlayerBulletGroundSFX,
	PlayerBombSFX,
	PlayerBulletEnemySFX,
	NomalExplosionM,
	Boss1SFX,
	Boss2SFX,

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
	Laser,
};

enum class eCharType {
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	Mission1,
	Mission2,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	ExclamationMark,
	None,
};