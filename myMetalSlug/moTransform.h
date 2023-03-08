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
		Vector2 GetTopDiff() { return mPlayerTopDiff; }
		void SetTopDiff(Vector2 topDiff) { mPlayerTopDiff = topDiff; }

		
		void SetDirection(eDirection direction) { mDirection = direction; }
		eDirection GetDirection() { return mDirection; }

	private:
		Vector2 mPlayerTopDiff;
		Vector2 mPos;
		Vector2 mScale;
		eDirection mDirection;
	};
}
