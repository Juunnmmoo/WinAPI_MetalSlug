#pragma once
#include "moGameObject.h"

namespace mo {
	class Animator;
	class Boss1_Attackor : public GameObject
	{
	public:

		Boss1_Attackor();
		~Boss1_Attackor();

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
		class Sound* deathSound;
		Animator* mAnimator;
		int heart;
	};
}