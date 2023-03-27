#include "moPistol.h"
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
	Pistol::Pistol(Marco* marco, MarcoBottom* bottom)
		: unUsedParaglider(false)
		, player(marco)
		, playerBottom(bottom)
	{
	}
	Pistol::~Pistol()
	{
	}
	void Pistol::Initialize()
	{
	/*	player = GetPlayer();
		playerBottom = GetBottom();*/


		mState = player->GetState();
		mAnimator = player->GetComponent<Animator>();
		mRigidbody = player->GetComponent<RigidBody>();
		mTransform = player->GetComponent<Transform>();

		Image* mImageR = Resources::Load<Image>(L"PistolRight", L"..\\Resources\\Player\\PistolRight.bmp");
		Image* mImageL = Resources::Load<Image>(L"PistolLeft", L"..\\Resources\\Player\\PistolLeft.bmp");

		// Coulmn : 행	row : 열
		mAnimator->CreateAnimation(L"P_IdleR", mImageR, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"P_IdleRT", mImageR, Vector2(120.0f * 0, 120.0f * 4), 120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"P_IdleL", mImageL, Vector2(120.0f * 29, 120.0f * 0), -120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"P_IdleLT", mImageL, Vector2(120.0f * 29, 120.0f * 4), -120.0f, 30, 60, 4, Vector2::Zero, 0.15);


		mAnimator->CreateAnimation(L"P_ShootR", mImageR, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 30, 60, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_ShootRT", mImageR, Vector2(120.0f * 0, 120.0f * 5), 120.0f, 30, 60, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_ShootL", mImageL, Vector2(120.0f * 29, 120.0f * 1), -120.0f, 30, 60, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_ShootLT", mImageL, Vector2(120.0f * 29, 120.0f * 5), -120.0f, 30, 60, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_ShootRB", mImageR, Vector2(120.0f * 0, 120.0f * 9), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_ShootLB", mImageL, Vector2(120.0f * 29, 120.0f * 9), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);


		mAnimator->CreateAnimation(L"P_KnifeR", mImageR, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_KnifeL", mImageL, Vector2(120.0f * 29, 120.0f * 3), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"P_MoveR", mImageR, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 30, 60, 12, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"P_MoveL", mImageL, Vector2(120.0f * 29, 120.0f * 2), -120.0f, 30, 60, 12, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"None", mImageR, Vector2(120.0f * 29, 120.0f * 0), 120.0f, 30, 60, 1, Vector2::Zero, 1.0);

		mAnimator->CreateAnimation(L"P_JumpIdleR", mImageR, Vector2(120.0f * 0, 120.0f * 6), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_JumpIdleL", mImageL, Vector2(120.0f * 29, 120.0f * 6), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"P_JumpMoveR", mImageR, Vector2(120.0f * 0, 120.0f * 7), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_JumpMoveL", mImageL, Vector2(120.0f * 29, 120.0f * 7), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"P_JumpDownR", mImageR, Vector2(120.0f * 0, 120.0f * 8), 120.0f, 30, 60, 3, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_JumpDownL", mImageL, Vector2(120.0f * 29, 120.0f * 8), -120.0f, 30, 60, 3, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"P_paraglider", mImageR, Vector2(120.0f * 0, 120.0f * 6), 120.0f, 30, 60, 6, Vector2::Zero, 0.05);


		/*mAnimator->GetStartEvent(L"KnifeR") = std::bind(&Pistol::AttackEndEvent, this);
		mAnimator->GetStartEvent(L"KnifeL") = std::bind(&Pistol::AttackEndEvent, this);*/
		mAnimator->GetStartEvent(L"P_ShootR") = std::bind(&Pistol::shootStartEvent, this);
		mAnimator->GetStartEvent(L"P_ShootL") = std::bind(&Pistol::shootStartEvent, this);
		mAnimator->GetStartEvent(L"P_ShootRT") = std::bind(&Pistol::shootStartEvent, this);
		mAnimator->GetStartEvent(L"P_ShootLT") = std::bind(&Pistol::shootStartEvent, this);
		mAnimator->GetStartEvent(L"P_ShootRB") = std::bind(&Pistol::shootStartEvent, this);
		mAnimator->GetStartEvent(L"P_ShootLB") = std::bind(&Pistol::shootStartEvent, this);


		/*	mAnimator->GetCompleteEvent(L"KnifeR") = std::bind(&Pistol::AttackEndEvent, this);
			mAnimator->GetCompleteEvent(L"KnifeL") = std::bind(&Pistol::AttackEndEvent, this);*/
		mAnimator->GetCompleteEvent(L"P_ShootR") = std::bind(&Pistol::AttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_ShootL") = std::bind(&Pistol::AttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_ShootRT") = std::bind(&Pistol::AttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_ShootLT") = std::bind(&Pistol::AttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_ShootRB") = std::bind(&Pistol::AttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_ShootLB") = std::bind(&Pistol::AttackEndEvent, this);

		mAnimator->Play(L"P_paraglider", false);
	}
	void Pistol::Update()
	{
		mState = player->GetState();

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
			break;

		default:
			break;
		}

		player->SetState(mState);
	}

	void Pistol::paraglider()
	{

		if (unUsedParaglider == false) {
			if (Input::GetKeyDown(eKeyCode::S)) {
				unUsedParaglider = true;
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y -= 300.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);
				mRigidbody->SetGravity(Vector2(0.0f, 1500.0f));
			}
		}
		if (mRigidbody->GetGround()) {
			mAnimator->Play(L"P_IdleR", true);
			playerBottom->SetIsGround(true);
			mRigidbody->SetGravity(Vector2(0.0f, 1500.0f));
			mState = Marco::eMarcoState::Idle;
		}
	}

	void Pistol::move()
	{
		Vector2 pos = mTransform->GetPos();
		eDirection mDirection = mTransform->GetDirection();

		// 좌우 애니메이션

		if (Input::GetKey(eKeyCode::Right)) {
			if (Input::GetKeyDown(eKeyCode::Left)) {
				if (mDirection == eDirection::Right) {
					mAnimator->Play(L"P_IdleR", true);
				}
				else if (mDirection == eDirection::RTop) {
					mDirection = eDirection::LTop;
					mAnimator->Play(L"P_IdleLT", true);
				}
			}
			if (Input::GetKeyUp(eKeyCode::Left)) {
				if (mDirection == eDirection::RTop || mDirection == eDirection::LTop) {
					mDirection = eDirection::RTop;
					mAnimator->Play(L"P_IdleRT", true);
				}
				else if (mDirection == eDirection::Right || mDirection == eDirection::Left) {
					mDirection = eDirection::Right;
					mAnimator->Play(L"P_MoveR", true);
				}

			}
			if (Input::GetKeyDown(eKeyCode::Up)) {
				mDirection = eDirection::RTop;
				mAnimator->Play(L"P_IdleRT", true);
			}
			if (Input::GetKeyUp(eKeyCode::Up)) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"P_MoveR", true);
			}

		}
		if (Input::GetKey(eKeyCode::Left)) {

			if (Input::GetKeyDown(eKeyCode::Right)) {
				if (mDirection == eDirection::Left) {
					mAnimator->Play(L"P_IdleL", true);
				}
				else if (mDirection == eDirection::LTop) {
					mDirection = eDirection::RTop;
					mAnimator->Play(L"P_IdleRT", true);
				}
			}
			if (Input::GetKeyUp(eKeyCode::Right)) {
				if (mDirection == eDirection::RTop || mDirection == eDirection::LTop) {
					mDirection = eDirection::LTop;
					mAnimator->Play(L"P_IdleLT", true);
				}
				else if (mDirection == eDirection::Right || mDirection == eDirection::Left) {
					mDirection = eDirection::Left;
					mAnimator->Play(L"P_MoveL", true);
				}
			}
			if (Input::GetKeyDown(eKeyCode::Up)) {
				mDirection = eDirection::LTop;
				mAnimator->Play(L"P_IdleLT", true);
			}
			if (Input::GetKeyUp(eKeyCode::Up)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"P_MoveL", true);
			}
		}

		if (Input::GetKeyNone(eKeyCode::Right))
			if (Input::GetKeyDown(eKeyCode::Left)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"P_MoveL", true);
			}
		if (Input::GetKeyNone(eKeyCode::Left))
			if (Input::GetKeyDown(eKeyCode::Right)) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"P_MoveR", true);
			}


		

		// To Idle
		if ((Input::GetKeyNone(eKeyCode::Right)
			&& Input::GetKeyNone(eKeyCode::Left)))
		{
			if (mDirection == eDirection::Right)
				mAnimator->Play(L"P_IdleR", true);
			else if (mDirection == eDirection::Left)
				mAnimator->Play(L"P_IdleL", true);

			mState = Marco::eMarcoState::Idle;
		}

		// To Sit
		if (Input::GetKeyDown(eKeyCode::Down)) {
			mAnimator->Play(L"None", false);
			mState = Marco::eMarcoState::Sit;
		}

		//Junp
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (Input::GetKey(eKeyCode::Down)) {
				if (mDirection == eDirection::Right) {
					mDirection = eDirection::RBottom;
					mAnimator->Play(L"P_JumpDownR", false);
				}
				else if (mDirection == eDirection::Left) {
					mDirection = eDirection::LBottom;
					mAnimator->Play(L"P_JumpDownL", false);
				}
			}
			else {
				if (Input::GetKey(eKeyCode::Right))
					mAnimator->Play(L"P_JumpMoveR", false);
				else if (Input::GetKey(eKeyCode::Left))
					mAnimator->Play(L"P_JumpMoveL", false);
			}

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 700.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mState = Marco::eMarcoState::Jump;
		}
		// Shooting
		if (Input::GetKeyDown(eKeyCode::D)) {

			/*if (isKnife) {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"KnifeR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"KnifeL", false);
			}*/
			//else {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_ShootR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_ShootL", false);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"P_ShootRT", false);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"P_ShootLT", false);
			//}
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
		mTransform->SetDirection(mDirection);
		mTransform->SetPos(pos);
	}

	void Pistol::shoot()
	{
	}

	void Pistol::death()
	{
	}

	void Pistol::idle()
	{

		eDirection mDirection = mTransform->GetDirection();


		// To move
		if (Input::GetKey(eKeyCode::Up)) {
			if (Input::GetKeyDown(eKeyCode::Right))
			{
				mDirection = eDirection::RTop;
				mAnimator->Play(L"P_IdleRT", true);
				mState = Marco::eMarcoState::Move;
			}
			if (Input::GetKeyDown(eKeyCode::Left))
			{
				mDirection = eDirection::LTop;
				mAnimator->Play(L"P_IdleLT", true);
				mState = Marco::eMarcoState::Move;
			}

		}
		else {
			if (Input::GetKey(eKeyCode::Right))
			{
				mDirection = eDirection::Right;
				mAnimator->Play(L"P_MoveR", true);
				mState = Marco::eMarcoState::Move;
			}
			if (Input::GetKey(eKeyCode::Left))
			{
				mDirection = eDirection::Left;
				mAnimator->Play(L"P_MoveL", true);
				mState = Marco::eMarcoState::Move;
			}
		}


		//Idle
		if (Input::GetKeyDown(eKeyCode::Up) && (mDirection == eDirection::Right)) {
			mDirection = eDirection::RTop;
			mAnimator->Play(L"P_IdleRT", true);
		}
		else if (Input::GetKeyDown(eKeyCode::Up) && (mDirection == eDirection::Left)) {
			mDirection = eDirection::LTop;
			mAnimator->Play(L"P_IdleLT", true);
		}

		if (Input::GetKeyUp(eKeyCode::Up) && (mDirection == eDirection::RTop)) {
			mDirection = eDirection::Right;
			mAnimator->Play(L"P_IdleR", true);
		}
		else if (Input::GetKeyUp(eKeyCode::Up) && (mDirection == eDirection::LTop)) {
			mDirection = eDirection::Left;
			mAnimator->Play(L"P_IdleL", true);
		}
		mTransform->SetDirection(mDirection);


		// To Sit
		if (Input::GetKeyDown(eKeyCode::Down)) {
			mAnimator->Play(L"None", false);
			mState = Marco::eMarcoState::Sit;
		}

		//Junp
		if (Input::GetKeyDown(eKeyCode::S))
		{	
			if (Input::GetKey(eKeyCode::Down)) {
				if (mDirection == eDirection::Right) {
					mDirection = eDirection::RBottom;
					mAnimator->Play(L"P_JumpDownR", false);
				}
				if (mDirection == eDirection::Left) {
					mDirection = eDirection::LBottom;
					mAnimator->Play(L"P_JumpDownL", false);
				}
			}
			else {
				if (mDirection == eDirection::Right || mDirection == eDirection::RTop)
					mAnimator->Play(L"P_JumpIdleR", false);
				if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
					mAnimator->Play(L"P_JumpIdleL", false);
			}

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 700.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mState = Marco::eMarcoState::Jump;
		}


		// Shooting
		if (Input::GetKeyDown(eKeyCode::D)) {

		/*	if (isKnife) {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"KnifeR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"KnifeL", false);
			}
			else {*/
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_ShootR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_ShootL", false);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"P_ShootRT", false);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"P_ShootLT", false);
			//}
		}

	}

	void Pistol::sit()
	{
	
		eDirection mDirection = mTransform->GetDirection();
		Vector2 pos = mTransform->GetPos();

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
				mAnimator->Play(L"P_MoveR", true);
				mState = Marco::eMarcoState::Move;
			}
			if (Input::GetKey(eKeyCode::Left)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"P_MoveL", true);
				mState = Marco::eMarcoState::Move;
			}
			if (Input::GetKeyNone(eKeyCode::Right)
				&& Input::GetKeyNone(eKeyCode::Left)) {

				if (mDirection == eDirection::Right || mDirection == eDirection::RSit) {
					mAnimator->Play(L"P_IdleR", true);
					mDirection = eDirection::Right;
				}

				if (mDirection == eDirection::Left || mDirection == eDirection::LSit) {
					mAnimator->Play(L"P_IdleL", true);
					mDirection = eDirection::Left;
				}
				mState = Marco::eMarcoState::Idle;

			}

		}
		mTransform->SetPos(pos);
		mTransform->SetDirection(mDirection);

		//Junp
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDirection == eDirection::Right) {
				mDirection = eDirection::RBottom;
				mAnimator->Play(L"P_JumpDownR", false);
			}
			if (mDirection == eDirection::Left) {
				mDirection = eDirection::LBottom;
				mAnimator->Play(L"P_JumpDownL", false);
			}
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 700.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mTransform->SetDirection(mDirection);
			mState = Marco::eMarcoState::Jump;
		}


		// Shooting
		if (Input::GetKeyDown(eKeyCode::D)
			&& Input::GetKeyNone(eKeyCode::Right)
			&& Input::GetKeyNone(eKeyCode::Left)) {
			/*if (isKnife) {
				if (mDirection == eDirection::Right) {
					mDirection = eDirection::RSit;
				}
				if (mDirection == eDirection::Left) {
					mDirection = eDirection::LSit;
				}
			}
			else {*/
				if (mDirection == eDirection::Right) {
					mDirection = eDirection::RSit;
				}
				if (mDirection == eDirection::Left) {
					mDirection = eDirection::LSit;
				}
			//}
			mTransform->SetDirection(mDirection);
			shootStartEvent();
		}



	}

	void Pistol::jump()
	{
		
		eDirection mDirection = mTransform->GetDirection();
		Vector2 pos = mTransform->GetPos();


		//Junp
		if (mRigidbody->GetGround())
		{
			
			if (Input::GetKey(eKeyCode::Left))
			{
				if (mDirection == eDirection::LTop) {
					//mDirection = eDirection::LTop;
					mAnimator->Play(L"P_IdleLT", true);
				}
				else {
					mDirection == eDirection::Left;
					mAnimator->Play(L"P_MoveL", true);
				}

			}

			if (Input::GetKey(eKeyCode::Right))
			{
				if (mDirection == eDirection::RTop) {
					//mDirection = eDirection::RTop;
					mAnimator->Play(L"P_IdleRT", true);
				}
				else {
					mDirection = eDirection::Right;
					mAnimator->Play(L"P_MoveR", true);
				}

			}
			playerBottom->SetIsGround(true);
			mState = Marco::eMarcoState::Move;
			

		}

		if (Input::GetKeyDown(eKeyCode::Down)) {
			if (mDirection == eDirection::Right) {
				mDirection = eDirection::RBottom;
				mAnimator->Play(L"P_JumpDownR", false);
			}
			if (mDirection == eDirection::Left) {
				mDirection = eDirection::LBottom;
				mAnimator->Play(L"P_JumpDownL", false);
			}
		}

		if (Input::GetKeyUp(eKeyCode::Down)) {
			if (mDirection == eDirection::RBottom) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"P_JumpIdleR", false);
			}
			if (mDirection == eDirection::LBottom) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"P_JumpIdleL", false);
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

			//if (isKnife) {
			//	if (mDirection == eDirection::Right)
			//		mAnimator->Play(L"KnifeR", false);
			//	else if (mDirection == eDirection::Left)
			//		mAnimator->Play(L"KnifeL", false);
			//}
			//else {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_ShootR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_ShootL", false);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"P_ShootRT", false);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"P_ShootLT", false);
				else if (mDirection == eDirection::RBottom)
					mAnimator->Play(L"P_ShootRB", false);
				else if (mDirection == eDirection::LBottom)
					mAnimator->Play(L"P_ShootLB", false);
			//}
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

		mTransform->SetPos(pos);
		mTransform->SetDirection(mDirection);

	}

	void Pistol::shootStartEvent()
	{
	
		eDirection mDirection = mTransform->GetDirection();

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

		//카메라 좌표
		//bullet->GetComponent<Transform>()->SetPos(Camera::CaluatePos(tr->GetPos()));
		bullet->GetComponent<Transform>()->SetPos(mTransform->GetPos());
		curScene->AddGameObject(bullet, eLayerType::Bullet);
		bullet->Initialize();

		Animation* activeAnimation = mAnimator->GetActiveAnimation();
		Animation* prevAnimation = mAnimator->GetPrevAniamtion();

		if (prevAnimation->GetName() != L"P_ShootR" &&
			prevAnimation->GetName() != L"P_ShootRT" &&
			prevAnimation->GetName() != L"P_ShootL" &&
			prevAnimation->GetName() != L"P_ShootLT" &&
			prevAnimation->GetName() != L"P_ShootRB" &&
			prevAnimation->GetName() != L"P_ShootLB" )
				mPrevAnimation = prevAnimation;

		//if(activeAnimation->GetName() != L"P_")

	}


	void Pistol::AttackEndEvent()
	{
		mAnimator->Play(mPrevAnimation->GetName(), true);
	}


}