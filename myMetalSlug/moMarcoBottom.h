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
			Sit,
		};


		MarcoBottom();
		~MarcoBottom();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		Animator* GetAnimator() { return mAnimator; }

	private:
		void move();
		void shoot();
		void death();
		void idle();
		void sit();
	private:
		eMarcoState mState;
		Animator* mAnimator;
	};
}
