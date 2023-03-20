#pragma once
#include "moGameObject.h"

namespace mo {
	class Image;
	class Mission1BG : public GameObject
	{
	public:

		Mission1BG();
		~Mission1BG();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

	private:
		Image* mImage;
		UINT TopDiff;
	};
}
