#pragma once
class ArmyRoket
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
	class ArmyRoket : public GameObject
	{
	public:

		enum class eArmyRoketFSM {
			None,
			Move,
			Idle,
			Attack,
			Turn,
			Death,
		};


		ArmyRoket(Marco* p, Scene* scene, eDirection dir);
		~ArmyRoket();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

		Animator* GetAnimator() { return mAnimator; }
		void ArmyAppear();
		void StopMove();

	private:
		void none();
		void move();
		void idle();
		void attack();
		void turn();
		void death();
		
	private:
		Animator* mAnimator;
		eArmyRoketFSM mState;
		Marco* player;
		Scene* curScene;
		eDirection mDir;
		float mTime;
		bool isShoot;
	};
}
