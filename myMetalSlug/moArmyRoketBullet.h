#pragma once
#include "moGameObject.h"

namespace mo {
	class Image;
	class ArmyRoketBullet : public GameObject
	{
	public:
		ArmyRoketBullet();
		~ArmyRoketBullet();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;
		void SetDir(Vector2 dir) {
			mDir = dir;
			mDir.Normalize();
		}

	private:
		float mTime;
		Image* mImage;
		Vector2 mDir;
		class Animator* mAnimator;
		bool isDeath;

	};
}
