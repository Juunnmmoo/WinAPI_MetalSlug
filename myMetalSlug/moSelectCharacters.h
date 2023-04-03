#pragma once
#include "moGameObject.h"

namespace mo {
	class Image;
	class SelectCharactor : public GameObject
	{
	public:

		SelectCharactor(Vector2 pos, Vector2 iPos);
		~SelectCharactor();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;
		
		void SetImagePos(Vector2 pos) { imagePos = pos; }


	private:
		Image* mImage;
		Vector2 mPos;
		Vector2 imagePos;
	};
}
