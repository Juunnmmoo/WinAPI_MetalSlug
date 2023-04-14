#include "moMachinegun.h"
#include "moMarco.h"
#include "moImage.h"
#include "moSceneManager.h"
#include "moResources.h"
#include "moTransform.h"
#include "moInput.h"
#include "moTime.h"
#include "moAnimator.h"
#include "Collider.h"
#include "moPistolBullet.h"
#include "moScene.h"
#include "moCamera.h"
#include "moRigidBody.h"
#include "moApplication.h"
#include "moPlayerBomb.h"
#include "moMachinegunBullet.h"

extern mo::Application application;

namespace mo {
	Machinegun::Machinegun(Marco* marco, MarcoBottom* bottom)
		: unUsedParaglider(false)
		, player(marco)
		, playerBottom(bottom)
		, isShooting (false)
	{
	}
	Machinegun::~Machinegun()
	{
	}
	void Machinegun::Initialize()
	{
		/*	player = GetPlayer();
			playerBottom = GetBottom();*/


		mState = player->GetMarcoState();
		mAnimator = player->GetComponent<Animator>();
		mRigidbody = player->GetComponent<RigidBody>();
		mTransform = player->GetComponent<Transform>();

		
		Image* mImageR = Resources::Load<Image>(L"RipleRight", L"..\\Resources\\Player\\RipleRight.bmp");
		Image* mImageL = Resources::Load<Image>(L"RipleLeft", L"..\\Resources\\Player\\RipleLeft.bmp");

		// Coulmn : 행	row : 열
		//mAnimator->CreateAnimation(L"IdleR", mImageR, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"M_IdleR", mImageR, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 30, 60, 4, Vector2::Zero, 0.15); 
		mAnimator->CreateAnimation(L"M_IdleRT", mImageR, Vector2(120.0f * 0, 120.0f * 5), 120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"M_IdleL", mImageL, Vector2(120.0f * 29, 120.0f * 0), -120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"M_IdleLT", mImageL, Vector2(120.0f * 29, 120.0f * 5), -120.0f, 30, 60, 4, Vector2::Zero, 0.15);


		//mAnimator->CreateAnimation(L"ShootR", mImageR, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 30, 60, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_ShootR", mImageR, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 30, 60, 4, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_ShootRT", mImageR, Vector2(120.0f * 0, 120.0f * 6), 120.0f, 30, 60, 4, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_ShootL", mImageL, Vector2(120.0f * 29, 120.0f * 1), -120.0f, 30, 60, 4, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_ShootLT", mImageL, Vector2(120.0f * 29, 120.0f * 6), -120.0f, 30, 60, 4, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_ShootRB", mImageR, Vector2(120.0f * 0, 120.0f * 8), 120.0f, 30, 60, 4, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_ShootLB", mImageL, Vector2(120.0f * 29, 120.0f * 8), -120.0f, 30, 60, 4, Vector2::Zero, 0.07);


		mAnimator->CreateAnimation(L"M_KnifeR", mImageR, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 30, 60, 6, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"M_KnifeL", mImageL, Vector2(120.0f * 29, 120.0f * 3), -120.0f, 30, 60, 6, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"M_MoveR", mImageR, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 30, 60, 12, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"M_MoveL", mImageL, Vector2(120.0f * 29, 120.0f * 2), -120.0f, 30, 60, 12, Vector2::Zero, 0.05);

		//mAnimator->CreateAnimation(L"M_None", mImageR, Vector2(120.0f * 29, 120.0f * 0), 120.0f, 30, 60, 1, Vector2::Zero, 1.0);

		mAnimator->CreateAnimation(L"M_JumpIdleR", mImageR, Vector2(120.0f * 0, 120.0f * 9), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_JumpIdleL", mImageL, Vector2(120.0f * 29, 120.0f * 9), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"M_JumpMoveR", mImageR, Vector2(120.0f * 0, 120.0f * 10), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_JumpMoveL", mImageL, Vector2(120.0f * 29, 120.0f * 10), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);

		//mAnimator->CreateAnimation(L"M_JumpDownR", test, Vector2(120.0f * 0, 120.0f * 7), 120.0f, 30, 60, 3, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_JumpDownR", mImageR, Vector2(120.0f * 0, 120.0f * 11), 120.0f, 30, 60, 7, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_JumpDownL", mImageL, Vector2(120.0f * 29, 120.0f * 11), -120.0f, 30, 60, 7, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"M_ThrowingBombR", mImageR, Vector2(120.0f * 0, 120.0f * 12), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_ThrowingBombL", mImageL, Vector2(120.0f * 29, 120.0f * 12), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"M_ShootR_RT", mImageR, Vector2(120.0f * 0, 120.0f * 13), 120.0f, 30, 60, 2, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_ShootR_TR", mImageR, Vector2(120.0f * 0, 120.0f * 14), 120.0f, 30, 60, 2, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_ShootR_RB", mImageR, Vector2(120.0f * 0, 120.0f * 15), 120.0f, 30, 60, 2, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_ShootR_BR", mImageR, Vector2(120.0f * 0, 120.0f * 16), 120.0f, 30, 60, 2, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_ShootR_LT", mImageL, Vector2(120.0f * 29, 120.0f * 13), -120.0f, 30, 60, 2, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_ShootR_TL", mImageL, Vector2(120.0f * 29, 120.0f * 14), -120.0f, 30, 60, 2, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_ShootR_LB", mImageL, Vector2(120.0f * 29, 120.0f * 15), -120.0f, 30, 60, 2, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_ShootR_BL", mImageL, Vector2(120.0f * 29, 120.0f * 16), -120.0f, 30, 60, 2, Vector2::Zero, 0.07);


		mAnimator->GetStartEvent(L"M_ThrowingBombR") = std::bind(&Machinegun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"M_ThrowingBombL") = std::bind(&Machinegun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"M_KnifeR") = std::bind(&Machinegun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"M_KnifeL") = std::bind(&Machinegun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootR") = std::bind(&Machinegun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootL") = std::bind(&Machinegun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootRT") = std::bind(&Machinegun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootLT") = std::bind(&Machinegun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootRB") = std::bind(&Machinegun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootLB") = std::bind(&Machinegun::shootStartEvent, this);

		mAnimator->GetCompleteEvent(L"M_ThrowingBombR") = std::bind(&Machinegun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"M_ThrowingBombL") = std::bind(&Machinegun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"M_KnifeR") = std::bind(&Machinegun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"M_KnifeL") = std::bind(&Machinegun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootR") = std::bind(&Machinegun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootL") = std::bind(&Machinegun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootRT") = std::bind(&Machinegun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootLT") = std::bind(&Machinegun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootRB") = std::bind(&Machinegun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootLB") = std::bind(&Machinegun::attackCompleteEvent, this);

		mAnimator->GetEndEvent(L"M_ThrowingBombR") = std::bind(&Machinegun::attackEndEvent, this);
		mAnimator->GetEndEvent(L"M_ThrowingBombL") = std::bind(&Machinegun::attackEndEvent, this);
		mAnimator->GetEndEvent(L"M_KnifeR") = std::bind(&Machinegun::attackEndEvent, this);
		mAnimator->GetEndEvent(L"M_KnifeL") = std::bind(&Machinegun::attackEndEvent, this);
		mAnimator->GetEndEvent(L"M_ShootR") = std::bind(&Machinegun::attackEndEvent, this);
		mAnimator->GetEndEvent(L"M_ShootL") = std::bind(&Machinegun::attackEndEvent, this);
		mAnimator->GetEndEvent(L"M_ShootRT") = std::bind(&Machinegun::attackEndEvent, this);
		mAnimator->GetEndEvent(L"M_ShootLT") = std::bind(&Machinegun::attackEndEvent, this);
		mAnimator->GetEndEvent(L"M_ShootRB") = std::bind(&Machinegun::attackEndEvent, this);
		mAnimator->GetEndEvent(L"M_ShootLB") = std::bind(&Machinegun::attackEndEvent, this);

		mAnimator->GetStartEvent(L"M_ShootR_RT") = std::bind(&Machinegun::diagonalAttackStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootR_TR") = std::bind(&Machinegun::diagonalAttackStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootR_RB") = std::bind(&Machinegun::diagonalAttackStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootR_BR") = std::bind(&Machinegun::diagonalAttackStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootR_LT") = std::bind(&Machinegun::diagonalAttackStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootR_TL") = std::bind(&Machinegun::diagonalAttackStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootR_LB") = std::bind(&Machinegun::diagonalAttackStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootR_BL") = std::bind(&Machinegun::diagonalAttackStartEvent, this);

		mAnimator->GetCompleteEvent(L"M_ShootR_RT") = std::bind(&Machinegun::diagonalAttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootR_TR") = std::bind(&Machinegun::diagonalAttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootR_RB") = std::bind(&Machinegun::diagonalAttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootR_BR") = std::bind(&Machinegun::diagonalAttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootR_LT") = std::bind(&Machinegun::diagonalAttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootR_TL") = std::bind(&Machinegun::diagonalAttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootR_LB") = std::bind(&Machinegun::diagonalAttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootR_BL") = std::bind(&Machinegun::diagonalAttackEndEvent, this);


		
		//mAnimator->Play(L"M_paraglider", false);
	}
	void Machinegun::Update()
	{
		mState = player->GetMarcoState();

		switch (mState) {
		/*case mo::Marco::eMarcoState::Paraglider:
			paraglider();
			break;*/
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

		player->SetMarcoState(mState);
	}

	void Machinegun::move()
	{
		Vector2 pos = mTransform->GetPos();
		eDirection mDirection = mTransform->GetDirection();

		// 좌우 애니메이션

		if (Input::GetKey(eKeyCode::Right)) {
			if (Input::GetKeyDown(eKeyCode::Left)) {
				if (mDirection == eDirection::Right) {
					mAnimator->Play(L"M_IdleR", true);
				}
				else if (mDirection == eDirection::RTop) {
					mDirection = eDirection::LTop;
					mAnimator->Play(L"M_IdleLT", true);
				}
			}
			if (Input::GetKeyUp(eKeyCode::Left)) {
				if (mDirection == eDirection::RTop || mDirection == eDirection::LTop) {
					mDirection = eDirection::RTop;
					mAnimator->Play(L"M_IdleRT", true);
				}
				else if (mDirection == eDirection::Right || mDirection == eDirection::Left) {
					mDirection = eDirection::Right;
					mAnimator->Play(L"M_MoveR", true);
				}

			}
			if (!isShooting)
			{
				if (Input::GetKeyDown(eKeyCode::Up)) {
					mDirection = eDirection::RTop;
					mAnimator->Play(L"M_IdleRT", true);
				}
				if (Input::GetKeyUp(eKeyCode::Up)) {
					mDirection = eDirection::Right;
					mAnimator->Play(L"M_MoveR", true);
				}
			}
			else
			{
				if (Input::GetKeyDown(eKeyCode::Up)) {
					mDirection = eDirection::RTop;
					mAnimator->Play(L"M_ShootR_RT", false);
				}
				if (Input::GetKeyUp(eKeyCode::Up)) {
					mDirection = eDirection::Right;
					mAnimator->Play(L"M_ShootR_TR", false);
				}
			}

		}
		if (Input::GetKey(eKeyCode::Left)) {

			if (Input::GetKeyDown(eKeyCode::Right)) {
				if (mDirection == eDirection::Left) {
					mAnimator->Play(L"M_IdleL", true);
				}
				else if (mDirection == eDirection::LTop) {
					mDirection = eDirection::RTop;
					mAnimator->Play(L"M_IdleRT", true);
				}
			}
			if (Input::GetKeyUp(eKeyCode::Right)) {
				if (mDirection == eDirection::RTop || mDirection == eDirection::LTop) {
					mDirection = eDirection::LTop;
					mAnimator->Play(L"M_IdleLT", true);
				}
				else if (mDirection == eDirection::Right || mDirection == eDirection::Left) {
					mDirection = eDirection::Left;
					mAnimator->Play(L"M_MoveL", true);
				}
			}
			if (!isShooting)
			{
				if (Input::GetKeyDown(eKeyCode::Up)) {
					mDirection = eDirection::LTop;
					mAnimator->Play(L"M_IdleLT", true);
				}
				if (Input::GetKeyUp(eKeyCode::Up)) {
					mDirection = eDirection::Left;
					mAnimator->Play(L"M_MoveL", true);
				}
			}
			else
			{
				if (Input::GetKeyDown(eKeyCode::Up)) {
					mDirection = eDirection::LTop;
					mAnimator->Play(L"M_ShootR_LT", false);
				}
				if (Input::GetKeyUp(eKeyCode::Up)) {
					mDirection = eDirection::Left;
					mAnimator->Play(L"M_ShootR_TL", false);
				}
			}
		}

		if (Input::GetKeyUp(eKeyCode::Right))
			if (Input::GetKeyDown(eKeyCode::Left)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"M_MoveL", true);
			}
		if (Input::GetKeyUp(eKeyCode::Left))
			if (Input::GetKeyDown(eKeyCode::Right)) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"M_MoveR", true);
			}
		if (Input::GetKeyNone(eKeyCode::Right))
			if (Input::GetKeyDown(eKeyCode::Left)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"M_MoveL", true);
			}
		if (Input::GetKeyNone(eKeyCode::Left))
			if (Input::GetKeyDown(eKeyCode::Right)) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"M_MoveR", true);
			}

		// To Idle
		if ((Input::GetKeyNone(eKeyCode::Right)
			&& Input::GetKeyNone(eKeyCode::Left)))
		{
			if (mDirection == eDirection::Left)
				mAnimator->Play(L"M_IdleL", true);
			if (mDirection == eDirection::Right)
				mAnimator->Play(L"M_IdleR", true);


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
					mAnimator->Play(L"M_JumpDownR", false);
				}
				else if (mDirection == eDirection::Left) {
					mDirection = eDirection::LBottom;
					mAnimator->Play(L"M_JumpDownL", false);
				}
			}
			else {
				if (Input::GetKey(eKeyCode::Right))
					mAnimator->Play(L"M_JumpMoveR", false);
				else if (Input::GetKey(eKeyCode::Left))
					mAnimator->Play(L"M_JumpMoveL", false);
			}

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 700.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mState = Marco::eMarcoState::Jump;
		}
		// Shooting
		if (Input::GetKeyDown(eKeyCode::D)) {

			if (player->GetIsKnife()) {
				if (mDirection == eDirection::Right || mDirection == eDirection::RTop)
					mAnimator->Play(L"M_KnifeR", false);
				else if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
					mAnimator->Play(L"M_KnifeL", false);
			}
			else {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"M_ShootR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"M_ShootL", false);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"M_ShootRT", false);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"M_ShootLT", false);
			}
		}
		if (Input::GetKeyDown(eKeyCode::F)) {
			if (mDirection == eDirection::Right || mDirection == eDirection::RTop)
				mAnimator->Play(L"M_ThrowingBombR", false);
			else if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
				mAnimator->Play(L"M_ThrowingBombL", false);
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

	void Machinegun::shoot()
	{
	}

	void Machinegun::death()
	{
	}

	void Machinegun::idle()
	{

		eDirection mDirection = mTransform->GetDirection();


		// To move

		if (Input::GetKeyDown(eKeyCode::Right))
		{
			if (mDirection == eDirection::RTop || mDirection == eDirection::LTop)
			{
				mDirection = eDirection::RTop;
				mAnimator->Play(L"M_IdleRT", true);
			}

			else if (mDirection == eDirection::Right || mDirection == eDirection::Left)
			{
				mDirection = eDirection::Right;
				mAnimator->Play(L"M_MoveR", true);
			}

			mState = Marco::eMarcoState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			if (mDirection == eDirection::RTop || mDirection == eDirection::LTop)
			{
				mDirection = eDirection::LTop;
				mAnimator->Play(L"M_IdleLT", true);
			}
			else if (mDirection == eDirection::Right || mDirection == eDirection::Left)
			{
				mDirection = eDirection::Left;
				mAnimator->Play(L"M_MoveL", true);
			}

			mState = Marco::eMarcoState::Move;
		}


		if (!isShooting) 
		{
			//Idle
			if (Input::GetKey(eKeyCode::Up) && (mDirection == eDirection::Right)) {
				mDirection = eDirection::RTop;
				mAnimator->Play(L"M_IdleRT", true);
			}
			else if (Input::GetKey(eKeyCode::Up) && (mDirection == eDirection::Left)) {
				mDirection = eDirection::LTop;
				mAnimator->Play(L"M_IdleLT", true);
			}

			if (Input::GetKeyNone(eKeyCode::Up) && (mDirection == eDirection::RTop)) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"M_IdleR", true);
			}
			else if (Input::GetKeyNone(eKeyCode::Up) && (mDirection == eDirection::LTop)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"M_IdleL", true);
			}
		}
		else
		{
			//Idle
			if (Input::GetKeyDown(eKeyCode::Up) && (mDirection == eDirection::Right)) {
				mDirection = eDirection::RTop;
				mAnimator->Play(L"M_ShootR_RT", false);
			}
			else if (Input::GetKeyDown(eKeyCode::Up) && (mDirection == eDirection::Left)) {
				mDirection = eDirection::LTop;
				mAnimator->Play(L"M_ShootR_LT", false);
			}

			if (Input::GetKeyUp(eKeyCode::Up) && (mDirection == eDirection::RTop)) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"M_ShootR_TR", false);
			}
			else if (Input::GetKeyUp(eKeyCode::Up) && (mDirection == eDirection::LTop)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"M_ShootR_TL", false);
			}
			mTransform->SetDirection(mDirection);

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

			if (mDirection == eDirection::Right || mDirection == eDirection::RTop)
				mAnimator->Play(L"M_JumpIdleR", false);
			if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
				mAnimator->Play(L"M_JumpIdleL", false);


			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 700.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mState = Marco::eMarcoState::Jump;
		}


		// Shooting
		if (Input::GetKeyDown(eKeyCode::D)) {

			if (player->GetIsKnife()) {
				if (mDirection == eDirection::Right || mDirection == eDirection::RTop)
					mAnimator->Play(L"M_KnifeR", false);
				else if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
					mAnimator->Play(L"M_KnifeL", false);
			}
			else {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"M_ShootR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"M_ShootL", false);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"M_ShootRT", false);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"M_ShootLT", false);
			}
		}
		if (Input::GetKeyDown(eKeyCode::F)) {
			if (mDirection == eDirection::Right || mDirection == eDirection::RTop)
				mAnimator->Play(L"M_ThrowingBombR", false);
			else if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
				mAnimator->Play(L"M_ThrowingBombL", false);
		}
	}

	void Machinegun::sit()
	{

		eDirection mDirection = mTransform->GetDirection();
		Vector2 pos = mTransform->GetPos();

	
			//이동중
			if (Input::GetKey(eKeyCode::Left)
				&& Camera::GetDistance().x < pos.x - 30.0f
				&& Input::GetKeyNone(eKeyCode::Right))
			{
				if(!playerBottom->GetIsShooting())
					pos.x -= 80.0f * Time::DeltaTime();
				mDirection = eDirection::Left;
			}
			if (Input::GetKey(eKeyCode::Right)
				&& Camera::GetDistance().x + application.GetWidth() > pos.x + 30.0f
				&& Input::GetKeyNone(eKeyCode::Left))
			{
				if (!playerBottom->GetIsShooting())
					pos.x += 80.0f * Time::DeltaTime();
				mDirection = eDirection::Right;

			}
		



		if (Input::GetKeyUp(eKeyCode::Down)) {
			// 둘다 눌려있을때 
			if (Input::GetKey(eKeyCode::Right) && Input::GetKey(eKeyCode::Left))
			{
				if (mDirection == eDirection::Right)
				{
					mAnimator->Play(L"M_MoveR", true);
					mState = Marco::eMarcoState::Move;
				}
				else if (mDirection == eDirection::Left)
				{
					mAnimator->Play(L"M_MoveL", true);
					mState = Marco::eMarcoState::Move;
				}
			}
			else if (Input::GetKey(eKeyCode::Right))
			{
				mAnimator->Play(L"M_MoveR", true);
				mState = Marco::eMarcoState::Move;
			}
			else if (Input::GetKey(eKeyCode::Left))
			{
				mAnimator->Play(L"M_MoveL", true);
				mState = Marco::eMarcoState::Move;
			}
			else if (Input::GetKeyNone(eKeyCode::Right)
				&& Input::GetKeyNone(eKeyCode::Left)) {

				if (mDirection == eDirection::Right || mDirection == eDirection::RSit || mDirection == eDirection::RBottom) {
					mAnimator->Play(L"M_IdleR", true);
					mDirection = eDirection::Right;
				}

				if (mDirection == eDirection::Left || mDirection == eDirection::LSit || mDirection == eDirection::LBottom) {
					mAnimator->Play(L"M_IdleL", true);
					mDirection = eDirection::Left;
				}
				mState = Marco::eMarcoState::Idle;

			}

		}

		//Junp
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDirection == eDirection::Right || mDirection == eDirection::RBottom) {
				mDirection = eDirection::RBottom;
				mAnimator->Play(L"M_JumpDownR", false);
			}
			if (mDirection == eDirection::Left || mDirection == eDirection::LBottom) {
				mDirection = eDirection::LBottom;
				mAnimator->Play(L"M_JumpDownL", false);
			}
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 700.0f;

			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
			mTransform->SetDirection(mDirection);
			mState = Marco::eMarcoState::Jump;
		}

		mTransform->SetPos(pos);
		mTransform->SetDirection(mDirection);
		
		// Shooting
		if (Input::GetKeyDown(eKeyCode::D))
		{
			mTransform->SetDirection(mDirection);
			shootStartEvent();
		}
		if (Input::GetKeyDown(eKeyCode::F))
		{
			isBomb = true;
			mTransform->SetDirection(mDirection);
			shootStartEvent();
		}


	}

	void Machinegun::jump()
	{

		eDirection mDirection = mTransform->GetDirection();
		Vector2 pos = mTransform->GetPos();


		//Junp
		if (mRigidbody->GetGround())
		{
			if (Input::GetKey(eKeyCode::Down))
			{
				if (mDirection == eDirection::Right || mDirection == eDirection::RBottom)
					mAnimator->Play(L"None", false);
				else if (mDirection == eDirection::Left || mDirection == eDirection::LBottom)
					mAnimator->Play(L"None", false);

				playerBottom->SetIsGround(true);
				mState = Marco::eMarcoState::Sit;
			}
			else
			{
				if (Input::GetKeyNone(eKeyCode::Left) &&
					Input::GetKeyNone(eKeyCode::Right))
				{
					if (mDirection == eDirection::RTop)
						mAnimator->Play(L"M_IdleRT", true);
					else if (mDirection == eDirection::LTop)
						mAnimator->Play(L"M_IdleLT", true);
					else if (mDirection == eDirection::Right)
						mAnimator->Play(L"M_IdleR", true);
					else if (mDirection == eDirection::Left)
						mAnimator->Play(L"M_IdleL", true);

					playerBottom->SetIsGround(true);
					mState = Marco::eMarcoState::Idle;
				}

				else if (Input::GetKey(eKeyCode::Left) && Input::GetKey(eKeyCode::Right))
				{
					if (mDirection == eDirection::LTop)
						mAnimator->Play(L"M_IdleLT", true);
					else if (mDirection == eDirection::Left)
						mAnimator->Play(L"M_MoveL", true);
					else if (mDirection == eDirection::RTop)
						mAnimator->Play(L"M_IdleRT", true);
					else if (mDirection == eDirection::Right)
						mAnimator->Play(L"M_MoveR", true);

					playerBottom->SetIsGround(true);
					mState = Marco::eMarcoState::Move;
				}
				else if (Input::GetKey(eKeyCode::Left))
				{
					if (mDirection == eDirection::LTop)
						mAnimator->Play(L"M_IdleLT", true);
					else if (mDirection == eDirection::Left)
						mAnimator->Play(L"M_MoveL", true);

					playerBottom->SetIsGround(true);
					mState = Marco::eMarcoState::Move;
				}
				else if (Input::GetKey(eKeyCode::Right))
				{
					if (mDirection == eDirection::RTop)
						mAnimator->Play(L"M_IdleRT", true);
					else if (mDirection == eDirection::Right)
						mAnimator->Play(L"M_MoveR", true);

					playerBottom->SetIsGround(true);
					mState = Marco::eMarcoState::Move;

				}
			}
		}



		if (!isShooting)
		{
			if (Input::GetKeyDown(eKeyCode::Down)) {
				if (mDirection == eDirection::Right) {
					mDirection = eDirection::RBottom;
					mAnimator->Play(L"M_JumpDownR", false);
				}
				if (mDirection == eDirection::Left) {
					mDirection = eDirection::LBottom;
					mAnimator->Play(L"M_JumpDownL", false);
				}
			}
			if (Input::GetKeyUp(eKeyCode::Down)) {
				if (mDirection == eDirection::RBottom) {
					mDirection = eDirection::Right;
					mAnimator->Play(L"M_JumpIdleR", false);
				}
				if (mDirection == eDirection::LBottom) {
					mDirection = eDirection::Left;
					mAnimator->Play(L"M_JumpIdleL", false);
				}
			}
		}
		else
		{
			if (Input::GetKeyDown(eKeyCode::Down)) {
				if (mDirection == eDirection::Right) {
					mDirection = eDirection::RBottom;
					mAnimator->Play(L"M_ShootR_RB", false);
				}
				if (mDirection == eDirection::Left) {
					mDirection = eDirection::LBottom;
					mAnimator->Play(L"M_ShootR_LB", false);
				}
			}
			if (Input::GetKeyUp(eKeyCode::Down)) {
				if (mDirection == eDirection::RBottom) {
					mDirection = eDirection::Right;
					mAnimator->Play(L"M_ShootR_BR", false);
				}
				if (mDirection == eDirection::LBottom) {
					mDirection = eDirection::Left;
					mAnimator->Play(L"M_ShootR_BL", false);
				}
			}
		}


		if (Input::GetKey(eKeyCode::Right)) {
			if (Input::GetKeyUp(eKeyCode::Left)) {
				if (mDirection == eDirection::RTop || mDirection == eDirection::LTop)
					mDirection = eDirection::RTop;

				else if (mDirection == eDirection::Right || mDirection == eDirection::Left)
					mDirection = eDirection::Right;

				else if (mDirection == eDirection::RBottom || mDirection == eDirection::LBottom)
					mDirection = eDirection::RBottom;
			}
			if (!isShooting)
			{
				if (Input::GetKeyDown(eKeyCode::Up)) {
					mDirection = eDirection::RTop;
					
				}
				if (Input::GetKeyUp(eKeyCode::Up)) {
					mDirection = eDirection::Right;
				}
			}else
			{
				if (Input::GetKeyDown(eKeyCode::Up)) {
					mDirection = eDirection::RTop;
					mAnimator->Play(L"M_ShootR_RT", false);
				}
				if (Input::GetKeyUp(eKeyCode::Up)) {
					mDirection = eDirection::Right;
					mAnimator->Play(L"M_ShootR_TR", false);
				}
			}

		}
		if (Input::GetKey(eKeyCode::Left)) {
			if (Input::GetKeyUp(eKeyCode::Right)) {
				if (mDirection == eDirection::RTop || mDirection == eDirection::LTop)
					mDirection = eDirection::LTop;
				else if (mDirection == eDirection::Right || mDirection == eDirection::Left)
					mDirection = eDirection::Left;
				else if (mDirection == eDirection::RBottom || mDirection == eDirection::LBottom)
					mDirection = eDirection::LBottom;
			}
			if(!isShooting)
			{
				if (Input::GetKeyDown(eKeyCode::Up)) {
					mDirection = eDirection::LTop;
				}
				if (Input::GetKeyUp(eKeyCode::Up)) {
					mDirection = eDirection::Left;
				}
			}
			else
			{
				if (Input::GetKeyDown(eKeyCode::Up)) {
					mDirection = eDirection::LTop;
					mAnimator->Play(L"M_ShootR_LT", false);
				}
				if (Input::GetKeyUp(eKeyCode::Up)) {
					mDirection = eDirection::Left;
					mAnimator->Play(L"M_ShootR_TL", false);
				}
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


		/*if (Input::GetKeyNone(eKeyCode::Right)
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

		}*/

		if (isShooting)
		{
			if (mDirection == eDirection::Right || mDirection == eDirection::RTop)
			{
				if (Input::GetKeyDown(eKeyCode::Up)) {
					mDirection = eDirection::RTop;
					mAnimator->Play(L"M_ShootR_RT", false);
				}
				if (Input::GetKeyUp(eKeyCode::Up)) {
					mDirection = eDirection::Right;
					mAnimator->Play(L"M_ShootR_TR", false);
				}
			}
			else if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
			{
				if (Input::GetKeyDown(eKeyCode::Up)) {
					mDirection = eDirection::LTop;
					mAnimator->Play(L"M_ShootR_LT", false);
				}
				if (Input::GetKeyUp(eKeyCode::Up)) {
					mDirection = eDirection::Left;
					mAnimator->Play(L"M_ShootR_TL", false);
				}
			}
		}

		// up키 눌렀을때 mDirection설정
		if (Input::GetKey(eKeyCode::Up))
		{
			if (mDirection == eDirection::Right)
				mDirection = eDirection::RTop;
			if (mDirection == eDirection::Left)
				mDirection = eDirection::LTop;
		}
		if (Input::GetKeyNone(eKeyCode::Up))
		{
			if (mDirection == eDirection::RTop)
				mDirection = eDirection::Right;
			if (mDirection == eDirection::LTop)
				mDirection = eDirection::Left;
		}


		// Down키 눌렀을때 mDirection설정
		if (Input::GetKey(eKeyCode::Down))
		{
			if (mDirection == eDirection::Right)
				mDirection = eDirection::RBottom;
			if (mDirection == eDirection::Left)
				mDirection = eDirection::LBottom;
		}
		if (Input::GetKeyNone(eKeyCode::Down))
		{
			if (mDirection == eDirection::RBottom)
				mDirection = eDirection::Right;
			if (mDirection == eDirection::LBottom)
				mDirection = eDirection::Left;
		}

		mTransform->SetDirection(mDirection);

		if (Input::GetKeyDown(eKeyCode::D)) {


			if (player->GetIsKnife()) {
				if (mDirection == eDirection::Right || mDirection == eDirection::RTop || mDirection == eDirection::RBottom)
					mAnimator->Play(L"M_KnifeR", false);
				else if (mDirection == eDirection::Left || mDirection == eDirection::LTop || mDirection == eDirection::LBottom)
					mAnimator->Play(L"M_KnifeL", false);
			}
			else {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"M_ShootR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"M_ShootL", false);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"M_ShootRT", false);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"M_ShootLT", false);
				else if (mDirection == eDirection::RBottom)
					mAnimator->Play(L"M_ShootRB", false);
				else if (mDirection == eDirection::LBottom)
					mAnimator->Play(L"M_ShootLB", false);
			}

		}
		if (Input::GetKeyDown(eKeyCode::F)) {
			if (mDirection == eDirection::Right || mDirection == eDirection::RTop || mDirection == eDirection::RBottom)
				mAnimator->Play(L"M_ThrowingBombR", false);
			else if (mDirection == eDirection::Left || mDirection == eDirection::LTop || mDirection == eDirection::LBottom)
				mAnimator->Play(L"M_ThrowingBombL", false);
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

	void Machinegun::shootStartEvent()
	{
		

		eDirection mDirection = mTransform->GetDirection();
		Vector2 mPos = mTransform->GetPos();
		Scene* curScene = SceneManager::GetActiveScene();
		
		Animation* activeAnimation = mAnimator->GetActiveAnimation();
		Animation* prevAnimation = mAnimator->GetPrevAniamtion();

		isShooting = true;

		if (mState == Marco::eMarcoState::Sit) {
			if (activeAnimation->GetName() == L"M_ThrowingBombR" ||
				activeAnimation->GetName() == L"M_ThrowingBombL" ||
				isBomb)
			{
				isBomb = false; 
				
				if (player->GetBombNum() > 0)
				{
					player->SetBombNum(player->GetBombNum() - 1);
					PlayerBomb* bomb = new PlayerBomb();
					curScene->AddGameObject(bomb, eLayerType::PlayerBomb);
					bomb->Initialize();
					bomb->GetComponent<Transform>()->SetPos(mPos);
					bomb->PlayAnimation(mDirection);
				}
			}
			else if (player->GetIsKnife())
			{

			}
			else
			{
				if (mDirection == eDirection::Right || mDirection == eDirection::RBottom) {
					for (int i = 0; i < 4; i++)
					{
						int bulletNum = player->GetBulletNum();
						if (bulletNum > 0)
						{
							bulletNum--;
							player->SetBulletNum(bulletNum);
							MachinegunBullet* machinegunBullet = new MachinegunBullet(player);
							if (i == 0) {
								machinegunBullet->SetDir(Vector2{ 5.0f, 0.0f });
								machinegunBullet->SetTime(0.0f);
							}
							else if (i == 1)
							{
								machinegunBullet->SetDir(Vector2{ 5.0f, -0.08f });
								machinegunBullet->SetTime(0.06f);
							}
							else if (i == 2)
							{
								machinegunBullet->SetDir(Vector2{ 5.0f, 0.08f });
								machinegunBullet->SetTime(0.12f);
							}
							else if (i == 3)
							{
								machinegunBullet->SetDir(Vector2{ 5.0f, 0.14f });
								machinegunBullet->SetTime(0.18f);
							}

							machinegunBullet->SetDirection(eDirection::Right, 0);
							machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(50.0f, 0.0f));
							curScene->AddGameObject(machinegunBullet, eLayerType::PlayerMachinegun);
							machinegunBullet->Initialize();
						}
					}
				
				}
				else if (mDirection == eDirection::Left || mDirection == eDirection::LBottom) {
					for (int i = 0; i < 4; i++)
					{
						int bulletNum = player->GetBulletNum();
						if (bulletNum > 0)
						{
							bulletNum--;
							player->SetBulletNum(bulletNum);
							MachinegunBullet* machinegunBullet = new MachinegunBullet(player);
							if (i == 0) {
								machinegunBullet->SetDir(Vector2{ -5.0f, 0.0f });
								machinegunBullet->SetTime(0.0f);
							}
							else if (i == 1)
							{
								machinegunBullet->SetDir(Vector2{ -5.0f, -0.08f });
								machinegunBullet->SetTime(0.06f);
							}
							else if (i == 2)
							{
								machinegunBullet->SetDir(Vector2{ -5.0f, 0.08f });
								machinegunBullet->SetTime(0.12f);
							}
							else if (i == 3)
							{
								machinegunBullet->SetDir(Vector2{ -5.0f, 0.14f });
								machinegunBullet->SetTime(0.18f);
							}

							machinegunBullet->SetDirection(eDirection::Left, 0);
							machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-50.0f, 0.0f));
							curScene->AddGameObject(machinegunBullet, eLayerType::PlayerMachinegun);
							machinegunBullet->Initialize();

						}
					}
				}
			}
		}
		else {
			if (activeAnimation->GetName() == L"M_ThrowingBombR" ||
				activeAnimation->GetName() == L"M_ThrowingBombL")
			{
				if (player->GetBombNum() > 0)
				{
					player->SetBombNum(player->GetBombNum() - 1);
					PlayerBomb* bomb = new PlayerBomb();
					curScene->AddGameObject(bomb, eLayerType::PlayerBomb);
					bomb->Initialize();
					bomb->GetComponent<Transform>()->SetPos(mPos + Vector2(0.0f, -30.0f));
					bomb->PlayAnimation(mDirection);
				}
			}
			else if (player->GetIsKnife())
			{

			}
			else
			{
					if (mDirection == eDirection::Right) {
						for (int i = 0; i < 4; i++)
						{
							int bulletNum = player->GetBulletNum();
							if (bulletNum > 0)
							{
								bulletNum--;
								player->SetBulletNum(bulletNum);
								MachinegunBullet* machinegunBullet = new MachinegunBullet(player);
								if (i == 0) {
									machinegunBullet->SetDir(Vector2{ 5.0f, 0.0f });
									machinegunBullet->SetTime(0.0f);
								}
								else if (i == 1)
								{
									machinegunBullet->SetDir(Vector2{ 5.0f, -0.08f });
									machinegunBullet->SetTime(0.06f);
								}	
								else if (i == 2)
								{
									machinegunBullet->SetDir(Vector2{ 5.0f, 0.08f });
									machinegunBullet->SetTime(0.12f);
								}
								else if (i == 3)
								{
									machinegunBullet->SetDir(Vector2{ 5.0f, 0.14f });
									machinegunBullet->SetTime(0.18f);
								}

								machinegunBullet->SetDirection(eDirection::Right, 0);
								machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(50.0f, -15.0f));
								curScene->AddGameObject(machinegunBullet, eLayerType::PlayerMachinegun);
								machinegunBullet->Initialize();
							}
						}
					}
					else if (mDirection == eDirection::Left) {
						for (int i = 0; i < 4; i++)
						{
							int bulletNum = player->GetBulletNum();
							if (bulletNum > 0)
							{
								bulletNum--;
								player->SetBulletNum(bulletNum);
								MachinegunBullet* machinegunBullet = new MachinegunBullet(player);
								if (i == 0) {
									machinegunBullet->SetDir(Vector2{ -5.0f, 0.0f });
									machinegunBullet->SetTime(0.0f);
								}
								else if (i == 1)
								{
									machinegunBullet->SetDir(Vector2{ -5.0f, -0.08f });
									machinegunBullet->SetTime(0.06f);
								}
								else if (i == 2)
								{
									machinegunBullet->SetDir(Vector2{ -5.0f, 0.08f });
									machinegunBullet->SetTime(0.12f);
								}
								else if (i == 3)
								{
									machinegunBullet->SetDir(Vector2{ -5.0f, 0.14f });
									machinegunBullet->SetTime(0.18f);
								}

								machinegunBullet->SetDirection(eDirection::Left, 0);
								machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-50.0f, -15.0f));
								curScene->AddGameObject(machinegunBullet, eLayerType::PlayerMachinegun);
								machinegunBullet->Initialize();

							}
						}
					}
					else if (mDirection == eDirection::RTop || mDirection == eDirection::LTop) {
						
						for (int i = 0; i < 4; i++)
						{
							int bulletNum = player->GetBulletNum();
							if (bulletNum > 0)
							{
								bulletNum--;
								player->SetBulletNum(bulletNum);
								MachinegunBullet* machinegunBullet = new MachinegunBullet(player);
								if (i == 0) {
									machinegunBullet->SetDir(Vector2{ 0.0f, -5.0f });
									machinegunBullet->SetTime(0.0f);
								}
								else if (i == 1)
								{
									machinegunBullet->SetDir(Vector2{ 0.05F, -5.0f });
									machinegunBullet->SetTime(0.06f);
								}
								else if (i == 2)
								{
									machinegunBullet->SetDir(Vector2{ -0.05f, -5.0f });
									machinegunBullet->SetTime(0.12f);
								}
								else if (i == 3)
								{
									machinegunBullet->SetDir(Vector2{ 0.1f, -5.0f });
									machinegunBullet->SetTime(0.18f);
								}

								machinegunBullet->SetDirection(eDirection::RTop, 0);
								machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-5.0f, -90.0f));
								curScene->AddGameObject(machinegunBullet, eLayerType::PlayerMachinegun);
								machinegunBullet->Initialize();

							}
						}
					}
					else if (mDirection == eDirection::RBottom || mDirection == eDirection::LBottom) {
						for (int i = 0; i < 4; i++)
						{
							int bulletNum = player->GetBulletNum();
							if (bulletNum > 0)
							{
								bulletNum--;
								player->SetBulletNum(bulletNum);
								MachinegunBullet* machinegunBullet = new MachinegunBullet(player);
								if (i == 0) {
									machinegunBullet->SetDir(Vector2{ 0.0f, 5.0f });
									machinegunBullet->SetTime(0.0f);
								}
								else if (i == 1)
								{
									machinegunBullet->SetDir(Vector2{ 0.05f, 5.0f });
									machinegunBullet->SetTime(0.06f);
								}
								else if (i == 2)
								{
									machinegunBullet->SetDir(Vector2{ -0.05f, 5.0f });
									machinegunBullet->SetTime(0.12f);
								}
								else if (i == 3)
								{
									machinegunBullet->SetDir(Vector2{ 0.1f, 5.0f });
									machinegunBullet->SetTime(0.18f);
								}

								machinegunBullet->SetDirection(eDirection::RBottom, 0);
								machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-5.0f, 90.0f));
								curScene->AddGameObject(machinegunBullet, eLayerType::PlayerMachinegun);
								machinegunBullet->Initialize();

							}
						}

					}
					

			}
		}

		
		if (prevAnimation->GetName() != L"M_ShootR" &&
			prevAnimation->GetName() != L"M_ShootRT" &&
			prevAnimation->GetName() != L"M_ShootL" &&
			prevAnimation->GetName() != L"M_ShootLT" &&
			prevAnimation->GetName() != L"M_ShootRB" &&
			prevAnimation->GetName() != L"M_ShootLB"&&
			prevAnimation->GetName() != L"M_KnifeR" &&
			prevAnimation->GetName() != L"M_KnifeL" &&
			prevAnimation->GetName() != L"M_ThrowingBombR" &&
			prevAnimation->GetName() != L"M_ThrowingBombL")
				mPrevAnimation = prevAnimation;
	}


	void Machinegun::attackCompleteEvent()
	{
		isShooting = false;
		
		if (mRigidbody->GetGround() == false)
		{
			if (Input::GetKey(eKeyCode::Up))
			{
				if (Input::GetKey(eKeyCode::Right))
					mAnimator->Play(L"M_IdleRT", true);
				else if (Input::GetKey(eKeyCode::Left))
					mAnimator->Play(L"M_IdleLT", true);
			}
			else
				mAnimator->Play(mPrevAnimation->GetName(), true);
		}
		else
			mAnimator->Play(mPrevAnimation->GetName(), true);
	}

	void Machinegun::attackEndEvent()
	{
		isShooting = false;
	}

	void Machinegun::diagonalAttackStartEvent()
	{
		isShooting = false;
	
		eDirection mDirection = mTransform->GetDirection();
		Vector2 mPos = mTransform->GetPos();
		Scene* curScene = SceneManager::GetActiveScene();

		if (mAnimator->GetActiveAnimation()->GetName() == L"M_ShootR_RT")
		{
			for (int i = 1; i < 5; i++)
			{
				int bulletNum = player->GetBulletNum();
				if (bulletNum > 0)
				{
					bulletNum--;
					player->SetBulletNum(bulletNum);
					MachinegunBullet* machinegunBullet = new MachinegunBullet(player);
					if (i == 1) {
						machinegunBullet->SetDir(Vector2{ 5.0f, -2.0f });
						machinegunBullet->SetTime(0.0f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(70.0f, -35.0f));

					}
					else if (i == 2)
					{
						machinegunBullet->SetDir(Vector2{ 5.0f, -4.0f });
						machinegunBullet->SetTime(0.06f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(70.0f, -65.0f));

					}
					else if (i == 3)
					{
						machinegunBullet->SetDir(Vector2{ 5.0f, -7.0f });
						machinegunBullet->SetTime(0.12f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(60.0f, -80.0f));

					}
					else if (i == 4)
					{
						machinegunBullet->SetDir(Vector2{ 5.0f, -11.0f });
						machinegunBullet->SetTime(0.18f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(55.0f, -105.0f));

					}

					machinegunBullet->SetDirection(eDirection::RTop, i);
					curScene->AddGameObject(machinegunBullet, eLayerType::PlayerMachinegun);
					machinegunBullet->Initialize();

				}
			}
		}
		else if (mAnimator->GetActiveAnimation()->GetName() == L"M_ShootR_TR")
		{
			for (int i = 1; i < 5; i++)
			{
				int bulletNum = player->GetBulletNum();
				if (bulletNum > 0)
				{
					bulletNum--;
					player->SetBulletNum(bulletNum);
					MachinegunBullet* machinegunBullet = new MachinegunBullet(player);
					if (i == 1) {
						machinegunBullet->SetDir(Vector2{ 5.0f, -11.0f });
						machinegunBullet->SetTime(0.0f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(45.0f, -90.0f));

					}
					else if (i == 2)
					{
						machinegunBullet->SetDir(Vector2{ 5.0f, -7.0f });
						machinegunBullet->SetTime(0.06f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(50.0f, -60.0f));

					}
					else if (i == 3)
					{
						machinegunBullet->SetDir(Vector2{ 5.0f, -4.0f });
						machinegunBullet->SetTime(0.12f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(60.0f, -30.0f));

					}
					else if (i == 4)
					{
						machinegunBullet->SetDir(Vector2{ 5.0f, -2.0f });
						machinegunBullet->SetTime(0.18f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(60.0f, -15.0f));

					}

					machinegunBullet->SetDirection(eDirection::Right, i);
					curScene->AddGameObject(machinegunBullet, eLayerType::PlayerMachinegun);
					machinegunBullet->Initialize();

				}
			}
		}
		else if (mAnimator->GetActiveAnimation()->GetName() == L"M_ShootR_RB")
		{
			for (int i = 1; i < 5; i++)
			{
				int bulletNum = player->GetBulletNum();
				if (bulletNum > 0)
				{
					bulletNum--;
					player->SetBulletNum(bulletNum);
					MachinegunBullet* machinegunBullet = new MachinegunBullet(player);
					if (i == 1) {
						machinegunBullet->SetDir(Vector2{ 5.0f, 2.0f });
						machinegunBullet->SetTime(0.0f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(50.0f, 35.0f));

					}
					else if (i == 2)
					{
						machinegunBullet->SetDir(Vector2{ 5.0f, 4.0f });
						machinegunBullet->SetTime(0.06f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(50.0f, 65.0f));

					}
					else if (i == 3)
					{
						machinegunBullet->SetDir(Vector2{ 5.0f, 7.0f });
						machinegunBullet->SetTime(0.12f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(40.0f, 80.0f));

					}
					else if (i == 4)
					{
						machinegunBullet->SetDir(Vector2{ 5.0f, 11.0f });
						machinegunBullet->SetTime(0.18f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(35.0f, 105.0f));

					}

					machinegunBullet->SetDirection(eDirection::RBottom, i);
					curScene->AddGameObject(machinegunBullet, eLayerType::PlayerMachinegun);
					machinegunBullet->Initialize();

				}
			}
		}
		else if (mAnimator->GetActiveAnimation()->GetName() == L"M_ShootR_BR")
		{
			for (int i = 1; i < 5; i++)
			{
				int bulletNum = player->GetBulletNum();
				if (bulletNum > 0)
				{
					bulletNum--;
					player->SetBulletNum(bulletNum);
					MachinegunBullet* machinegunBullet = new MachinegunBullet(player);
					if (i == 1) {
						machinegunBullet->SetDir(Vector2{ 5.0f, 11.0f });
						machinegunBullet->SetTime(0.0f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(35.0f, 105.0f));

					}
					else if (i == 2)
					{
						machinegunBullet->SetDir(Vector2{ 5.0f, 7.0f });
						machinegunBullet->SetTime(0.06f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(40.0f, 80.0f));

					}
					else if (i == 3)
					{
						machinegunBullet->SetDir(Vector2{ 5.0f, 4.0f });
						machinegunBullet->SetTime(0.12f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(50.0f, 65.0f));

					}
					else if (i == 4)
					{
						machinegunBullet->SetDir(Vector2{ 5.0f, 2.0f });
						machinegunBullet->SetTime(0.18f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(50.0f, 35.0f));

					}

					machinegunBullet->SetDirection(eDirection::RSit, i);
					curScene->AddGameObject(machinegunBullet, eLayerType::PlayerMachinegun);
					machinegunBullet->Initialize();

				}
			}
		}
		else if (mAnimator->GetActiveAnimation()->GetName() == L"M_ShootR_LT")
		{
			for (int i = 1; i < 5; i++)
			{
				int bulletNum = player->GetBulletNum();
				if (bulletNum > 0)
				{
					bulletNum--;
					player->SetBulletNum(bulletNum);
					MachinegunBullet* machinegunBullet = new MachinegunBullet(player);
					if (i == 1) {
						machinegunBullet->SetDir(Vector2{ -5.0f, -2.0f });
						machinegunBullet->SetTime(0.0f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-70.0f, -35.0f));

					}
					else if (i == 2)
					{
						machinegunBullet->SetDir(Vector2{ -5.0f, -4.0f });
						machinegunBullet->SetTime(0.06f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-70.0f, -65.0f));

					}
					else if (i == 3)
					{
						machinegunBullet->SetDir(Vector2{ -5.0f, -7.0f });
						machinegunBullet->SetTime(0.12f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-60.0f, -80.0f));

					}
					else if (i == 4)
					{
						machinegunBullet->SetDir(Vector2{ -5.0f, -11.0f });
						machinegunBullet->SetTime(0.18f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-55.0f, -105.0f));

					}

					machinegunBullet->SetDirection(eDirection::LTop, i);
					curScene->AddGameObject(machinegunBullet, eLayerType::PlayerMachinegun);
					machinegunBullet->Initialize();

				}
			}
		}
		else if (mAnimator->GetActiveAnimation()->GetName() == L"M_ShootR_TL")
		{
			for (int i = 1; i < 5; i++)
			{
				int bulletNum = player->GetBulletNum();
				if (bulletNum > 0)
				{
					bulletNum--;
					player->SetBulletNum(bulletNum);
					MachinegunBullet* machinegunBullet = new MachinegunBullet(player);
					if (i == 1) {
						machinegunBullet->SetDir(Vector2{ -5.0f, -11.0f });
						machinegunBullet->SetTime(0.0f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-45.0f, -105.0f));

					}
					else if (i == 2)
					{
						machinegunBullet->SetDir(Vector2{ -5.0f, -7.0f });
						machinegunBullet->SetTime(0.06f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-50.0f, -80.0f));

					}
					else if (i == 3)
					{
						machinegunBullet->SetDir(Vector2{ -5.0f, -4.0f });
						machinegunBullet->SetTime(0.12f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-60.0f, -65.0f));

					}
					else if (i == 4)
					{
						machinegunBullet->SetDir(Vector2{ -5.0f, -2.0f });
						machinegunBullet->SetTime(0.18f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-60.0f, -35.0f));

					}

					machinegunBullet->SetDirection(eDirection::Left, i);
					curScene->AddGameObject(machinegunBullet, eLayerType::PlayerMachinegun);
					machinegunBullet->Initialize();

				}
			}
		}
		else if (mAnimator->GetActiveAnimation()->GetName() == L"M_ShootR_LB")
		{
			for (int i = 1; i < 5; i++)
			{
				int bulletNum = player->GetBulletNum();
				if (bulletNum > 0)
				{
					bulletNum--;
					player->SetBulletNum(bulletNum);
					MachinegunBullet* machinegunBullet = new MachinegunBullet(player);
					if (i == 1) {
						machinegunBullet->SetDir(Vector2{ -5.0f, 2.0f });
						machinegunBullet->SetTime(0.0f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-50.0f, 35.0f));

					}
					else if (i == 2)
					{
						machinegunBullet->SetDir(Vector2{ -5.0f, 4.0f });
						machinegunBullet->SetTime(0.06f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-50.0f, 65.0f));

					}
					else if (i == 3)
					{
						machinegunBullet->SetDir(Vector2{ -5.0f, 7.0f });
						machinegunBullet->SetTime(0.12f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-40.0f, 80.0f));

					}
					else if (i == 4)
					{
						machinegunBullet->SetDir(Vector2{ -5.0f, 11.0f });
						machinegunBullet->SetTime(0.18f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-35.0f, 105.0f));

					}

					machinegunBullet->SetDirection(eDirection::RBottom, i);
					curScene->AddGameObject(machinegunBullet, eLayerType::PlayerMachinegun);
					machinegunBullet->Initialize();

				}
			}
		}
		else if (mAnimator->GetActiveAnimation()->GetName() == L"M_ShootR_BL")
		{
			for (int i = 1; i < 5; i++)
			{
				int bulletNum = player->GetBulletNum();
				if (bulletNum > 0)
				{
					bulletNum--;
					player->SetBulletNum(bulletNum);
					MachinegunBullet* machinegunBullet = new MachinegunBullet(player);
					if (i == 1) {
						machinegunBullet->SetDir(Vector2{ -5.0f, 11.0f });
						machinegunBullet->SetTime(0.0f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-35.0f, 105.0f));

					}
					else if (i == 2)
					{
						machinegunBullet->SetDir(Vector2{ -5.0f, 7.0f });
						machinegunBullet->SetTime(0.06f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-40.0f, 80.0f));

					}
					else if (i == 3)
					{
						machinegunBullet->SetDir(Vector2{ -5.0f, 4.0f });
						machinegunBullet->SetTime(0.12f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-50.0f, 65.0f));

					}
					else if (i == 4)
					{
						machinegunBullet->SetDir(Vector2{ -5.0f, 2.0f });
						machinegunBullet->SetTime(0.18f);
						machinegunBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-50.0f, 35.0f));

					}

					machinegunBullet->SetDirection(eDirection::LSit, i);
					curScene->AddGameObject(machinegunBullet, eLayerType::PlayerMachinegun);
					machinegunBullet->Initialize();

				}
			}
		}
	}

	void Machinegun::diagonalAttackEndEvent()
	{
		isShooting = false;

		eDirection mDirection = mTransform->GetDirection();
		Vector2 mPos = mTransform->GetPos();
		Scene* curScene = SceneManager::GetActiveScene();

		if (Input::GetKey(eKeyCode::Up))
		{
			if (Input::GetKey(eKeyCode::Right) && Input::GetKey(eKeyCode::Left))
			{
				if (mDirection == eDirection::Right || mDirection == eDirection::RSit|| mDirection == eDirection::RTop|| mDirection == eDirection::RBottom)
					mAnimator->Play(L"M_IdleRT", true);
				else
					mAnimator->Play(L"M_IdleLT", true);
			}
			else if (Input::GetKey(eKeyCode::Right))
			{
				mAnimator->Play(L"M_IdleRT", true);
			}
			else if (Input::GetKey(eKeyCode::Left))
			{
				mAnimator->Play(L"M_IdleLT", true);
			}
			else if (Input::GetKeyNone(eKeyCode::Right) || Input::GetKeyNone(eKeyCode::Left))
			{
				if (mDirection == eDirection::Right || mDirection == eDirection::RSit || mDirection == eDirection::RTop || mDirection == eDirection::RBottom)
					mAnimator->Play(L"M_IdleRT", true);
				else
					mAnimator->Play(L"M_IdleLT", true);
			}
		}
		else if (Input::GetKey(eKeyCode::Down))
		{
			if (Input::GetKey(eKeyCode::Right) && Input::GetKey(eKeyCode::Left))
			{
				if (mDirection == eDirection::Right || mDirection == eDirection::RSit || mDirection == eDirection::RTop || mDirection == eDirection::RBottom)
					mAnimator->Play(L"M_JumpDownR", true);
				else
					mAnimator->Play(L"M_JumpDownL", true);
			}
			else if (Input::GetKey(eKeyCode::Right))
			{
				mAnimator->Play(L"M_JumpDownR", true);
			}
			else if (Input::GetKey(eKeyCode::Left))
			{
				mAnimator->Play(L"M_JumpDownL", true);
			}
			else if (Input::GetKeyNone(eKeyCode::Right) || Input::GetKeyNone(eKeyCode::Left))
			{
				if (mDirection == eDirection::Right || mDirection == eDirection::RSit || mDirection == eDirection::RTop || mDirection == eDirection::RBottom)
					mAnimator->Play(L"M_JumpDownR", true);
				else
					mAnimator->Play(L"M_JumpDownL", true);
			}
		}
		else if (Input::GetKeyNone(eKeyCode::Up) || Input::GetKeyNone(eKeyCode::Down))
		{
			if (Input::GetKey(eKeyCode::Right) && Input::GetKey(eKeyCode::Left))
			{
				if (mDirection == eDirection::Right || mDirection == eDirection::RSit || mDirection == eDirection::RTop || mDirection == eDirection::RBottom)
					mAnimator->Play(L"M_IdleR", true);
				else
					mAnimator->Play(L"M_IdleL", true);
			}
			else if (Input::GetKey(eKeyCode::Right))
			{
				mAnimator->Play(L"M_IdleR", true);
			}
			else if (Input::GetKey(eKeyCode::Left))
			{
				mAnimator->Play(L"M_IdleL", true);
			}
			else if (Input::GetKeyNone(eKeyCode::Right) || Input::GetKeyNone(eKeyCode::Left))
			{
				if (mDirection == eDirection::Right || mDirection == eDirection::RSit || mDirection == eDirection::RTop || mDirection == eDirection::RBottom)
					mAnimator->Play(L"M_IdleR", true);
				else
					mAnimator->Play(L"M_IdleL", true);
			}
		}

	}


}