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
		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }
	private:

		Vector2 mPos;
		Vector2 mSize;
	};
}
