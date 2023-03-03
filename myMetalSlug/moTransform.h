#pragma once
#include "moComponent.h"

namespace mo {
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;
	
		Vector2 GetPos() { return mPos; }
		void SetPos(Vector2 pos) { mPos = pos; }
		Vector2 GetScale() { return mScale; }
		void SetScale(Vector2 size) { mScale = size; }
	private:

		Vector2 mPos;
		Vector2 mScale;
	};
}
