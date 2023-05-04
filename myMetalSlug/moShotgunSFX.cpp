#include "moShotgunSFX.h"
#include "moImage.h"
#include "moResources.h"
#include "moTransform.h"
#include "moTime.h"
#include "Collider.h"
#include "moObject.h"
#include "moInput.h"
#include "moCamera.h"
#include "moMarco.h"
#include "moObject.h"
#include "moArabian.h"
#include "moSceneManager.h"
#include "moObject.h"
#include "moAnimator.h"
#include "moSlave.h"
#include "moSound.h"

namespace mo {
	ShotgunSFX::ShotgunSFX()
		:mTime(0.0f)
	{
	}
	ShotgunSFX::~ShotgunSFX()
	{
	}
	void ShotgunSFX::Initialize()
	{
		shootgunSound = Resources::Load<Sound>(L"ShotgunBulletSound", L"..\\Resources\\Sound\\ShotgunBulletSound.wav");
		shootgunSound->SetVolume(80);
		shootgunSound->Play(false);
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 2.0f));
		tr->SetDisToBottom(Vector2(0.0f, 100.0f));

		Image* mImage = Resources::Load<Image>(L"ShotgunSFX", L"..\\Resources\\Weapon\\ShotgunSFX.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"shootR", mImage, Vector2(200.0f * 0, 200.0f * 0), 200.0f, 12, 4, 12, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"shootL", mImage, Vector2(200.0f * 11, 200.0f * 1), -200.0f, 12, 4, 12, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"shootTop", mImage, Vector2(200.0f * 0, 200.0f * 2), 200.0f, 12, 4, 12, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"shootBottom", mImage, Vector2(200.0f * 0, 200.0f * 3), 200.0f, 12, 4, 12, Vector2::Zero, 0.05);


		Collider* mCollider = AddComponent<Collider>();

		if (mDirection == eDirection::Left)
		{
			mCollider->SetSize(Vector2{ 180.0f, 110.0f });
			mCollider->SetLeftTop(Vector2{ -180.0f, -55.0f });
			mAnimator->Play(L"shootL", false);
		}
		else if (mDirection == eDirection::Right)
		{
			mCollider->SetSize(Vector2{ 180.0f, 110.0f });
			mCollider->SetLeftTop(Vector2{ 0.0f, -55.0f });
			mAnimator->Play(L"shootR", false);
		}
		else if (mDirection == eDirection::Top)
		{
			mCollider->SetSize(Vector2{ 110.0f, 180.0f });
			mCollider->SetLeftTop(Vector2{ -55.0f, -180.0f });
			mAnimator->Play(L"shootTop", false);
		}
		else if (mDirection == eDirection::Bottom)
		{
			mCollider->SetSize(Vector2{ 110.0f, 180.0f });
			mCollider->SetLeftTop(Vector2{ -55.0f, 0.0f });
			mAnimator->Play(L"shootBottom", false);
		}

		SetBulletType(eBulletType::Bullet);

		GameObject::Initialize();
	}
	void ShotgunSFX::Update()
	{
		mTime += Time::DeltaTime();
		if (mTime >= 0.2f)
			SetState(eState::Pause);

		if (mAnimator->IsComplte())
			object::Destory(this);

		GameObject::Update();
	}
	void ShotgunSFX::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}
	void ShotgunSFX::OnCollisionEnter(Collider* other)
	{
	}
	void ShotgunSFX::OnCollisionStay(Collider* other)
	{
	}
	void ShotgunSFX::OnCollisionExit(Collider* other)
	{
	}
}