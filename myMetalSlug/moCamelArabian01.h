#pragma once
#include "moGameObject.h"

namespace mo {
	class Transform;
	class Animator;
	class AnimatorR;
	class Marco;
	class Scene;
	class Camel;
	class CamelArabian02;
	class CamelArabian01 : public GameObject
	{
	public:

		enum class eCamelArabianState {
			Start,
			Move,
			Idle,
			Death,
			Attack,
			Turn,
			Lost,
		};


		CamelArabian01(Marco* p, Camel* camel, CamelArabian02* arbian, Scene* scene);
		~CamelArabian01();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;


	private:
		void start();
		void move();
		void idle();
		void death();
		void attack();
		void turn();
		void lost();
	private:

		Vector2 mPos;
		Animator* mAnimator;
		Animator* camelAnimator;
		Animator* secondAnimator;
		Transform* mT;
		Transform* camelT;
		Transform* secondT;
		eCamelArabianState mState;
		Marco* player;
		Camel* mCamel;
		CamelArabian02* mSecond;
		class Sound* EnemyDeathSound4;
		Scene* curScene;
		bool isPlayed;
		bool noHeart;
		float moveTime;
		int bulletCnt;
		int heart;
		
	};
}
