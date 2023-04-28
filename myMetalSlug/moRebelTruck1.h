
#pragma once
#include "moGameObject.h"

namespace mo {
	class Transform;
	class Animator;
	class Marco;
	class Scene;
	class RebelTruck2;
	class RebelTruck1 : public GameObject
	{
	public:

		enum class eRebelTruckState {
			Move,
			Drop,
			Death,
		};


		RebelTruck1(Marco* p, RebelTruck2* second, Scene* scene, Vector2 stop);
		~RebelTruck1();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;


	private:
		void move();
		void drop();
		void death();

	private:

		Animator* mAnimator;
		Animator* secondAnimator;
		Transform* mT;
		Transform* secondT;
		eRebelTruckState mState;
		Marco* player;
		RebelTruck2* mSecond;
		Scene* curScene;
		Vector2 stopPos;
		int heart;
		bool useSfx;
		float dropTime;
		int createCnt;
		bool isCameraStop;
		class AbulAbbas* abul;
	};
}
