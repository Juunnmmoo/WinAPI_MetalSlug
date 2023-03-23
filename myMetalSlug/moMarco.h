#pragma once
#include "moGameObject.h"
#include "moMarcoBottom.h"

namespace mo {
	class Pistol;
	class RigidBody;
	class Animator;
	class Animation;
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
		};


		Marco(MarcoBottom* obj);
		~Marco();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

		eMarcoState GetState() { return mState; }
		void SetState(eMarcoState state) { mState = state; }

	private:
		void paraglider();
		void move();
		void shoot();
		void death();
		void idle();
		void sit();
		void jump();

		void shootStartEvent();
		void AttackEndEvent();

	private:
		MarcoBottom* bottom;
		eMarcoState mState;
		Animator* mAnimator;
		Animation* mPrevAnimation;
		RigidBody* mRigidbody;
		RigidBody* bottomRigidBody;
		bool isKnife;
		Pistol* pistol;
	};
}
