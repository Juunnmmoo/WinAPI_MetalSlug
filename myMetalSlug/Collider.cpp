#include "Collider.h"
#include "moGameObject.h"
#include "moTransform.h"


namespace mo {

	UINT Collider::ColliderNumber = 0;

	Collider::Collider()
		:Component(eComponentType::Collider)
		, mLeftTopPos(Vector2::Zero)
		, mPos(Vector2::Zero)
		, mSize(Vector2::One)
		, mID(ColliderNumber++)
		, colliderCheck(0)
	{
	}

	Collider::~Collider()
	{
	}

	

	void Collider::Initialize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		mPos = tr->GetPos() + mLeftTopPos;
	}

	void Collider::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		mPos = tr->GetPos() + mLeftTopPos;
	}

	void Collider::Render(HDC mHdc)
	{
		HPEN pen = NULL;

		if(colliderCheck<=0)
			pen = CreatePen(BS_SOLID, 2, RGB(0, 255, 0));
		else
			pen = CreatePen(BS_SOLID, 2, RGB(255, 0, 255));

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
		colliderCheck++;
		GetOwner()->OnCollisionEnter(other);
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		colliderCheck--;
		GetOwner()->OnCollisionExit(other);
	}
}