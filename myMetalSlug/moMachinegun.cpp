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

extern mo::Application application;

namespace mo {
	Machinegun::Machinegun(Marco* marco, MarcoBottom* bottom)
		: unUsedParaglider(false)
		, player(marco)
		, playerBottom(bottom)
	{
	}
	Machinegun::~Machinegun()
	{
	}
	void Machinegun::Initialize()
	{
		/*	player = GetPlayer();
			playerBottom = GetBottom();*/


		mState = player->GetState();
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


		//mAnimator->CreateAnimation(L"M_KnifeR", mImageR, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		//mAnimator->CreateAnimation(L"M_KnifeL", mImageL, Vector2(120.0f * 29, 120.0f * 3), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);

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

		mAnimator->CreateAnimation(L"M_paraglider", mImageR, Vector2(120.0f * 0, 120.0f * 9), 120.0f, 30, 60, 6, Vector2::Zero, 0.05);


		/*mAnimator->GetStartEvent(L"KnifeR") = std::bind(&Pistol::AttackEndEvent, this);
		mAnimator->GetStartEvent(L"KnifeL") = std::bind(&Pistol::AttackEndEvent, this);*/
		mAnimator->GetStartEvent(L"M_ShootR") = std::bind(&Machinegun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootL") = std::bind(&Machinegun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootRT") = std::bind(&Machinegun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootLT") = std::bind(&Machinegun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootRB") = std::bind(&Machinegun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"M_ShootLB") = std::bind(&Machinegun::shootStartEvent, this);


		/*	mAnimator->GetCompleteEvent(L"KnifeR") = std::bind(&Pistol::AttackEndEvent, this);
			mAnimator->GetCompleteEvent(L"KnifeL") = std::bind(&Pistol::AttackEndEvent, this);*/
		mAnimator->GetCompleteEvent(L"M_ShootR") = std::bind(&Machinegun::AttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootL") = std::bind(&Machinegun::AttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootRT") = std::bind(&Machinegun::AttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootLT") = std::bind(&Machinegun::AttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootRB") = std::bind(&Machinegun::AttackEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_ShootLB") = std::bind(&Machinegun::AttackEndEvent, this);

		//mAnimator->Play(L"M_paraglider", false);
	}
	void Machinegun::Update()
	{
		mState = player->GetState();

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

		player->SetState(mState);
	}

	/*void Machinegun::paraglider()
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
			mAnimator->Play(L"M_IdleR", true);
			playerBottom->SetIsGround(true);
			mRigidbody->SetGravity(Vector2(0.0f, 1500.0f));
			mState = Marco::eMarcoState::Idle;
		}
	}*/
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
			if (Input::GetKeyDown(eKeyCode::Up)) {
				mDirection = eDirection::RTop;
				mAnimator->Play(L"M_IdleRT", true);
			}
			if (Input::GetKeyUp(eKeyCode::Up)) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"M_MoveR", true);
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
			if (Input::GetKeyDown(eKeyCode::Up)) {
				mDirection = eDirection::LTop;
				mAnimator->Play(L"M_IdleLT", true);
			}
			if (Input::GetKeyUp(eKeyCode::Up)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"M_MoveL", true);
			}
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

			/*if (isKnife) {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"KnifeR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"KnifeL", false);
			}*/
			//else {
			if (mDirection == eDirection::Right)
				mAnimator->Play(L"M_ShootR", false);
			else if (mDirection == eDirection::Left)
				mAnimator->Play(L"M_ShootL", false);
			else if (mDirection == eDirection::RTop)
				mAnimator->Play(L"M_ShootRT", false);
			else if (mDirection == eDirection::LTop)
				mAnimator->Play(L"M_ShootLT", false);
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

			/*	if (isKnife) {
					if (mDirection == eDirection::Right)
						mAnimator->Play(L"KnifeR", false);
					else if (mDirection == eDirection::Left)
						mAnimator->Play(L"KnifeL", false);
				}
				else {*/
			if (mDirection == eDirection::Right)
				mAnimator->Play(L"M_ShootR", false);
			else if (mDirection == eDirection::Left)
				mAnimator->Play(L"M_ShootL", false);
			else if (mDirection == eDirection::RTop)
				mAnimator->Play(L"M_ShootRT", false);
			else if (mDirection == eDirection::LTop)
				mAnimator->Play(L"M_ShootLT", false);
			//}
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
			//mTransform->SetDirection(mDirection);
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


		if (Input::GetKey(eKeyCode::Right)) {
			if (Input::GetKeyUp(eKeyCode::Left)) {
				if (mDirection == eDirection::RTop || mDirection == eDirection::LTop)
					mDirection = eDirection::RTop;

				else if (mDirection == eDirection::Right || mDirection == eDirection::Left)
					mDirection = eDirection::Right;

				else if (mDirection == eDirection::RBottom || mDirection == eDirection::LBottom)
					mDirection = eDirection::RBottom;
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
				if (mDirection == eDirection::RTop || mDirection == eDirection::LTop)
					mDirection = eDirection::LTop;
				else if (mDirection == eDirection::Right || mDirection == eDirection::Left)
					mDirection = eDirection::Left;
				else if (mDirection == eDirection::RBottom || mDirection == eDirection::LBottom)
					mDirection = eDirection::LBottom;
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

		Scene* curScene = SceneManager::GetActiveScene();
		PistolBullet* pistolBullet = new PistolBullet();

		if (mState == Marco::eMarcoState::Sit) {
			if (mDirection == eDirection::Right) {
				pistolBullet->SetDirection(eDirection::RSit);
				pistolBullet->SetDir(Vector2{ 5.0f, 0.0f });
			}
			else if (mDirection == eDirection::Left) {
				pistolBullet->SetDirection(eDirection::LSit);
				pistolBullet->SetDir(Vector2{ -5.0f, 0.0f });
			}
		}
		else {
			if (mDirection == eDirection::Right) {
				pistolBullet->SetDirection(eDirection::Right);
				pistolBullet->SetDir(Vector2{ 5.0f, 0.0f });
			}
			else if (mDirection == eDirection::Left) {
				pistolBullet->SetDirection(eDirection::Left);
				pistolBullet->SetDir(Vector2{ -5.0f, 0.0f });
			}
			else if (mDirection == eDirection::RTop) {
				pistolBullet->SetDirection(eDirection::Top);
				pistolBullet->SetDir(Vector2{ 0.0f, -5.0f });
			}
			else if (mDirection == eDirection::LTop) {
				pistolBullet->SetDirection(eDirection::Top);
				pistolBullet->SetDir(Vector2{ 0.0f, -5.0f });
			}
			else if (mDirection == eDirection::RBottom) {
				pistolBullet->SetDirection(eDirection::Bottom);
				pistolBullet->SetDir(Vector2{ 0.0f, 5.0f });
			}
			else if (mDirection == eDirection::LBottom) {
				pistolBullet->SetDirection(eDirection::Bottom);
				pistolBullet->SetDir(Vector2{ 0.0f, 5.0f });
			}
		}

		//카메라 좌표
		//bullet->GetComponent<Transform>()->SetPos(Camera::CaluatePos(tr->GetPos()));
		pistolBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos());
		curScene->AddGameObject(pistolBullet, eLayerType::Bullet);
		pistolBullet->Initialize();

		Animation* activeAnimation = mAnimator->GetActiveAnimation();
		Animation* prevAnimation = mAnimator->GetPrevAniamtion();

		if (prevAnimation->GetName() != L"M_ShootR" &&
			prevAnimation->GetName() != L"M_ShootRT" &&
			prevAnimation->GetName() != L"M_ShootL" &&
			prevAnimation->GetName() != L"M_ShootLT" &&
			prevAnimation->GetName() != L"M_ShootRB" &&
			prevAnimation->GetName() != L"M_ShootLB")
				mPrevAnimation = prevAnimation;
	}


	void Machinegun::AttackEndEvent()
	{
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


}