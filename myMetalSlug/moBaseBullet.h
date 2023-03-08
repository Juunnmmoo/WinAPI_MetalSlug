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

		void SetDirection(eDirection direction) { mDirection = direction; }

	private:
		Image* mImage;
		eDirection mDirection;
	};
}
