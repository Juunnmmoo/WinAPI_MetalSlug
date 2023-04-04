#include "moPistolBullet.h"
#include "moImage.h"
#include "moResources.h"
#include "moTransform.h"
#include "moTime.h"
#include "Collider.h"
#include "moObject.h"
#include "moInput.h"
#include "moCamera.h"

namespace mo {
	PistolBullet::PistolBullet() 
		: mDirection(eDirection::Right)
		, mDir(Vector2(5.0f, 0.0f))
	{
		mDir.Normalize();
	}
	PistolBullet::~PistolBullet()
	{
	}
	void PistolBullet::Initialize()
	{
		mImage = Resources::Load<Image>(L"OriginalBullet", L"..\\Resources\\Weapon\\Bullet\\OriginalBullet.bmp");


		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 20.0f, 20.0f });
		if (mDirection == eDirection::Right)
			mCollider->SetLeftTop(Vector2{ 50.0f, -50.0f });
		else if (mDirection == eDirection::Left)
			mCollider->SetLeftTop(Vector2{ -50.0f, -50.0f });

		else if (mDirection == eDirection::Top)
			mCollider->SetLeftTop(Vector2{ -5.0f, -90.0f });
		else if (mDirection == eDirection::LSit)
			mCollider->SetLeftTop(Vector2{ -50.0f, -10.0f });
		else if (mDirection == eDirection::RSit)
			mCollider->SetLeftTop(Vector2{ +50.0f, -10.0f });
		else if (mDirection == eDirection::Bottom)
			mCollider->SetLeftTop(Vector2{ -5.0f, 90.0f });

		GameObject::Initialize();

	}
	void PistolBullet::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		//Vector2 pos = Camera::CaluatePos(tr->GetPos());

		/*if(mDirection == eDirection::Right)
			pos.x += 1200.0f * Time::DeltaTime();
		if (mDirection == eDirection::Left)
			pos.x -= 1200.0f * Time::DeltaTime();*/


		pos.x += 1000.0f * mDir.x * Time::DeltaTime();
		pos.y += 1000.0f * mDir.y * Time::DeltaTime();


		tr->SetPos(pos);

		GameObject::Update();
	}

	void PistolBullet::Render(HDC mHdc)
	{
		Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPos();
		Vector2 pos = Camera::CaluatePos(tr->GetPos());


		if (mDirection == eDirection::Right)
			TransparentBlt(mHdc, pos.x + 50.0f, pos.y - 50.0f, 20, 20, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(153, 217, 234));
		else if (mDirection == eDirection::Left)
			TransparentBlt(mHdc, pos.x - 50.0f, pos.y - 50.0f, 20, 20, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(153, 217, 234));
		else if (mDirection == eDirection::Top)
			TransparentBlt(mHdc, pos.x - 5.0f, pos.y - 90.0f, 20, 20, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(153, 217, 234));
		else if (mDirection == eDirection::RSit)
			TransparentBlt(mHdc, pos.x + 50.0f, pos.y - 10.0f, 20, 20, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(153, 217, 234));
		else if (mDirection == eDirection::LSit)
			TransparentBlt(mHdc, pos.x - 50.0f, pos.y - 10.0f, 20, 20, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(153, 217, 234));
		else if (mDirection == eDirection::Bottom)
			TransparentBlt(mHdc, pos.x - 5.0f, pos.y + 90.0f, 20, 20, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(153, 217, 234));
		GameObject::Render(mHdc);
	}
	void PistolBullet::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Enemy)
			object::Destory(this);
	}

	void PistolBullet::OnCollisionStay(Collider* other)
	{
	}

	void PistolBullet::OnCollisionExit(Collider* other)
	{
	}
}