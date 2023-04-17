#pragma once
#include "moGameObject.h"

namespace mo {
	class Transform;
	class Animator;
	class AnimatorR;
	class Camel : public GameObject
	{
	public:

		enum class eCamelArabianState {
			Start,
			Idle,
			Death,
			Attack,
			Turn,
			Throwing,
		};


		Camel();
		~Camel();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		Animator* GetAnimator() { return mAnimator; }
		void SetCamelArabianState(eCamelArabianState state) { mState = state; }



	private:
		void move();
		void attack();
		void start();
		void death();
		void idle();
		void turn();

	private:
		eCamelArabianState mState;
		Animator* mAnimator;
	};
}
