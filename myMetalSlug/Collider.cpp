#include "Collider.h"
#include "moGameObject.h"
#include "moTransform.h"


namespace mo {

	UINT Collider::ColliderNumber = 0;

	Collider::Collider()
		:Component(eComponentType::Collider)
		, mCenter(Vector2::Zero)
		, mPos(Vector2::Zero)
		, mSize(Vector2::One)
		, mID(ColliderNumber++)
	{
	}

	Collider::~Collider()
	{
	}

	

	void Collider::Initialize()
	{
	}

	void Collider::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		mPos = tr->GetPos() + mCenter;
	}

	void Collider::Render(HDC mHdc)
	{
		HPEN pen = CreatePen(BS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(mHdc, pen);
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(mHdc, brush);

		Rectangle(mHdc, mPos.x, mPos.y, mPos.x + mSize.x, mPos.y + mSize.y);

		(HPEN)SelectObject(mHdc, oldPen);
		(HBRUSH)SelectObject(mHdc, oldBrush);
		DeleteObject(pen);
	}
	void Collider::OnCollisionEnter(Collider* other)
	{
	}

	void Collider::OnCollisionStay(Collider* other)
	{
	}

	void Collider::OnCollisionExit(Collider* other)
	{
	}
}