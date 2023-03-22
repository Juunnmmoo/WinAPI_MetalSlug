#pragma once
#include "moGameObject.h"

namespace mo {
	class Mission1BG : public GameObject
	{
	public:

		Mission1BG();
		~Mission1BG();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		void SetPlayer(class Marco* marco) { mPlayer = marco; }

	private:
		class Image* main;
		class Image* ground;
		class Marco* mPlayer;
		UINT TopDiff;
	};
}
