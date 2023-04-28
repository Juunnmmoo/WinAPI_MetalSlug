#pragma once
#include "moGameObject.h"

namespace mo {
	class Animator;
	class Boss1_CurtainIdle : public GameObject
	{
	public:

		Boss1_CurtainIdle();
		~Boss1_CurtainIdle();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		Animator* GetAnimator() { return mAnimator; }

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

	private:
		class Image* mImage;
		float mTime;
		Animator* mAnimator;
	};
}