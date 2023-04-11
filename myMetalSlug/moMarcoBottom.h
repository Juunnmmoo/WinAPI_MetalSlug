#pragma once
#include "moGameObject.h"

namespace mo {
	class Transform;
	class Animator;
	class AnimatorR;
	class MarcoBottom : public GameObject
	{
	public:

		enum class eMarcoState {
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
		bool GetIsShooting() { return isSitShooting; }

		Animator* GetAnimator() { return mAnimator; }
		void SetBottomState(eMarcoState state) { mState = state; }

		void SetIsKnife(bool b) { isKnife = b; }

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

		void shootEndEvent();


	private:
		eMarcoState mState;
		Animator* mAnimator;
		bool isGround;
		bool isSitShooting;
		bool isKnife;
		eMarcoWeapon mWeaponState;
	};
}
