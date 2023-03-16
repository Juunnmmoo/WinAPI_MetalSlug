#pragma once
#include "moGameObject.h"
#include "moMarcoBottom.h"

namespace mo {
	class RigidBody;
	class Animator;
	class Animation;
	class Marco : public GameObject
	{
	public:

		enum class eMarcoState{
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

	private:
		void move();
		void shoot();
		void death();
		void idle();
		void sit();
		void Jump();

		void shootStartEvent();
		void knifeCompleteEvent();

	private:
		MarcoBottom* bottom;
		eMarcoState mState;
		Animator* mAnimator;
		Animation* mPrevAnimation;
		RigidBody* mRigidbody;
		RigidBody* bottomRigidBody;
		bool isKnife;
	};
}
