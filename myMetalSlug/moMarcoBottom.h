#pragma once
#include "moGameObject.h"

namespace mo {
	class Transform;
	class Animator;
	class AnimatorR;
	class MarcoBottom : public GameObject
	{
	public:

		enum class eMarcoState{
			Move,
			Shoot,
			Death,
			Idle,
		};


		MarcoBottom();
		~MarcoBottom();

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
