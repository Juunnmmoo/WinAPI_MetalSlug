#include "moMarco.h"
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

namespace mo {
	Marco::Marco()
		: isKnife(false)
		, mPrevAnimation(nullptr)
		, mAnimator(nullptr)
		, mState(eMarcoState::Idle)
	{
	}
	Marco::~Marco()
	{
	}
	void Marco::Initialize()
	{
		Image* mImageR = Resources::Load<Image>(L"MarcoTopRight", L"..\\Resources\\MarcoTopRight.bmp");
		Image* mImageL = Resources::Load<Image>(L"MarcoTopLeft", L"..\\Resources\\MarcoTopLeft.bmp");
		mAnimator = AddComponent<Animator>();
		Transform* tr;
		tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 100.0f, 560.0f });
		tr->SetScale(Vector2{ 3.0f, 3.0f });
		tr->SetTopDiff(Vector2{ 0.0f, 50.0f });
		
		// Coulmn : 행	row : 열
		mAnimator->CreateAnimation(L"IdleR", mImageR, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"IdleRT", mImageR, Vector2(120.0f * 0, 120.0f * 4), 120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"IdleL", mImageL, Vector2(120.0f * 29, 120.0f * 0), -120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"IdleLT", mImageL, Vector2(120.0f * 29, 120.0f * 4), -120.0f, 30, 60, 4, Vector2::Zero, 0.15);


		mAnimator->CreateAnimation(L"ShootR", mImageR, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 30, 60, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"ShootRT", mImageR, Vector2(120.0f * 0, 120.0f * 5), 120.0f, 30, 60, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"ShootL", mImageL, Vector2(120.0f * 29, 120.0f * 1), -120.0f, 30, 60, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"ShootLT", mImageL, Vector2(120.0f * 29, 120.0f * 5), -120.0f, 30, 60, 10, Vector2::Zero, 0.07);


		mAnimator->CreateAnimation(L"KnifeR", mImageR, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"KnifeL", mImageL, Vector2(120.0f * 29, 120.0f * 3), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"MoveR", mImageR, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 30, 60, 12, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MoveL", mImageL, Vector2(120.0f * 29, 120.0f * 2), -120.0f, 30, 60, 12, Vector2::Zero, 0.05);
		
		

		
	
		

		mAnimator->GetStartEvent(L"ShootR") = std::bind(&Marco::shootStartEvent, this);
		mAnimator->GetStartEvent(L"ShootL") = std::bind(&Marco::shootStartEvent, this);
		mAnimator->GetStartEvent(L"ShootRT") = std::bind(&Marco::shootStartEvent, this);
		mAnimator->GetStartEvent(L"ShootLT") = std::bind(&Marco::shootStartEvent, this);

		mAnimator->GetCompleteEvent(L"KnifeR") = std::bind(&Marco::knifeCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"KnifeL") = std::bind(&Marco::knifeCompleteEvent, this);


		mAnimator->Play(L"IdleR", true);
		//mAnimatorL->Play(L"IdleL", true);
	
		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{60.0f, 110.0f});
		mCollider->SetLeftTop(Vector2{ -30.50f, -70.0f });
		
		GameObject::Initialize();
	}
	void Marco::Update()
	{

		switch (mState) {
		
		case mo::Marco::eMarcoState::Move:
			move();
			break;
		case mo::Marco::eMarcoState::Shoot:
			shoot();
			break;
		case mo::Marco::eMarcoState::Death:
			death();
			break;
		case mo::Marco::eMarcoState::Idle:
			idle();
			break;
		default:
			break;
		}

		GameObject::Update();
	}
	void Marco::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}

	void Marco::OnCollisionEnter(Collider* other, eLayerType otherType)
	{
		if (otherType == eLayerType::Monster)
			isKnife = true;
	}

	void Marco::OnCollisionStay(Collider* other, eLayerType otherType)
	{
		

	}

	void Marco::OnCollisionExit(Collider* other, eLayerType otherType)
	{
		if (otherType == eLayerType::Monster)
			isKnife = false;
	}

	void Marco::move()
	{

		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();
		Vector2 pos = tr->GetPos();


		// 좌우 애니메이션

		if (Input::GetKey(eKeyCode::Right)) {
			if (Input::GetKeyDown(eKeyCode::Left)) {
				if (mDirection == eDirection::Right) {
					mAnimator->Play(L"IdleR", true);
				}
				else if (mDirection == eDirection::RTop) {
					mDirection = eDirection::LTop;
					mAnimator->Play(L"IdleLT", true);
				}
			}
			if (Input::GetKeyUp(eKeyCode::Left)) {
				if (mDirection == eDirection::RTop|| mDirection == eDirection::LTop) {
					mDirection = eDirection::RTop;
					mAnimator->Play(L"IdleRT", true);
				}
				else if(mDirection == eDirection::Right || mDirection == eDirection::Left){
					mDirection = eDirection::Right;
					mAnimator->Play(L"MoveR", true);
				}

			}
			if (Input::GetKeyDown(eKeyCode::Up)) {
				mDirection = eDirection::RTop;
				mAnimator->Play(L"IdleRT", true);
			}
			if (Input::GetKeyUp(eKeyCode::Up)) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"MoveR", true);
			}
			
		}
		if (Input::GetKey(eKeyCode::Left)) {
			
			if (Input::GetKeyDown(eKeyCode::Right)) {
				if (mDirection == eDirection::Left) {
					mAnimator->Play(L"IdleL", true);
				}
				else if (mDirection == eDirection::LTop) {
					mDirection = eDirection::RTop;
					mAnimator->Play(L"IdleRT", true);
				}
			}
			if (Input::GetKeyUp(eKeyCode::Right)) {
				if (mDirection == eDirection::RTop || mDirection == eDirection::LTop) {
					mDirection = eDirection::LTop;
					mAnimator->Play(L"IdleLT", true);
				}
				else if(mDirection == eDirection::Right || mDirection == eDirection::Left){
					mDirection = eDirection::Left;
					mAnimator->Play(L"MoveL", true);
				}
			}
			if (Input::GetKeyDown(eKeyCode::Up)) {
				mDirection = eDirection::LTop;
				mAnimator->Play(L"IdleLT", true);
			}
			if (Input::GetKeyUp(eKeyCode::Up)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"MoveL", true);
			}
		}
		
		tr->SetDirection(mDirection);



		// To Idle
		if ( (Input::GetKeyNone(eKeyCode::Right)
			&& Input::GetKeyNone(eKeyCode::Left)))
		{
			if (mDirection == eDirection::Right)
				mAnimator->Play(L"IdleR", true);
			else if (mDirection == eDirection::Left)
				mAnimator->Play(L"IdleL", true);

			mState = eMarcoState::Idle;
		}



		// Shooting
		if (Input::GetKeyDown(eKeyCode::D)) {

			if (isKnife) {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"KnifeR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"KnifeL", false);
			}
			else {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"ShootR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"ShootL", false);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"ShootRT", false);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"ShootLT", false);
			}
		}


		Animator* mAnimator = GetComponent<Animator>();

		if (Input::GetKey(eKeyCode::Left))
		{
			pos.x -= 150.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::Right))
		{
			pos.x += 150.0f * Time::DeltaTime();
		}
		tr->SetPos(pos);
		

	}
	void Marco::shoot()
	{
	}
	void Marco::death()
	{
	}
	void Marco::idle()
	{

		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();

		// To move
		if (Input::GetKey(eKeyCode::Up)) {
			if (Input::GetKeyDown(eKeyCode::Right))
			{
				mDirection = eDirection::RTop;
				mAnimator->Play(L"IdleRT", true);
				mState = eMarcoState::Move;
			}
			if (Input::GetKeyDown(eKeyCode::Left))
			{
				mDirection = eDirection::LTop;
				mAnimator->Play(L"IdleLT", true);
				mState = eMarcoState::Move;
			}

		}
		else {
			if (Input::GetKeyDown(eKeyCode::Right))
			{
				mDirection = eDirection::Right;
				mAnimator->Play(L"MoveR", true);
				mState = eMarcoState::Move;
			}
			if (Input::GetKeyDown(eKeyCode::Left))
			{
				mDirection = eDirection::Left;
				mAnimator->Play(L"MoveL", true);
				mState = eMarcoState::Move;
			}
		}
		//Idle
		if (Input::GetKeyDown(eKeyCode::Up)&& (mDirection == eDirection::Right)) {
			mDirection = eDirection::RTop;
			mAnimator->Play(L"IdleRT", true);
		}
		else if (Input::GetKeyDown(eKeyCode::Up) && (mDirection == eDirection::Left)) {
			mDirection = eDirection::LTop;
			mAnimator->Play(L"IdleLT", true);
		}

		if (Input::GetKeyUp(eKeyCode::Up) && (mDirection == eDirection::RTop)) {
			mDirection = eDirection::Right;
			mAnimator->Play(L"IdleR", true);
		}
		else if (Input::GetKeyUp(eKeyCode::Up) && (mDirection == eDirection::LTop)) {
			mDirection = eDirection::Left;
			mAnimator->Play(L"IdleL", true);
		}
		tr->SetDirection(mDirection);


		// Shooting
		if (Input::GetKeyDown(eKeyCode::D)) {

			if (isKnife) {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"KnifeR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"KnifeL", false);
			}
			else {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"ShootR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"ShootL", false);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"ShootRT", false);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"ShootLT", false);
			}
		}
		
	}
	
	void Marco::shootStartEvent()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();

		Scene* curScene = SceneManager::GetActiveScene();
		BaseBullet* bullet = new BaseBullet();

		if (mDirection == eDirection::Right) {
			bullet->SetDirection(eDirection::Right);
			bullet->SetDir(Vector2{ 5.0f, 0.0f });
		}
		else if (mDirection == eDirection::Left) {
			bullet->SetDirection(eDirection::Left);
			bullet->SetDir(Vector2{ -5.0f, 0.0f });
		}
		else if (mDirection == eDirection::RTop) {
			bullet->SetDirection(eDirection::Top);
			bullet->SetDir(Vector2{ 0.0f, -5.0f });
		}
		else if (mDirection == eDirection::LTop) {
			bullet->SetDirection(eDirection::Top);
			bullet->SetDir(Vector2{ 0.0f, -5.0f });
		}		
		//Transform* tr;
		//tr = GetComponent<Transform>();
		bullet->GetComponent<Transform>()->SetPos(tr->GetPos());
		curScene->AddGameObject(bullet, eLayerType::Bullet);

	}
	void Marco::knifeCompleteEvent()
	{
		
		Animation* activeAnimation = mAnimator->GetActiveAnimation();
		Animation* prevAnimation = mAnimator->GetPrevAniamtion();

		if(activeAnimation != prevAnimation)
			mPrevAnimation = prevAnimation;

		//if(PrevAnimation!= ActiveAnimation)
		mAnimator->Play(mPrevAnimation->GetName(), true);

	}
}