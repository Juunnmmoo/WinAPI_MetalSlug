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
		Vector2 GetDisToBottom() { return disToBottom; }
		void SetDisToBottom(Vector2 topDiff) { disToBottom = topDiff; }

		
		void SetDirection(eDirection direction) { mDirection = direction; }
		eDirection GetDirection() { return mDirection; }
		

	private:
		//콜라이더 밑에 값 빼주는 역활
		Vector2 disToBottom;
		Vector2 mPos;
		Vector2 mScale;
		eDirection mDirection;
	};
}
