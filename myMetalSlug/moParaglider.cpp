#include "moParaglider.h"
#include "moResources.h"
#include "moInput.h"
#include "moAnimator.h"
#include "moTransform.h"
#include "moImage.h"
#include "moMarco.h"
#include "Collider.h"
#include"moRigidBody.h"
#include "moObject.h"

namespace mo {
	Paraglider::Paraglider(Marco* owner)
		: mOwner(owner)
		, mState(eState::use)
	{
	}
	Paraglider::~Paraglider()
	{
	}
	void Paraglider::Initialize()
	{


		Transform* tr = GetComponent<Transform>();
		Transform* ownerTr = mOwner->GetComponent<Transform>();
		tr->SetScale(Vector2{ 3.0f, 3.0f });
		tr->SetTopDiff(Vector2{ 0.0f, 30.0f });
		//tr->SetPos(ownerTr->GetPos()+ Vector2(0.0f, 15.0f));

		mImage = Resources::Load<Image>(L"Effect", L"..\\Resources\\Effect\\something.bmp");

		mAnimator = AddComponent<Animator>();
		
		mAnimator->CreateAnimation(L"Idle", mImage, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 20, 10, 5, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"Destory", mImage, Vector2(120.0f * 19, 120.0f * 1), -120.0f, 20, 10, 17, Vector2::Zero, 0.05);

		mAnimator->Play(L"Idle", true);

		GameObject::Initialize();
	}
	void Paraglider::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Transform* ownerTr = mOwner->GetComponent<Transform>();
		tr->SetPos(ownerTr->GetPos() + Vector2(-10.0f, 20.0f));

		switch (mState) {

		case mo::Paraglider::eState::use:
			use();
			break;
		case mo::Paraglider::eState::notUse:
			notUse();
			break;
		
		default:
			break;
		}
		

		GameObject::Update();
	}
	void Paraglider::Render(HDC mHdc)
	{

		GameObject::Render(mHdc);
	}
	void Paraglider::use()
	{
		RigidBody* rg = mOwner->GetComponent<RigidBody>();


		if (Input::GetKeyDown(eKeyCode::S)) {
			mAnimator->Play(L"Destory", false);
			mState = eState::notUse;
		}

		if (rg->GetGround()) {
			mAnimator->Play(L"Destory", false);
			mState = eState::notUse;
		}

	}
	void Paraglider::notUse()
	{
		if (mAnimator->IsComplte()) {
			object::Destory(this);
		}

	}
}