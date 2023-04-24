#pragma once
#include "moGameObject.h"

namespace mo {
	class PlayerIdleBottom : public GameObject
	{
	public:

		PlayerIdleBottom();
		~PlayerIdleBottom();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

	private:
		class Animator* mAnimator;
		float mTime;
	};
}
