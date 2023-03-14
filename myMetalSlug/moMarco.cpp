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
	Marco::Marco(MarcoBottom* obj)
		: isKnife(false)
		, mPrevAnimation(nullptr)
		, mAnimator(nullptr)
		, mState(eMarcoState::Idle)
		, bottom(obj)
	{
	}
	Marco::~Marco()
	{
	}
	void Marco::Initialize()
	{
		Image* mImageR = Resources::Load<Image>(L"MarcoTopRight", L"..\\Resources\\Player\\MarcoTopRight.bmp");
		Image* mImageL = Resources::Load<Image>(L"MarcoTopLeft", L"..\\Resources\\Player\\MarcoTopLeft.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->SetAlpha(true);
		Transform* tr;
		tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 100.0f, 560.0f });
		tr->SetScale(Vector2{ 3.0f, 3.0f });
		tr->SetTopDiff(Vector2{ 0.0f, 50.0f });
		
		// Coulmn : ��	row : ��
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

		mAnimator->CreateAnimation(L"None", mImageR, Vector2(120.0f * 29, 120.0f * 0), 120.0f, 30, 60, 1, Vector2::Zero, 1.0);



		

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
		case mo::Marco::eMarcoState::Sit:
			sit();
		default:
			break;
		}

		GameObject::Update();
	}
	void Marco::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}



	void Marco::OnCollisionEnter(Collider* other)
	{
		if ( other->GetOwner()->GetLayerType() == eLayerType::Monster)
			isKnife = true;

		if (other->GetOwner()->GetLayerType() == eLayerType::Monster) {
			mAnimator->SetUseinvincibility(true);
			bottom->GetAnimator()->SetUseinvincibility(true);
		}
	}

	void Marco::OnCollisionStay(Collider* other)
	{
	}

	void Marco::OnCollisionExit(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Monster)
			isKnife = false;

	
	
	}

	

	void Marco::move()
	{

		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();
		Vector2 pos = tr->GetPos();


		// �¿� �ִϸ��̼�

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

		// To Sit
		if (Input::GetKeyDown(eKeyCode::Down)) {
			mAnimator->Play(L"None", false);
			mState = eMarcoState::Sit;
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
			pos.x -= 180.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::Right))
		{
			pos.x += 180.0f * Time::DeltaTime();
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


		// To Sit
		if (Input::GetKeyDown(eKeyCode::Down)) {
			mAnimator->Play(L"None", false);
			mState = eMarcoState::Sit;
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
		
	}

	void Marco::sit()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();
		Vector2 pos = tr->GetPos();

		//�̵���
		if (Input::GetKey(eKeyCode::Left)) {
			pos.x -= 80.0f * Time::DeltaTime();
			mDirection = eDirection::Left;
		}
		if (Input::GetKey(eKeyCode::Right)) {
			pos.x += 80.0f * Time::DeltaTime();
			mDirection = eDirection::Right;

		}
		

		if (Input::GetKeyUp(eKeyCode::Down)) {
			if (Input::GetKey(eKeyCode::Right)) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"MoveR", true);
				mState = eMarcoState::Move;
			}
			if (Input::GetKey(eKeyCode::Left)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"MoveL", true);
				mState = eMarcoState::Move;
			}
			if (Input::GetKeyNone(eKeyCode::Right)
				&& Input::GetKeyNone(eKeyCode::Left)) {
				
				if (mDirection == eDirection::Right || mDirection == eDirection::RSit) {
					mAnimator->Play(L"IdleR", true);
					mDirection = eDirection::Right;
				}
					
				if (mDirection == eDirection::Left || mDirection == eDirection::LSit){
					mAnimator->Play(L"IdleL", true);
					mDirection = eDirection::Left;
				}
				mState = eMarcoState::Idle;
			
			}

		}		
		tr->SetPos(pos);
		tr->SetDirection(mDirection);

		// Shooting
		if (Input::GetKeyDown(eKeyCode::D)
			&& Input::GetKeyNone(eKeyCode::Right)
			&& Input::GetKeyNone(eKeyCode::Left)) {
			if (isKnife) {
				if (mDirection == eDirection::Right){
					mDirection = eDirection::RSit;	
				}
				if (mDirection == eDirection::Left) {
					mDirection = eDirection::LSit;
				}
			}
			else {
				if (mDirection == eDirection::Right){
					mDirection = eDirection::RSit;
				}
				if (mDirection == eDirection::Left){
					mDirection = eDirection::LSit;
				}
			}
			tr->SetDirection(mDirection);
			shootStartEvent();
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
		else if (mDirection == eDirection::RSit) {
			bullet->SetDirection(eDirection::RSit);
			bullet->SetDir(Vector2{ 5.0f, 0.0f });
		}
		else if (mDirection == eDirection::LSit) {
			bullet->SetDirection(eDirection::LSit);
			bullet->SetDir(Vector2{ -5.0f, 0.0f });
		}
		//Transform* tr;
		//tr = GetComponent<Transform>();
		bullet->GetComponent<Transform>()->SetPos(tr->GetPos());
		curScene->AddGameObject(bullet, eLayerType::Bullet);
		bullet->Initialize();
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