#pragma once
#include "moGameObject.h"

namespace mo {
	class Animator;
	class Marco : public GameObject
	{
	public:

		enum class eMarcoState{
			Move,
			Shoot,
			Death,
			Idle,
		};


		Marco();
		~Marco();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

	private:
		void move();
		void shoot();
		void death();
		void idle();

	private:
		eMarcoState mState;
		Animator* mAnimator;
	};
}
