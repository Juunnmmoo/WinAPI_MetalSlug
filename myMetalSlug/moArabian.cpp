#include "moArabian.h"
#include "moImage.h"
#include "moSceneManager.h"
#include "moResources.h"
#include "moTransform.h"
#include "moInput.h"
#include "moTime.h"
#include "moAnimator.h"
#include "Collider.h"
#include "moScene.h"
#include "moObject.h"

namespace mo{
	Arabian::Arabian(Vector2 pos)
		:mPos (pos)
	{
	}

	Arabian::~Arabian()
	{
	}

	void Arabian::Initialize()
	{

		Image* mImageL = Resources::Load<Image>(L"ArabianLeft", L"..\\Resources\\Enemy\\ArabianLeft.bmp");

		
		Transform* tr;
		tr = GetComponent<Transform>();
		//tr->SetPos(Vector2{ 700.0f, 600.0f });
		tr->SetPos( mPos);
		tr->SetScale(Vector2{ 3.0f, 3.0f });
		tr->SetDisToBottom(Vector2{ 0.0f, 40.0f });

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"IdleL", mImageL, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 20, 15, 6, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"DeathL", mImageL, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 20, 15, 11, Vector2::Zero, 0.07);

		mAnimator->GetCompleteEvent(L"DeathL") = std::bind(&Arabian::deathCompleteEvent, this);

		mAnimator->Play(L"IdleL", true);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 60.0f, 100.0f });
		mCollider->SetLeftTop(Vector2{ -30.50f, -100.0f });

		GameObject::Initialize();
	}

	void Arabian::Update()
	{

		//Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPos();

		///*if(mDirection == eDirection::Right)
		//	pos.x += 1200.0f * Time::DeltaTime();
		//if (mDirection == eDirection::Left)
		//	pos.x -= 1200.0f * Time::DeltaTime();*/


		//pos.x += 100.0f * Time::DeltaTime();
	
		//tr->SetPos(pos);

		GameObject::Update();
	}

	void Arabian::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}

	void Arabian::OnCollisionEnter(Collider* other)
	{	
		

		if (other->GetOwner()->GetLayerType() == eLayerType::Bullet) {
			mAnimator->Play(L"DeathL", false);
			SetIsDeath(true);
		}
	}

	void Arabian::OnCollisionStay(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player
			&& Input::GetKeyDown(eKeyCode::D)) {
			mAnimator->Play(L"DeathL", false);
			SetIsDeath(true);
		}
	}

	void Arabian::OnCollisionExit(Collider* other)
	{
	}

	void Arabian::move()
	{
	}

	void Arabian::shoot()
	{
	}

	void Arabian::death()
	{
	}

	void Arabian::idle()
	{
	}
	void Arabian::deathCompleteEvent()
	{
		object::Destory(this);
	}
}