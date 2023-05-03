#include "moShotgun.h"
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
#include "moSound.h"
extern mo::Application application;

namespace mo {
	Shotgun::Shotgun(Marco* marco, MarcoBottom* bottom)
		: unUsedParaglider(false)
		, player(marco)
		, playerBottom(bottom)
		, isShooting(false)
	{
	}
	Shotgun::~Shotgun()
	{
	}
	void Shotgun::Initialize()
	{
		/*	player = GetPlayer();
			playerBottom = GetBottom();*/

		machinegunBulletSound = Resources::Load<Sound>(L"machinegunBulletSound", L"..\\Resources\\Sound\\machinegunBulletSound.wav");

		mState = player->GetMarcoState();
		mAnimator = player->GetComponent<Animator>();
		mRigidbody = player->GetComponent<RigidBody>();
		mTransform = player->GetComponent<Transform>();


		Image* mImageR = Resources::Load<Image>(L"RipleRight", L"..\\Resources\\Player\\RipleRight.bmp");
		Image* mImageL = Resources::Load<Image>(L"RipleLeft", L"..\\Resources\\Player\\RipleLeft.bmp");

		// Coulmn : 행	row : 열
		//mAnimator->CreateAnimation(L"IdleR", mImageR, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"S_IdleR", mImageR, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"S_IdleRT", mImageR, Vector2(120.0f * 0, 120.0f * 5), 120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"S_IdleL", mImageL, Vector2(120.0f * 29, 120.0f * 0), -120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"S_IdleLT", mImageL, Vector2(120.0f * 29, 120.0f * 5), -120.0f, 30, 60, 4, Vector2::Zero, 0.15);


		//mAnimator->CreateAnimation(L"ShootR", mImageR, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 30, 60, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_ShootR", mImageR, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 30, 60, 4, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_ShootRT", mImageR, Vector2(120.0f * 0, 120.0f * 6), 120.0f, 30, 60, 4, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_ShootL", mImageL, Vector2(120.0f * 29, 120.0f * 1), -120.0f, 30, 60, 4, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_ShootLT", mImageL, Vector2(120.0f * 29, 120.0f * 6), -120.0f, 30, 60, 4, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_ShootRB", mImageR, Vector2(120.0f * 0, 120.0f * 8), 120.0f, 30, 60, 4, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_ShootLB", mImageL, Vector2(120.0f * 29, 120.0f * 8), -120.0f, 30, 60, 4, Vector2::Zero, 0.07);


		mAnimator->CreateAnimation(L"S_KnifeR", mImageR, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_KnifeL", mImageL, Vector2(120.0f * 29, 120.0f * 3), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"S_MoveR", mImageR, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 30, 60, 12, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"S_MoveL", mImageL, Vector2(120.0f * 29, 120.0f * 2), -120.0f, 30, 60, 12, Vector2::Zero, 0.05);

		//mAnimator->CreateAnimation(L"M_None", mImageR, Vector2(120.0f * 29, 120.0f * 0), 120.0f, 30, 60, 1, Vector2::Zero, 1.0);

		mAnimator->CreateAnimation(L"S_JumpIdleR", mImageR, Vector2(120.0f * 0, 120.0f * 9), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_JumpIdleL", mImageL, Vector2(120.0f * 29, 120.0f * 9), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"S_JumpMoveR", mImageR, Vector2(120.0f * 0, 120.0f * 10), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_JumpMoveL", mImageL, Vector2(120.0f * 29, 120.0f * 10), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);

		//mAnimator->CreateAnimation(L"M_JumpDownR", test, Vector2(120.0f * 0, 120.0f * 7), 120.0f, 30, 60, 3, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_JumpDownR", mImageR, Vector2(120.0f * 0, 120.0f * 11), 120.0f, 30, 60, 7, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_JumpDownL", mImageL, Vector2(120.0f * 29, 120.0f * 11), -120.0f, 30, 60, 7, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"S_ThrowingBombR", mImageR, Vector2(120.0f * 0, 120.0f * 12), 120.0f, 30, 60, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_ThrowingBombL", mImageL, Vector2(120.0f * 29, 120.0f * 12), -120.0f, 30, 60, 6, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"S_ShootR_RT", mImageR, Vector2(120.0f * 0, 120.0f * 13), 120.0f, 30, 60, 2, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_ShootR_TR", mImageR, Vector2(120.0f * 0, 120.0f * 14), 120.0f, 30, 60, 2, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_ShootR_RB", mImageR, Vector2(120.0f * 0, 120.0f * 15), 120.0f, 30, 60, 2, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_ShootR_BR", mImageR, Vector2(120.0f * 0, 120.0f * 16), 120.0f, 30, 60, 2, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_ShootR_LT", mImageL, Vector2(120.0f * 29, 120.0f * 13), -120.0f, 30, 60, 2, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_ShootR_TL", mImageL, Vector2(120.0f * 29, 120.0f * 14), -120.0f, 30, 60, 2, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_ShootR_LB", mImageL, Vector2(120.0f * 29, 120.0f * 15), -120.0f, 30, 60, 2, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"S_ShootR_BL", mImageL, Vector2(120.0f * 29, 120.0f * 16), -120.0f, 30, 60, 2, Vector2::Zero, 0.07);


		mAnimator->GetStartEvent(L"S_ThrowingBombR") = std::bind(&Shotgun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"S_ThrowingBombL") = std::bind(&Shotgun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"S_KnifeR") = std::bind(&Shotgun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"S_KnifeL") = std::bind(&Shotgun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"S_ShootR") = std::bind(&Shotgun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"S_ShootL") = std::bind(&Shotgun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"S_ShootRT") = std::bind(&Shotgun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"S_ShootLT") = std::bind(&Shotgun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"S_ShootRB") = std::bind(&Shotgun::shootStartEvent, this);
		mAnimator->GetStartEvent(L"S_ShootLB") = std::bind(&Shotgun::shootStartEvent, this);

		mAnimator->GetCompleteEvent(L"S_ThrowingBombR") = std::bind(&Shotgun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"S_ThrowingBombL") = std::bind(&Shotgun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"S_KnifeR") = std::bind(&Shotgun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"S_KnifeL") = std::bind(&Shotgun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"S_ShootR") = std::bind(&Shotgun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"S_ShootL") = std::bind(&Shotgun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"S_ShootRT") = std::bind(&Shotgun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"S_ShootLT") = std::bind(&Shotgun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"S_ShootRB") = std::bind(&Shotgun::attackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"S_ShootLB") = std::bind(&Shotgun::attackCompleteEvent, this);





		//mAnimator->Play(L"M_paraglider", false);
	}
	void Shotgun::Update()
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
		case mo::Marco::eMarcoState::Complete:
			complete();
			break;
		default:
			break;
		}

		player->SetMarcoState(mState);
	}

	void Shotgun::move()
	{
		Vector2 pos = mTransform->GetPos();
		eDirection mDirection = mTransform->GetDirection();

		// 좌우 애니메이션

		if (Input::GetKey(eKeyCode::Right)) {
			if (Input::GetKeyDown(eKeyCode::Left)) {
				if (mDirection == eDirection::Right) {
					mAnimator->Play(L"S_IdleR", true);
				}
				else if (mDirection == eDirection::RTop) {
					mDirection = eDirection::LTop;
					mAnimator->Play(L"S_IdleLT", true);
				}
			}
			if (Input::GetKeyUp(eKeyCode::Left)) {
				if (mDirection == eDirection::RTop || mDirection == eDirection::LTop) {
					mDirection = eDirection::RTop;
					mAnimator->Play(L"S_IdleRT", true);
				}
				else if (mDirection == eDirection::Right || mDirection == eDirection::Left) {
					mDirection = eDirection::Right;
					mAnimator->Play(L"S_MoveR", true);
				}

			}
			
				if (Input::GetKeyDown(eKeyCode::Up)) {
					mDirection = eDirection::RTop;
					mAnimator->Play(L"S_IdleRT", true);
				}
				if (Input::GetKeyUp(eKeyCode::Up)) {
					mDirection = eDirection::Right;
					mAnimator->Play(L"S_MoveR", true);
				}
			

		}
		if (Input::GetKey(eKeyCode::Left)) {

			if (Input::GetKeyDown(eKeyCode::Right)) {
				if (mDirection == eDirection::Left) {
					mAnimator->Play(L"S_IdleL", true);
				}
				else if (mDirection == eDirection::LTop) {
					mDirection = eDirection::RTop;
					mAnimator->Play(L"S_IdleRT", true);
				}
			}
			if (Input::GetKeyUp(eKeyCode::Right)) {
				if (mDirection == eDirection::RTop || mDirection == eDirection::LTop) {
					mDirection = eDirection::LTop;
					mAnimator->Play(L"S_IdleLT", true);
				}
				else if (mDirection == eDirection::Right || mDirection == eDirection::Left) {
					mDirection = eDirection::Left;
					mAnimator->Play(L"S_MoveL", true);
				}
			}
			
				if (Input::GetKeyDown(eKeyCode::Up)) {
					mDirection = eDirection::LTop;
					mAnimator->Play(L"S_IdleLT", true);
				}
				if (Input::GetKeyUp(eKeyCode::Up)) {
					mDirection = eDirection::Left;
					mAnimator->Play(L"S_MoveL", true);
				}
			
		}

		if (Input::GetKeyUp(eKeyCode::Right))
			if (Input::GetKeyDown(eKeyCode::Left)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"S_MoveL", true);
			}
		if (Input::GetKeyUp(eKeyCode::Left))
			if (Input::GetKeyDown(eKeyCode::Right)) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"S_MoveR", true);
			}
		if (Input::GetKeyNone(eKeyCode::Right))
			if (Input::GetKeyDown(eKeyCode::Left)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"S_MoveL", true);
			}
		if (Input::GetKeyNone(eKeyCode::Left))
			if (Input::GetKeyDown(eKeyCode::Right)) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"S_MoveR", true);
			}

		// To Idle
		if ((Input::GetKeyNone(eKeyCode::Right)
			&& Input::GetKeyNone(eKeyCode::Left)))
		{
			if (mDirection == eDirection::Left)
				mAnimator->Play(L"S_IdleL", true);
			if (mDirection == eDirection::Right)
				mAnimator->Play(L"S_IdleR", true);


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
					mAnimator->Play(L"S_JumpDownR", false);
				}
				else if (mDirection == eDirection::Left) {
					mDirection = eDirection::LBottom;
					mAnimator->Play(L"S_JumpDownL", false);
				}
			}
			else {
				if (Input::GetKey(eKeyCode::Right))
					mAnimator->Play(L"S_JumpMoveR", false);
				else if (Input::GetKey(eKeyCode::Left))
					mAnimator->Play(L"S_JumpMoveL", false);
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
					mAnimator->Play(L"S_KnifeR", false);
				else if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
					mAnimator->Play(L"S_KnifeL", false);
			}
			else {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"S_ShootR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"S_ShootL", false);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"S_ShootRT", false);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"S_ShootLT", false);
			}
		}
		if (Input::GetKeyDown(eKeyCode::F)) {
			if (mDirection == eDirection::Right || mDirection == eDirection::RTop)
				mAnimator->Play(L"S_ThrowingBombR", false);
			else if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
				mAnimator->Play(L"S_ThrowingBombL", false);
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

	void Shotgun::shoot()
	{
	}

	void Shotgun::death()
	{
	}

	void Shotgun::idle()
	{

		eDirection mDirection = mTransform->GetDirection();


		// To move

		if (Input::GetKeyDown(eKeyCode::Right))
		{
			if (mDirection == eDirection::RTop || mDirection == eDirection::LTop)
			{
				mDirection = eDirection::RTop;
				mAnimator->Play(L"S_IdleRT", true);
			}

			else if (mDirection == eDirection::Right || mDirection == eDirection::Left)
			{
				mDirection = eDirection::Right;
				mAnimator->Play(L"S_MoveR", true);
			}

			mState = Marco::eMarcoState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			if (mDirection == eDirection::RTop || mDirection == eDirection::LTop)
			{
				mDirection = eDirection::LTop;
				mAnimator->Play(L"S_IdleLT", true);
			}
			else if (mDirection == eDirection::Right || mDirection == eDirection::Left)
			{
				mDirection = eDirection::Left;
				mAnimator->Play(L"S_MoveL", true);
			}

			mState = Marco::eMarcoState::Move;
		}


			//Idle
			if (Input::GetKey(eKeyCode::Up) && (mDirection == eDirection::Right)) {
				mDirection = eDirection::RTop;
				mAnimator->Play(L"S_IdleRT", true);
			}
			else if (Input::GetKey(eKeyCode::Up) && (mDirection == eDirection::Left)) {
				mDirection = eDirection::LTop;
				mAnimator->Play(L"S_IdleLT", true);
			}

			if (Input::GetKeyNone(eKeyCode::Up) && (mDirection == eDirection::RTop)) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"S_IdleR", true);
			}
			else if (Input::GetKeyNone(eKeyCode::Up) && (mDirection == eDirection::LTop)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"S_IdleL", true);
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
				mAnimator->Play(L"S_JumpIdleR", false);
			if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
				mAnimator->Play(L"S_JumpIdleL", false);


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
					mAnimator->Play(L"S_KnifeR", false);
				else if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
					mAnimator->Play(L"S_KnifeL", false);
			}
			else {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"S_ShootR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"S_ShootL", false);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"S_ShootRT", false);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"S_ShootLT", false);
			}
		}
		if (Input::GetKeyDown(eKeyCode::F)) {
			if (mDirection == eDirection::Right || mDirection == eDirection::RTop)
				mAnimator->Play(L"S_ThrowingBombR", false);
			else if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
				mAnimator->Play(L"S_ThrowingBombL", false);
		}
	}

	void Shotgun::sit()
	{

		eDirection mDirection = mTransform->GetDirection();
		Vector2 pos = mTransform->GetPos();


		//이동중
		if (Input::GetKey(eKeyCode::Left)
			&& Camera::GetDistance().x < pos.x - 30.0f
			&& Input::GetKeyNone(eKeyCode::Right))
		{
			if (!playerBottom->GetIsShooting())
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
					mAnimator->Play(L"S_MoveR", true);
					mState = Marco::eMarcoState::Move;
				}
				else if (mDirection == eDirection::Left)
				{
					mAnimator->Play(L"S_MoveL", true);
					mState = Marco::eMarcoState::Move;
				}
			}
			else if (Input::GetKey(eKeyCode::Right))
			{
				mAnimator->Play(L"S_MoveR", true);
				mState = Marco::eMarcoState::Move;
			}
			else if (Input::GetKey(eKeyCode::Left))
			{
				mAnimator->Play(L"S_MoveL", true);
				mState = Marco::eMarcoState::Move;
			}
			else if (Input::GetKeyNone(eKeyCode::Right)
				&& Input::GetKeyNone(eKeyCode::Left)) {

				if (mDirection == eDirection::Right || mDirection == eDirection::RSit || mDirection == eDirection::RBottom) {
					mAnimator->Play(L"S_IdleR", true);
					mDirection = eDirection::Right;
				}

				if (mDirection == eDirection::Left || mDirection == eDirection::LSit || mDirection == eDirection::LBottom) {
					mAnimator->Play(L"S_IdleL", true);
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
				mAnimator->Play(L"S_JumpDownR", false);
			}
			if (mDirection == eDirection::Left || mDirection == eDirection::LBottom) {
				mDirection = eDirection::LBottom;
				mAnimator->Play(L"S_JumpDownL", false);
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

	void Shotgun::jump()
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
						mAnimator->Play(L"S_IdleRT", true);
					else if (mDirection == eDirection::LTop)
						mAnimator->Play(L"S_IdleLT", true);
					else if (mDirection == eDirection::Right)
						mAnimator->Play(L"S_IdleR", true);
					else if (mDirection == eDirection::Left)
						mAnimator->Play(L"S_IdleL", true);

					playerBottom->SetIsGround(true);
					mState = Marco::eMarcoState::Idle;
				}

				else if (Input::GetKey(eKeyCode::Left) && Input::GetKey(eKeyCode::Right))
				{
					if (mDirection == eDirection::LTop)
						mAnimator->Play(L"S_IdleLT", true);
					else if (mDirection == eDirection::Left)
						mAnimator->Play(L"S_MoveL", true);
					else if (mDirection == eDirection::RTop)
						mAnimator->Play(L"S_IdleRT", true);
					else if (mDirection == eDirection::Right)
						mAnimator->Play(L"S_MoveR", true);

					playerBottom->SetIsGround(true);
					mState = Marco::eMarcoState::Move;
				}
				else if (Input::GetKey(eKeyCode::Left))
				{
					if (mDirection == eDirection::LTop)
						mAnimator->Play(L"S_IdleLT", true);
					else if (mDirection == eDirection::Left)
						mAnimator->Play(L"S_MoveL", true);

					playerBottom->SetIsGround(true);
					mState = Marco::eMarcoState::Move;
				}
				else if (Input::GetKey(eKeyCode::Right))
				{
					if (mDirection == eDirection::RTop)
						mAnimator->Play(L"S_IdleRT", true);
					else if (mDirection == eDirection::Right)
						mAnimator->Play(L"S_MoveR", true);

					playerBottom->SetIsGround(true);
					mState = Marco::eMarcoState::Move;

				}
			}
		}



		
			if (Input::GetKeyDown(eKeyCode::Down)) {
				if (mDirection == eDirection::Right) {
					mDirection = eDirection::RBottom;
					mAnimator->Play(L"S_JumpDownR", false);
				}
				if (mDirection == eDirection::Left) {
					mDirection = eDirection::LBottom;
					mAnimator->Play(L"S_JumpDownL", false);
				}
			}
			if (Input::GetKeyUp(eKeyCode::Down)) {
				if (mDirection == eDirection::RBottom) {
					mDirection = eDirection::Right;
					mAnimator->Play(L"S_JumpIdleR", false);
				}
				if (mDirection == eDirection::LBottom) {
					mDirection = eDirection::Left;
					mAnimator->Play(L"S_JumpIdleL", false);
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
					mAnimator->Play(L"S_KnifeR", false);
				else if (mDirection == eDirection::Left || mDirection == eDirection::LTop || mDirection == eDirection::LBottom)
					mAnimator->Play(L"S_KnifeL", false);
			}
			else {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"S_ShootR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"S_ShootL", false);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"S_ShootRT", false);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"S_ShootLT", false);
				else if (mDirection == eDirection::RBottom)
					mAnimator->Play(L"S_ShootRB", false);
				else if (mDirection == eDirection::LBottom)
					mAnimator->Play(L"S_ShootLB", false);
			}

		}
		if (Input::GetKeyDown(eKeyCode::F)) {
			if (mDirection == eDirection::Right || mDirection == eDirection::RTop || mDirection == eDirection::RBottom)
				mAnimator->Play(L"S_ThrowingBombR", false);
			else if (mDirection == eDirection::Left || mDirection == eDirection::LTop || mDirection == eDirection::LBottom)
				mAnimator->Play(L"S_ThrowingBombL", false);
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

	void Shotgun::complete()
	{
	}

	void Shotgun::shootStartEvent()
	{



		eDirection mDirection = mTransform->GetDirection();
		Vector2 mPos = mTransform->GetPos();

		Scene* curScene = SceneManager::GetActiveScene();

		Animation* activeAnimation = mAnimator->GetActiveAnimation();
		Animation* prevAnimation = mAnimator->GetPrevAniamtion();

		if (mState == Marco::eMarcoState::Sit) {
			if (activeAnimation->GetName() == L"S_ThrowingBombR" ||
				activeAnimation->GetName() == L"S_ThrowingBombL" ||
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
				PistolBullet* pistolBullet = new PistolBullet();

				//pistolSound->Play(false);

				if (mDirection == eDirection::Right || mDirection == eDirection::RBottom) {
					pistolBullet->SetDir(Vector2{ 5.0f, 0.0f });
					pistolBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(50.0f, -10.0f));
				}
				else if (mDirection == eDirection::Left || mDirection == eDirection::LBottom) {
					pistolBullet->SetDir(Vector2{ -5.0f, 0.0f });
					pistolBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-50.0f, -10.0f));
				}
				curScene->AddGameObject(pistolBullet, eLayerType::PlayerPistol);
				pistolBullet->Initialize();
			}
		}
		else {
			if (activeAnimation->GetName() == L"S_ThrowingBombR" ||
				activeAnimation->GetName() == L"S_ThrowingBombL"
				)
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
				PistolBullet* pistolBullet = new PistolBullet();
				//pistolSound->Play(false);


				if (mDirection == eDirection::Right) {
					pistolBullet->SetDir(Vector2{ 5.0f, 0.0f });
					pistolBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(50.0f, -50.0f));

				}
				else if (mDirection == eDirection::Left) {
					pistolBullet->SetDir(Vector2{ -5.0f, 0.0f });
					pistolBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-50.0f, -50.0f));

				}
				else if (mDirection == eDirection::RTop || mDirection == eDirection::LTop) {
					pistolBullet->SetDir(Vector2{ 0.0f, -5.0f });
					pistolBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-5.0f, -90.0f));
				}
				else if (mDirection == eDirection::RBottom || mDirection == eDirection::LBottom) {
					pistolBullet->SetDir(Vector2{ 0.0f, 5.0f });
					pistolBullet->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(-5.0f, 90.0f));

				}
				curScene->AddGameObject(pistolBullet, eLayerType::PlayerPistol);
				pistolBullet->Initialize();
			}
		}





		if (prevAnimation->GetName() != L"S_ShootR" &&
			prevAnimation->GetName() != L"S_ShootRT" &&
			prevAnimation->GetName() != L"S_ShootL" &&
			prevAnimation->GetName() != L"S_ShootLT" &&
			prevAnimation->GetName() != L"S_ShootRB" &&
			prevAnimation->GetName() != L"S_ShootLB" &&
			prevAnimation->GetName() != L"S_KnifeR" &&
			prevAnimation->GetName() != L"S_KnifeL" &&
			prevAnimation->GetName() != L"S_ThrowingBombR" &&
			prevAnimation->GetName() != L"S_ThrowingBombL")
			mPrevAnimation = prevAnimation;

	}
	

	void Shotgun::attackCompleteEvent()
	{
		isShooting = false;

		if (mRigidbody->GetGround() == false)
		{
			if (Input::GetKey(eKeyCode::Up))
			{
				if (Input::GetKey(eKeyCode::Right))
					mAnimator->Play(L"S_IdleRT", true);
				else if (Input::GetKey(eKeyCode::Left))
					mAnimator->Play(L"S_IdleLT", true);
			}
			else
				mAnimator->Play(mPrevAnimation->GetName(), true);
		}
		else
			mAnimator->Play(mPrevAnimation->GetName(), true);
	}



}