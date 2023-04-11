#pragma once
#include "moWeapon.h"

namespace mo {
	class Pistol : public Weapon
	{
	public:
		Pistol(Marco* marco, MarcoBottom* bottom);
		virtual ~Pistol();

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
		void attackEndEvent();
		void deathEndEvent();
		void resurrectionEndEvent();

	private:
		Marco* player;
		MarcoBottom* playerBottom;
		Marco::eMarcoState mState;		
		Animator* mAnimator;
		Animation* mPrevAnimation;
		RigidBody* mRigidbody;
		Transform* mTransform;
		bool unUsedParaglider;
		bool isBackToLife;
	};
}
