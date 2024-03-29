#pragma once
#include "moGameObject.h"

namespace mo {
	class Transform;
	class Animator;
	class AnimatorR;
	class Marco;
	class Scene;
	class ArabianFighter : public GameObject
	{
	public:

		enum class eArabianFighterState {
			Idle,
			Move,
			Sit,
			Foword,
			Attack,
			Death,
			Turn,
			MoveAway,
		};


		ArabianFighter(Marco* p, Vector2 stop, int max, eArabianFighterState state);
		~ArabianFighter();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

		Animator* GetAnimator() { return mAnimator; }
		void SetStartFoword(bool b) { startFoword = b; }
		void SetFighterState(eArabianFighterState state) { mState = state; }
		eArabianFighterState GetFighterState() { return mState; }

	private:
		void idle();
		void move();
		void sit();
		void foword();
		void attack();
		void turn();
		void death();
		void moveAway();
	private:

		Vector2 stopPos;
		Animator* mAnimator;
		eArabianFighterState mState;
		class Sound* EnemyDeathSound4;
		Marco* player;
		bool startFoword;
		int heart;
		int maxTurn;
		int runCnt;
		float time;
		bool readyToAttack;
	};
}
