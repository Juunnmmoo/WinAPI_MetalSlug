#pragma once
#include "moGameObject.h"

namespace mo {
	class Image;
	class SelectBG : public GameObject
	{
	public:

		SelectBG();
		~SelectBG();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

	private:
		Image* mImage;
	};
}
