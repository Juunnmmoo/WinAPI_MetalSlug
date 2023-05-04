#pragma once
#include "moGameObject.h"
#include "moMarcoBottom.h"

namespace mo {
	class Machinegun;
	class Pistol;
	class RigidBody;
	class Animator;
	class Animation;
	class PlayerKnife;
	class Shotgun;
	class Marco : public GameObject
	{
	public:
		enum class eMarcoState{
			Paraglider,
			Move,
			Shoot,
			Death,
			Idle,
			Sit,
			Jump,
			Complete,
		};


		Marco(MarcoBottom* obj, PlayerKnife* right, PlayerKnife* left);
		~Marco();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

		void ChangeWeapon(eMarcoWeapon state);

		void SetBulletNum(int num) { bulletNum = num; }
		void AddBulletNum(int num) { bulletNum += num; }
		int GetBulletNum() { return bulletNum; }

		void SetBombNum(int num) { bombNum = num; }
		void AddBombNum(int num) { bombNum += num; }
		int GetBombNum() { return bombNum; }

		void SetIsKnife(bool b) { isKnife = b; }
		bool GetIsKnife() { return isKnife; }

		void SetBossZone(bool b) { isBoss2Zone = b; }
		bool GetBossZone() { return isBoss2Zone; }

		void SetBossX(float x) { BossX = x; }
		float GetBossX() { return BossX; }

		void MissionComplete();

		eMarcoState GetMarcoState() { return mState; }
		void SetMarcoState(eMarcoState state) { mState = state; }

		eMarcoWeapon GetMarcoWeaponType() {	return mWeaponState;}

	private:
		MarcoBottom* bottom;
		eMarcoState mState;
		Animator* mAnimator;
		RigidBody* mRigidbody;
		Pistol* pistol;
		Machinegun* machinegun;
		Shotgun* shotgun;
		eMarcoWeapon mWeaponState;
		PlayerKnife* leftKnife;
		PlayerKnife* rightKnife;
		class Sound* marcoScream;
		bool isKnife;
		int bulletNum;
		int bombNum;
		bool isBoss2Zone;
		float BossX;
	};
}
