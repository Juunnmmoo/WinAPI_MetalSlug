
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
		void SetDirection(eDirection direction) { mDirection = direction; }
	
		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

	private:
		Marco* player;
		Vector2 mPos;
		eDirection mDirection;
		class Animator* mAnimator;
		class Sound* shootgunSound;
		float mTime;
		bool isCollide;
		bool isUse;
	};
}
