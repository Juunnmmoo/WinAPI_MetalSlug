#pragma once
#include "moGameObject.h"

namespace mo {
	class Image;
	class TitleBG : public GameObject
	{
	public:

		TitleBG();
		~TitleBG();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

	private:
		Image* mImage;
	};
}
