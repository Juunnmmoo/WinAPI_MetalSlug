#pragma once
#include "moGameObject.h"
#include "moMarcoBottom.h"

namespace mo {
	class Machinegun;
	class Pistol;
	class RigidBody;
	class Animator;
	class Animation;
	class Marco : public GameObject
	{
	public:
		enum class eMarcoWeapon {
			Pistol,
			Machinegun,
			Shotgun,
			Firegun,
		};

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
		MarcoBottom* bottom;
		eMarcoState mState;
		Animator* mAnimator;
		RigidBody* mRigidbody;
		Pistol* pistol;
		Machinegun* machinegun;
		eMarcoWeapon mWeaponState;
		bool isKnife;
	};
}
