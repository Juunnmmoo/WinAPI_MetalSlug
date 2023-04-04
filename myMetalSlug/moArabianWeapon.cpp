#include "moArabianWeapon.h"
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
#include "Collider.h"

namespace mo {
	ArabianWeapon::ArabianWeapon()

	{
	}
	ArabianWeapon::~ArabianWeapon()
	{
	}
	void ArabianWeapon::Initialize()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		tr->SetScale(Vector2{ 3.0f, 3.0f });
		tr->SetDisToBottom(Vector2{ 0.0f, 50.0f });

		RigidBody* mRigidbody = AddComponent<RigidBody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2(0.0f, 700.0f));

		

		/*Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 60.0f, 100.0f });
		mCollider->SetLeftTop(Vector2{ -30.50f, -100.0f });*/

		mImage = Resources::Load<Image>(L"ArabianWeapon", L"..\\Resources\\Enemy\\ArabianWeapon.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"WeaponL", mImage, Vector2(0.0f, 0.0f), 120.0f, 19, 1, 19, Vector2::Zero, 0.1);
		//mAnimator->CreateAnimation(L"dropWeaponL", mImage, Vector2(120.0f * 5, 120.0f), -120.0f, 6, 2, 6, Vector2::Zero, 0.08);

		GameObject::Initialize();
	}
	void ArabianWeapon::Update()
	{


		


		if (!isUsed)
		{
			isUsed = true;
			if (mDir == eDirection::Left)
			{
				mAnimator->Play(L"WeaponL", false);
			}
			else
			{
				mAnimator->Play(L"dropWeaponR", false);
			}
			RigidBody* mRigidbody = GetComponent<RigidBody>();
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 600.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
		}

			Transform* tr;
			tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();

			if (mDir == eDirection::Left)
				pos.x -= 200.0f * Time::DeltaTime();
			else if (mDir == eDirection::Right)
				pos.x += 200.0f * Time::DeltaTime();
			tr->SetPos(pos);

			if (mAnimator->IsComplte())
				object::Destory(this);
		


		GameObject::Update();
	}
	void ArabianWeapon::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void ArabianWeapon::PlayAnimation(eDirection direction)
	{
		mDir = direction;
	}
}