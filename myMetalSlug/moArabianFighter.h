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
			Move,
			Sit,
			Foword,
			Attack,
			Death,
			Turn,
		};


		ArabianFighter(Marco* p, Vector2 stop);
		~ArabianFighter();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

		Animator* GetAnimator() { return mAnimator; }
		void SetStartFoword(bool b) { startFoword = b; }

	private:
		void move();
		void sit();
		void foword();
		void attack();
		void turn();
		void death();
	private:

		Vector2 stopPos;
		Animator* mAnimator;
		eArabianFighterState mState;
		Marco* player;
		Scene* curScene;
		bool startFoword;
		float time;
		bool readyToAttack;
	};
}
