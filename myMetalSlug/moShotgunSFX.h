
#pragma once
#include "moGameObject.h"

namespace mo {
	class Marco;
	class ShotgunSFX : public GameObject
	{
	public:

		ShotgunSFX();
		~ShotgunSFX();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

	private:
		Marco* player;
		Vector2 mPos;
		class Animator* mAnimator;
		class Sound* shootgunSound;
		bool isCollide;
		bool isUse;
	};
}
