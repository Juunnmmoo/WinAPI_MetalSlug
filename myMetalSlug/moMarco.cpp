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
#include "moCamera.h"
#include "moRigidBody.h"
#include "moApplication.h"

extern mo::Application application;

namespace mo {
	Marco::Marco(MarcoBottom* obj)
		: isKnife(false)
		, mPrevAnimation(nullptr)
		, mAnimator(nullptr)
		, mState(eMarcoState::Paraglider)
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
		tr->SetPos(Vector2{ 300.0f, 200.0f });
		tr->SetScale(Vector2{ 3.0f, 3.0f });
		tr->SetDisToBottom(Vector2{ 0.0f, 50.0f });

		Transform* bottomTr;
		bottomTr = bottom->GetComponent<Transform>();
		bottomTr->SetPos(tr->GetPos() + Vector2(0.0f, 40.0f));
		bottomTr->SetScale(Vector2{ 3.0f, 3.0f });
		bottomTr->SetDisToBottom(Vector2{ 0.0f, 50.0f });

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 60.0f, 110.0f });
		mCollider->SetLeftTop(Vector2{ -30.50f, -70.0f });

		mRigidbody = AddComponent<RigidBody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2(0.0f, 250.0f));

		/*bottomRigidBody = bottom->AddComponent<RigidBody>();
		bottomRigidBody->SetMass(1.0f);*/


		// Coulmn : 행	row : 열
		mAnimator->CreateAnimation(L"IdleR", mImageR, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"IdleRT", mImageR, Vector2(120.0f * 0, 120.0f * 4), 120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"IdleL", mImageL, Vector2(120.0f * 29, 120.0f * 0), -120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"IdleLT", mImageL, Vector2(120.0f * 29, 120.0f * 4), -120.0f, 30, 60, 4, Vector2::Zero, 0.15);


		mAnimator->CreateAnimation(L"ShootR", mImageR, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 30, 60, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"ShootRT", mImageR, Vector2(120.0f * 0, 120.0f * 5), 120.0f, 30, 60, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"ShootL", mImageL, Vector2(120.0f * 29, 120.0f * 1), -120.0f, 30, 60, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"ShootLT", mImageL, Vector2(120.0f * 29, 120.0f * 5), -120.0f, 30, 60, 10, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"ShootRB", mImageR, Vector2(120.0f * 0, 120.0f * 9), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"ShootLB", mImageL, Vector2(120.0f * 29, 120.0f * 9), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);

		
		mAnimator->CreateAnimation(L"KnifeR", mImageR, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"KnifeL", mImageL, Vector2(120.0f * 29, 120.0f * 3), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"MoveR", mImageR, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 30, 60, 12, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MoveL", mImageL, Vector2(120.0f * 29, 120.0f * 2), -120.0f, 30, 60, 12, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"None", mImageR, Vector2(120.0f * 29, 120.0f * 0), 120.0f, 30, 60, 1, Vector2::Zero, 1.0);

		mAnimator->CreateAnimation(L"JumpIdleR", mImageR, Vector2(120.0f * 0, 120.0f * 6), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"JumpIdleL", mImageL, Vector2(120.0f * 29, 120.0f * 6), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"JumpMoveR", mImageR, Vector2(120.0f * 0, 120.0f * 7), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"JumpMoveL", mImageL, Vector2(120.0f * 29, 120.0f * 7), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		
		mAnimator->CreateAnimation(L"JumpDownR", mImageR, Vector2(120.0f * 0, 120.0f * 8), 120.0f, 30, 60, 3, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"JumpDownL", mImageL, Vector2(120.0f * 29, 120.0f * 8), -120.0f, 30, 60, 3, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"paraglider", mImageR, Vector2(120.0f * 0, 120.0f * 6), 120.0f, 30, 60, 6, Vector2::Zero, 0.05);
		


		mAnimator->GetStartEvent(L"ShootR") = std::bind(&Marco::shootStartEvent, this);
		mAnimator->GetStartEvent(L"ShootL") = std::bind(&Marco::shootStartEvent, this);
		mAnimator->GetStartEvent(L"ShootRT") = std::bind(&Marco::shootStartEvent, this);
		mAnimator->GetStartEvent(L"ShootLT") = std::bind(&Marco::shootStartEvent, this);
		mAnimator->GetStartEvent(L"ShootRB") = std::bind(&Marco::shootStartEvent, this);
		mAnimator->GetStartEvent(L"ShootLB") = std::bind(&Marco::shootStartEvent, this);

		mAnimator->GetCompleteEvent(L"KnifeR") = std::bind(&Marco::knifeCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"KnifeL") = std::bind(&Marco::knifeCompleteEvent, this);


		mAnimator->Play(L"paraglider", false);
		//mAnimatorL->Play(L"IdleL", true);
	
		


		GameObject::Initialize();
	}
	void Marco::Update()
	{

		switch (mState) {
		case mo::Marco::eMarcoState::Paraglider:
			paraglider();
			break;
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
			break;
		case mo::Marco::eMarcoState::Jump:
			jump();
		default:
			break;
		}

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Vector2 caPos = Camera::CaluatePos(pos);

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

	

	void Marco::paraglider()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Transform* bottomTr;
		bottomTr = bottom->GetComponent<Transform>();
		bottomTr->SetPos(tr->GetPos() + Vector2(0.0f, 40.0f));

		if (isKnife == false) {
			if (Input::GetKeyDown(eKeyCode::S)) {
				isKnife = true;
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y -= 300.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);
				mRigidbody->SetGravity(Vector2(0.0f, 1500.0f));
			}
		}
		if (mRigidbody->GetGround()) {
			mAnimator->Play(L"IdleR", true);
			bottom->SetIsGround(true);
			isKnife = false;
			mRigidbody->SetGravity(Vector2(0.0f, 1500.0f));
			mState = eMarcoState::Idle;
		}
		
	}

	void Marco::move()
	{

		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();
		Vector2 pos = tr->GetPos();

		Transform* bottomTr;
		bottomTr = bottom->GetComponent<Transform>();
		
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
		
		if (Input::GetKeyNone(eKeyCode::Right))
			if (Input::GetKeyDown(eKeyCode::Left)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"MoveL", true);
			}
		if (Input::GetKeyNone(eKeyCode::Left))
			if (Input::GetKeyDown(eKeyCode::Right)) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"MoveR", true);
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

		//Junp
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (Input::GetKey(eKeyCode::Right))
				mAnimator->Play(L"JumpMoveR", false);
			if (Input::GetKey(eKeyCode::Left))
				mAnimator->Play(L"JumpMoveL", false);

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 700.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mState = eMarcoState::Jump;
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

		if (Input::GetKey(eKeyCode::Left)
			&& Camera::GetDistance().x < pos.x - 30.0f)
		{
			pos.x -= 250.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::Right)
			&& Camera::GetDistance().x + application.GetWidth() > pos.x + 30.0f)
		{
			pos.x += 250.0f * Time::DeltaTime();
		}
		tr->SetPos(pos);
		bottomTr->SetPos(tr->GetPos() + Vector2(0.0f, 40.0f));


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

		Transform* bottomTr;
		bottomTr = bottom->GetComponent<Transform>();

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
			if (Input::GetKey(eKeyCode::Right))
			{
				mDirection = eDirection::Right;
				mAnimator->Play(L"MoveR", true);
				mState = eMarcoState::Move;
			}
			if (Input::GetKey(eKeyCode::Left))
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
		bottomTr->SetPos(tr->GetPos() + Vector2(0.0f, 40.0f));


		// To Sit
		if (Input::GetKeyDown(eKeyCode::Down)) {
			mAnimator->Play(L"None", false);
			mState = eMarcoState::Sit;
		}
		
		//Junp
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDirection == eDirection::Right || mDirection == eDirection::RTop)
				mAnimator->Play(L"JumpIdleR", false);
			if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
				mAnimator->Play(L"JumpIdleL", false);

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 700.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mState = eMarcoState::Jump;
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

		Transform* bottomTr;
		bottomTr = bottom->GetComponent<Transform>();

		

		//이동중
		if (Input::GetKey(eKeyCode::Left)
			&& Camera::GetDistance().x < pos.x - 30.0f) 
		{
			pos.x -= 80.0f * Time::DeltaTime();
			mDirection = eDirection::Left;
		}
		if (Input::GetKey(eKeyCode::Right)
			&& Camera::GetDistance().x + application.GetWidth() > pos.x + 30.0f) 
		{
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
		bottomTr->SetPos(tr->GetPos() + Vector2(0.0f, 40.0f));

		//Junp
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDirection == eDirection::Right){
				mDirection = eDirection::RBottom;
				mAnimator->Play(L"JumpDownR", false);
			}
			if (mDirection == eDirection::Left) {
				mDirection = eDirection::LBottom;
				mAnimator->Play(L"JumpDownL", false);
			}
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 700.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			tr->SetDirection(mDirection);
			mState = eMarcoState::Jump;
		}
	

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

	void Marco::jump()
	{

		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();
		Vector2 pos = tr->GetPos();

		Transform* bottomTr;
		bottomTr = bottom->GetComponent<Transform>();

		//Junp
		if (mRigidbody->GetGround())
		{
			//if (Input::GetKey(eKeyCode::Down)) {
			//	// To Sit
			//	 
			//		mAnimator->Play(L"None", false);
			//		mState = eMarcoState::Sit;
			//	
			//}
			
				if (Input::GetKey(eKeyCode::Left))
				{
					if (mDirection == eDirection::LTop) {
						mDirection == eDirection::LTop;
						mAnimator->Play(L"IdleLT", true);
					}
					else {
						mDirection == eDirection::Left;
						mAnimator->Play(L"MoveL", true);
					}
					
				}

				if (Input::GetKey(eKeyCode::Right))
				{
					if (mDirection == eDirection::RTop) {
						mDirection == eDirection::RTop;
						mAnimator->Play(L"IdleRT", true);
					}
					else {
						mDirection = eDirection::Right;				
						mAnimator->Play(L"MoveR", true);
					}
					
				}
				bottom->SetIsGround(true);
				mState = eMarcoState::Move;
			
		}

		if (Input::GetKeyDown(eKeyCode::Down)) {
			if (mDirection == eDirection::Right) {
				mDirection = eDirection::RBottom;
				mAnimator->Play(L"JumpDownR", false);
			}
			if (mDirection == eDirection::Left){
				mDirection = eDirection::LBottom;
				mAnimator->Play(L"JumpDownL", false);
			}
		}

		if (Input::GetKeyUp(eKeyCode::Down)) {
			if (mDirection == eDirection::RBottom){
				mDirection = eDirection::Right;
				mAnimator->Play(L"JumpIdleR", false);
			}
			if (mDirection == eDirection::LBottom) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"JumpIdleL", false);
			}
		}


		if (Input::GetKey(eKeyCode::Right)) {
			
			if (Input::GetKeyUp(eKeyCode::Left)) {
				if (mDirection == eDirection::RTop || mDirection == eDirection::LTop) {
					mDirection = eDirection::RTop;
				}
				else if (mDirection == eDirection::Right || mDirection == eDirection::Left) {
					mDirection = eDirection::Right;
				}
			}
			if (Input::GetKeyDown(eKeyCode::Up)) {
				mDirection = eDirection::RTop;
			}
			if (Input::GetKeyUp(eKeyCode::Up)) {
				mDirection = eDirection::Right;
			}

		}
		if (Input::GetKey(eKeyCode::Left)) {
			if (Input::GetKeyUp(eKeyCode::Right)) {
				if (mDirection == eDirection::RTop || mDirection == eDirection::LTop) {
					mDirection = eDirection::LTop;
				}
				else if (mDirection == eDirection::Right || mDirection == eDirection::Left) {
					mDirection = eDirection::Left;
				}
			}
			if (Input::GetKeyDown(eKeyCode::Up)) {
				mDirection = eDirection::LTop;
			}
			if (Input::GetKeyUp(eKeyCode::Up)) {
				mDirection = eDirection::Left;
			}
		}

		if (Input::GetKeyNone(eKeyCode::Right))
			if (Input::GetKeyDown(eKeyCode::Left)) {
				mDirection = eDirection::Left;
			}
		if (Input::GetKeyNone(eKeyCode::Left))
			if (Input::GetKeyDown(eKeyCode::Right)) {
				mDirection = eDirection::Right;
			}

		if (Input::GetKeyNone(eKeyCode::Right)
			&& Input::GetKeyNone(eKeyCode::Left)) 
		{
			if (Input::GetKeyDown(eKeyCode::Up))
			{
				if (mDirection == eDirection::Left)
					mDirection = eDirection::LTop;
				if (mDirection == eDirection::Right)
					mDirection = eDirection::RTop;

			
			}
			if (Input::GetKeyUp(eKeyCode::Up))
			{
				if (mDirection == eDirection::LTop)
					mDirection = eDirection::Left;
				if (mDirection == eDirection::RTop)
					mDirection = eDirection::Right;

			}
			
		}
			
		
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
				else if (mDirection == eDirection::RBottom)
					mAnimator->Play(L"ShootRB", false);
				else if (mDirection == eDirection::LBottom)
					mAnimator->Play(L"ShootLB", false);
			}
		}




		if (Input::GetKey(eKeyCode::Left)
			&& Camera::GetDistance().x < pos.x - 30.0f)
		{
			pos.x -= 250.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::Right)
			&& Camera::GetDistance().x + application.GetWidth() > pos.x + 30.0f)
		{
			pos.x += 250.0f * Time::DeltaTime();
		}

		tr->SetPos(pos);
		tr->SetDirection(mDirection);
		bottomTr->SetPos(tr->GetPos() + Vector2(0.0f, 40.0f));

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
		else if (mDirection == eDirection::RBottom) {
			bullet->SetDirection(eDirection::Bottom);
			bullet->SetDir(Vector2{ 0.0f, 5.0f });
		}
		else if (mDirection == eDirection::LBottom) {
			bullet->SetDirection(eDirection::Bottom);
			bullet->SetDir(Vector2{ 0.0f, 5.0f });
		}
		//Transform* tr;
		//tr = GetComponent<Transform>();
		
		//카메라 좌표
		//bullet->GetComponent<Transform>()->SetPos(Camera::CaluatePos(tr->GetPos()));
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