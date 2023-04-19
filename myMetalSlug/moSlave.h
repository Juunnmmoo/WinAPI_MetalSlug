#pragma once
class Slave
{
};

#pragma once
#include "moGameObject.h"

namespace mo {
	class Transform;
	class Animator;
	class AnimatorR;
	class Marco;
	class Scene;
	class Slave : public GameObject
	{
	public:

		enum class eSlaveState {
			Idle,
			BeReleased,
			MoveL,
			MoveR,
			Flying,
			BeforeTakeOut,
			TakeOut,
			Sir,
			Run,
		};


		Slave(Marco* p, Scene* scene, Vector2 pos, eMarcoWeapon weapon);
		~Slave();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

		Animator* GetAnimator() { return mAnimator; }
		void SetIsRelease(bool b) { isReleased = b; }
		void SetSlaveState(eSlaveState state) { mState = state; }

	private:
		void idle();
		void beReleased();
		void moveL();
		void moveR();

		void flying();
		void beforeTakeOut();
		void takeOut();
		void sir();
		void run();
	
	private:
		Vector2 mPos;
		Animator* mAnimator;
		eSlaveState mState;
		eMarcoWeapon weaponType;
		Marco* player;
		Scene* curScene;
		Vector2 playerPos;
		bool isReleased;
		bool isTakeOut;
		bool isDrop;

		float time;
		
	};
}
