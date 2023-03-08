#pragma once
#include "moComponent.h"

namespace mo {
	class Collider : public Component
	{
	public:

		Collider() ;
		virtual ~Collider();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		void SetCenter(Vector2 center) { mCenter = center; };
		void SetSize(Vector2 size) { mSize = size; };
		void SetScale(Vector2 scale) { mScale = scale; };
		Vector2 GetPos() { return mPos; }
		Vector2 GetSize() { return mSize; }
	private:
		Vector2 mPos;
		Vector2 mCenter;
		Vector2 mScale;
		Vector2 mSize;
	};
}
