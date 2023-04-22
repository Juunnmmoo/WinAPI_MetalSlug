#pragma once
#include "moGameObject.h"

namespace mo {
	class Transform;
	class Animator;
	class AnimatorR;
	class Marco;
	class Scene;
	class Arabian : public GameObject
	{
	public:

		enum class eArabianState {
			Move,
			Run,
			Attack,
			Death,
			BackJump,
			Idle,
			Turn,
			Throwing,
			Jump,
		};


		Arabian(Marco* p, Scene* scene, eArabianState state);
		~Arabian();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;


		void SetArabianIdle();
		Animator* GetAnimator() { return mAnimator; }

	private:
		void move();
		void attack();
		void death();
		void idle();
		void throwing();
		void turn();
		void run();
		void jump();

	private:
		Vector2 mPos;
		Animator* mAnimator;
		eArabianState mState;
		Marco* player;
		Scene* curScene;
		bool isThrowing;
		float time;
		bool readyToAttack;
	};
}
