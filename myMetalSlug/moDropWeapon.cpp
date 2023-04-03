#include "moDropWeapon.h"
#include "moResources.h"
#include "moImage.h"
#include "moApplication.h"
#include "moCamera.h"
#include "moTransform.h"
#include "moMarco.h"
#include "moRigidBody.h"
#include "moAnimator.h"
#include "moObject.h"
#include "moTime.h"

namespace mo {
	DropWeapon::DropWeapon()
	{
	}
	DropWeapon::~DropWeapon()
	{
	}
	void DropWeapon::Initialize()
	{
		

		Transform* tr;
		tr = GetComponent<Transform>();
		tr->SetScale(Vector2{ 2.5f, 2.5f });
		tr->SetDisToBottom(Vector2{ 0.0f, 50.0f });
		//tr->SetDisToBottom(Vector2{ 0.0f, 50.0f });

		RigidBody* mRigidbody = AddComponent<RigidBody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2(0.0f, 700.0f));

		mImage = Resources::Load<Image>(L"DropWeapon", L"..\\Resources\\Weapon\\DropWeapon.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"dropWeaponR", mImage, Vector2(0.0f, 0.0f), 120.0f, 6, 2, 6, Vector2::Zero, 0.08);
		mAnimator->CreateAnimation(L"dropWeaponL", mImage, Vector2(120.0f * 5, 120.0f), -120.0f, 6, 2, 6, Vector2::Zero, 0.08);

		GameObject::Initialize();

	}
	void DropWeapon::Update()
	{
		if (mAnimator->IsComplte())
		{
			object::Destory(this);
		}
		
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		if (mDir == eDirection::Left)
		{
			pos.x -= 400.0f * Time::DeltaTime();
		}
		else
		{
			pos.x += 400.0f * Time::DeltaTime();
		}
		tr->SetPos(pos);

		GameObject::Update();
	}
	void DropWeapon::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}
	void DropWeapon::PlayAnimation(eDirection direction)
	{
		if (direction == eDirection::Left || direction == eDirection::LTop ||
			direction == eDirection::LBottom || direction == eDirection::LSit)
		{
			mDir = eDirection::Left;
			mAnimator->Play(L"dropWeaponL", false);
		}
		else
		{
			mDir = eDirection::Right;
			mAnimator->Play(L"dropWeaponR", false);
		}
	}
}