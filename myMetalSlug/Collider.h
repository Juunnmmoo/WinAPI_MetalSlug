#pragma once
#include "moComponent.h"

namespace mo {
	class Collider : public Component
	{
	public:

		Collider() ;
		virtual ~Collider();

		void OnCollisionEnter(Collider* other );
		void OnCollisionStay(Collider* other);
		void OnCollisionExit(Collider* other);

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		void SetLeftTop(Vector2 center) { mLeftTopPos = center; };
		void SetSize(Vector2 size) { mSize = size; };

		Vector2 GetCenter() { 
			Vector2 center = Vector2::Zero;
			center.x = mPos.x + (mSize.x / 2.0f);
			center.y = mPos.y + (mSize.y / 2.0f);
			return center; 
		}


		Vector2 GetPos() { return mPos; }
		Vector2 GetSize() { return mSize; }
		UINT GetID() { return mID; }

	private:
		Vector2 mPos;
		/*Vector2 mLeftTop;*/
		Vector2 mLeftTopPos;
		Vector2 mSize;
		static UINT ColliderNumber;
		UINT mID;
		int colliderCheck;
	};
}
