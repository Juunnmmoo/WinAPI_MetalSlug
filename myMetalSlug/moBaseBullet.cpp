#include "moBaseBullet.h"
#include "moImage.h"
#include "moResources.h"
#include "moTransform.h"
#include "moTime.h"
#include "Collider.h"

namespace mo {
	BaseBullet::BaseBullet()
		:mImage(Resources::Load<Image>(L"OriginalBullet", L"..\\Resources\\OriginalBullet.bmp"))
		, mDirection(eDirection::Right)
	{
	}
	BaseBullet::~BaseBullet()
	{
	}
	void BaseBullet::Initialize()
	{
		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 60.0f, 70.0f });
		mCollider->SetCenter(Vector2{ -30.50f, -70.0f });

	}
	void BaseBullet::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		if(mDirection == eDirection::Right)
			pos.x += 1200.0f * Time::DeltaTime();
		if (mDirection == eDirection::Left)
			pos.x -= 1200.0f * Time::DeltaTime();

		tr->SetPos(pos);
	}

	void BaseBullet::Render(HDC mHdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		if (mDirection == eDirection::Right)
			TransparentBlt(mHdc, pos.x + 25.0f, pos.y - 40.0f, 20, 20, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(153, 217, 234));
		if (mDirection == eDirection::Left)
			TransparentBlt(mHdc, pos.x - 25.0f, pos.y - 40.0f, 20, 20, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(153, 217, 234));
	}
}