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
		: mState(eWeaponObjectState::None)
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

		

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 30.0f, 50.0f });
		mCollider->SetLeftTop(Vector2{ 0.0f, -50.0f });

		mImage = Resources::Load<Image>(L"ArabianWeapon", L"..\\Resources\\Enemy\\ArabianWeapon.bmp");

		SetBulletType(eBulletType::knife);


		mAnimator = AddComponent<Animator>();
		mAnimator->SetAlpha(true);

		mAnimator->CreateAnimation(L"MoveL", mImage, Vector2(0.0f, 0.0f), 120.0f, 11, 4, 11, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MoveR", mImage, Vector2(120.0f * 10, 120.0f * 1), -120.0f, 11, 4, 11, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"StopL", mImage, Vector2(0.0f, 120.0f * 2), 120.0f, 11, 4, 1, Vector2::Zero, 0.08);
		mAnimator->CreateAnimation(L"StopR", mImage, Vector2(0.0f, 120.0f * 3), 120.0f, 11, 4, 1, Vector2::Zero, 0.08);

		//mAnimator->CreateAnimation(L"dropWeaponL", mImage, Vector2(120.0f * 5, 120.0f), -120.0f, 6, 2, 6, Vector2::Zero, 0.08);

		GameObject::Initialize();
	}
	void ArabianWeapon::Update()
	{	
		switch (mState)
		{
		case eWeaponObjectState::None:
			none();
			break;
		case eWeaponObjectState::Move:
			move();
			break; 
		case eWeaponObjectState::Drop:
			drop();
			break;
		}

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
	void ArabianWeapon::none()
	{
		if (mDir == eDirection::Left)
		{
			mAnimator->Play(L"MoveL", true);
		}
		else
		{
			mAnimator->Play(L"MoveR", true);
		}
		RigidBody* mRigidbody = GetComponent<RigidBody>();
		Vector2 velocity = mRigidbody->GetVelocity();
		velocity.y -= 600.0f;
		mRigidbody->SetVelocity(velocity);
		mRigidbody->SetGround(false);

		mState = eWeaponObjectState::Move;
	}
	void ArabianWeapon::move()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (mDir == eDirection::Left)
			pos.x -= 200.0f * Time::DeltaTime();
		else if (mDir == eDirection::Right)
			pos.x += 200.0f * Time::DeltaTime();
		
		tr->SetPos(pos);

		if (GetComponent<RigidBody>()->GetGround())
		{
			if (mDir == eDirection::Left)
			{
				mAnimator->Play(L"StopL", false);
			}
			else
			{
				mAnimator->Play(L"StopR", false);
			}
			SetState(eState::Pause);
			mAnimator->SetUseinvincibility(true);
			mState = eWeaponObjectState::Drop;
		}
	}
	void ArabianWeapon::drop()
	{

		if (!mAnimator->GetUseinvincibility())
		{
			object::Destory(this);
		}
	}
}