#pragma once
#include "moGameObject.h"

namespace mo {
	class Transform;
	class Animator;
	class AnimatorR;
	class Marco;
	class Scene;
	class AbulAbbas : public GameObject
	{
	public:

		enum class eAbulAbbasState {
			Idle,
			MoveFoword,
			MoveL,
			AttackSign,
			Run,
			BeforeGiveUp,
			GiveUp,
			None,
		};


		AbulAbbas(Vector2 stop, eAbulAbbasState state);
		~AbulAbbas();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

		Animator* GetAnimator() { return mAnimator; }
		void SetSlaveState(eAbulAbbasState state) { mState = state; }
		void StartAttack() { startAttack = true; }
		void StartRun() { startRun = true; };
		void StartGiveUp() { startGiveUp = true; };

	private:
		void idle();
		void moveFoword();
		void attackSign();
		void run();
		void beforeGiveUp();
		void giveUp();

	private:
		Animator* mAnimator;
		eAbulAbbasState mState;
		Vector2 stopPos;
		bool startAttack;
		bool startRun;
		bool startGiveUp;
		float time;

	};
}
