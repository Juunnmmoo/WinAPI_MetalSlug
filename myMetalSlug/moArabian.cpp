#include "moArabian.h"
#include "moImage.h"
#include "moSceneManager.h"
#include "moResources.h"
#include "moTransform.h"
#include "moInput.h"
#include "moTime.h"
#include "moAnimator.h"
#include "Collider.h"
#include "moBaseBullet.h"
#include "moScene.h"
#include "moObject.h"

namespace mo{
	


	Arabian::Arabian()
	{
	}

	Arabian::~Arabian()
	{
	}

	void Arabian::Initialize()
	{

		Image* mImageL = Resources::Load<Image>(L"ArabianLeft", L"..\\Resources\\ArabianLeft.bmp");

		
		Transform* tr;
		tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 700.0f, 600.0f });
		tr->SetScale(Vector2{ 3.0f, 3.0f });
		tr->SetTopDiff(Vector2{ 0.0f, 40.0f });

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"IdleL", mImageL, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 20, 15, 6, Vector2::Zero, 0.15);
		mAnimator->Play(L"IdleL", true);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 60.0f, 100.0f });
		mCollider->SetLeftTop(Vector2{ -30.50f, -100.0f });

		GameObject::Initialize();
	}

	void Arabian::Update()
	{
		GameObject::Update();
	}

	void Arabian::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}

	void Arabian::OnCollisionEnter(Collider* other, eLayerType otherType)
	{
		if (otherType == eLayerType::Bullet) 
			object::Destory(this);
		
	}

	void Arabian::OnCollisionStay(Collider* other, eLayerType otherType)
	{
	}

	void Arabian::OnCollisionExit(Collider* other, eLayerType otherType)
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

	void Arabian::shootStartEvent()
	{
	}

	void Arabian::knifeCompleteEvent()
	{
	}

}