#pragma once
#include "moGameObject.h"

namespace mo {
	class Transform;
	class Animator;
	class AnimatorR;
	class Arabian : public GameObject
	{
	public:

		enum class eMarcoState {
			Move,
			Shoot,
			Death,
			Idle,
		};


		Arabian();
		~Arabian();

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

		void deathCompleteEvent();
		void knifeCompleteEvent();

	private:
		eMarcoState mState;
		Animator* mAnimator;
	};
}
