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
			Paraglider,
			Move,
			Shoot,
			Death,
			Idle,
			Sit,
			Jump,
		};


		MarcoBottom();
		~MarcoBottom();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;
		
		void SetIsGround(bool b) { isGround = b; }


		Animator* GetAnimator() { return mAnimator; }

	private:
		void paraglider();
		void move();
		void shoot();
		void death();
		void idle();
		void sit();
		void jump();


	private:
		eMarcoState mState;
		Animator* mAnimator;
		bool isGround;
	};
}
