#pragma once
#include "moGameObject.h"

namespace mo {
	class Image;
	class BaseBullet : public GameObject
	{
	public:
		BaseBullet();
		~BaseBullet();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		virtual void OnCollisionEnter(class Collider* other)override;
		virtual void OnCollisionStay(class Collider* other)override;
		virtual void OnCollisionExit(class Collider* other)override;

		void SetDirection(eDirection direction) { mDirection = direction; }
		void SetDir(Vector2 dir) { 
			mDir = dir;
			mDir.Normalize();
		}

	private:
		float mTime;
		Image* mImage;
		eDirection mDirection;
		Vector2 mDir;
	};
}
