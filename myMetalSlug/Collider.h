#pragma once
#include "moComponent.h"

namespace mo {
	class Collider : public Component
	{
	public:

		Collider() ;
		virtual ~Collider();

		void OnCollisionEnter(Collider* other);
		void OnCollisionStay(Collider* other);
		void OnCollisionExit(Collider* other);

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		void SetCenter(Vector2 center) { mCenter = center; };
		void SetSize(Vector2 size) { mSize = size; };
		Vector2 GetPos() { return mPos; }
		Vector2 GetSize() { return mSize; }
		UINT GetID() { return mID; }

	private:
		Vector2 mPos;
		Vector2 mCenter;
		Vector2 mSize;
		static UINT ColliderNumber;
		UINT mID;
	};
}
