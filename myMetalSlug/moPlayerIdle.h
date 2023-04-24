#pragma once
#include "moGameObject.h"

namespace mo {
	class PlayerIdle : public GameObject
	{
	public:

		PlayerIdle();
		~PlayerIdle();

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
