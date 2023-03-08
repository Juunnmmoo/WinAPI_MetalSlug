#include "moTransform.h"

namespace mo {
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mPos(Vector2::Zero)
		, mScale(Vector2::One)
		, mPlayerTopDiff(Vector2::Zero)
		, mDirection(eDirection::Right)
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{
	}
	void Transform::Render(HDC mHdc)
	{
	}
}