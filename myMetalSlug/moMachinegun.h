#pragma once
#include "moWeapon.h"

namespace mo {
	class Machinegun : public Weapon
	{
	public:
		Machinegun(Marco* marco, MarcoBottom* bottom);
		virtual ~Machinegun();

		void Initialize();
		void Update();

	private:
		void paraglider();
		void move();
		void shoot();
		void death();
		void idle();
		void sit();
		void jump();

		void shootStartEvent();
		void attackCompleteEvent();
		void attackEndEvent();
		void diagonalAttackStartEvent();
		void diagonalAttackEndEvent();

			

	private:
		Marco* player;
		MarcoBottom* playerBottom;
		Marco::eMarcoState mState;
		Animator* mAnimator;
		Animation* mPrevAnimation;
		RigidBody* mRigidbody;
		Transform* mTransform;
		class Sound* machinegunBulletSound;
		bool unUsedParaglider;
		bool isBomb;
		bool isShooting;
	};
}
