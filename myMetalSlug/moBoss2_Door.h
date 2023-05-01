#pragma once
#include "moGameObject.h"

namespace mo {
	class Animator;
	class Boss2_Door : public GameObject
	{
	public:

		Boss2_Door();
		~Boss2_Door();

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