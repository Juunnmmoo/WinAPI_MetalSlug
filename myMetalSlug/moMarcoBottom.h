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
		void SetWeaponState(eMarcoWeapon state) { mWeaponState = state; }
		void PlaySitAnimation();

		Animator* GetAnimator() { return mAnimator; }

	private:
		void paraglider();
		void move();
		void shoot();
		void death();
		void idle();
		void p_sit();
		void m_sit();
		void s_sit();
		void f_sit();
		void jump();


	private:
		eMarcoState mState;
		Animator* mAnimator;
		bool isGround;
		eMarcoWeapon mWeaponState;
	};
}
