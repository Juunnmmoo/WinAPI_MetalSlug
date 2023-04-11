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
#include "moPistolBullet.h"
#include "moScene.h"
#include "moCamera.h"
#include "moRigidBody.h"
#include "moApplication.h"
#include "moPlayerBomb.h"

extern mo::Application application;

namespace mo {
	Pistol::Pistol(Marco* marco, MarcoBottom* bottom)
		: unUsedParaglider(false)
		, player(marco)
		, playerBottom(bottom)
		, isBackToLife(false)
	{
	}
	Pistol::~Pistol()
	{
	}
	void Pistol::Initialize()
	{
	/*	player = GetPlayer();
		playerBottom = GetBottom();*/


		mState = player->GetMarcoState();
		mAnimator = player->GetComponent<Animator>();
		mRigidbody = player->GetComponent<RigidBody>();
		mTransform = player->GetComponent<Transform>();

		Image* mImageR = Resources::Load<Image>(L"PistolRight", L"..\\Resources\\Player\\PistolRight.bmp");
		Image* mImageL = Resources::Load<Image>(L"PistolLeft", L"..\\Resources\\Player\\PistolLeft.bmp");

		// Coulmn : 행	row : 열
		mAnimator->CreateAnimation(L"P_IdleR", mImageR, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 30, 30, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"P_IdleRT", mImageR, Vector2(120.0f * 0, 120.0f * 4), 120.0f, 30, 30, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"P_IdleL", mImageL, Vector2(120.0f * 29, 120.0f * 0), -120.0f, 30, 30, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"P_IdleLT", mImageL, Vector2(120.0f * 29, 120.0f * 4), -120.0f, 30, 30, 4, Vector2::Zero, 0.15);


		mAnimator->CreateAnimation(L"P_ShootR", mImageR, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 30, 30, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_ShootRT", mImageR, Vector2(120.0f * 0, 120.0f * 5), 120.0f, 30, 30, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_ShootL", mImageL, Vector2(120.0f * 29, 120.0f * 1), -120.0f, 30, 30, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_ShootLT", mImageL, Vector2(120.0f * 29, 120.0f * 5), -120.0f, 30, 30, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_ShootRB", mImageR, Vector2(120.0f * 0, 120.0f * 9), 120.0f, 30, 30, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_ShootLB", mImageL, Vector2(120.0f * 29, 120.0f * 9), -120.0f, 30, 30, 6, Vector2::Zero, 0.07);


		mAnimator->CreateAnimation(L"P_KnifeR", mImageR, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 30, 30, 6, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"P_KnifeL", mImageL, Vector2(120.0f * 29, 120.0f * 3), -120.0f, 30, 30, 6, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"P_MoveR", mImageR, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 30, 30, 12, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"P_MoveL", mImageL, Vector2(120.0f * 29, 120.0f * 2), -120.0f, 30, 30, 12, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"None", mImageR, Vector2(120.0f * 29, 120.0f * 0), 120.0f, 30, 60, 1, Vector2::Zero, 1.0);

		mAnimator->CreateAnimation(L"P_JumpIdleR", mImageR, Vector2(120.0f * 0, 120.0f * 6), 120.0f, 30, 30, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_JumpIdleL", mImageL, Vector2(120.0f * 29, 120.0f * 6), -120.0f, 30, 30, 6, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"P_JumpMoveR", mImageR, Vector2(120.0f * 0, 120.0f * 7), 120.0f, 30, 30, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_JumpMoveL", mImageL, Vector2(120.0f * 29, 120.0f * 7), -120.0f, 30, 30, 6, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"P_JumpDownR", mImageR, Vector2(120.0f * 0, 120.0f * 8), 120.0f, 30, 30, 3, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_JumpDownL", mImageL, Vector2(120.0f * 29, 120.0f * 8), -120.0f, 30, 30, 3, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"P_ThrowingBombR", mImageR, Vector2(120.0f * 0, 120.0f * 10), 120.0f, 30, 30, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_ThrowingBombL", mImageL, Vector2(120.0f * 29, 120.0f * 10), -120.0f, 30, 30,6, Vector2::Zero, 0.07);


		mAnimator->CreateAnimation(L"P_paraglider", mImageR, Vector2(120.0f * 0, 120.0f * 6), 120.0f, 30, 30, 6, Vector2::Zero, 0.05);

		mAnimator->GetStartEvent(L"P_ThrowingBombR") = std::bind(&Pistol::shootStartEvent, this);
		mAnimator->GetStartEvent(L"P_ThrowingBombL") = std::bind(&Pistol::shootStartEvent, this);
		mAnimator->GetStartEvent(L"P_KnifeR") = std::bind(&Pistol::shootStartEvent, this);
		mAnimator->GetStartEvent(L"P_KnifeL") = std::bind(&Pistol::shootStartEvent, this);
		mAnimator->GetStartEvent(L"P_ShootR") = std::bind(&Pistol::shootStartEvent, this);
		mAnimator->GetStartEvent(L"P_ShootL") = std::bind(&Pistol::shootStartEvent, this);
		mAnimator->GetStartEvent(L"P_ShootRT") = std::bind(&Pistol::shootStartEvent, this);
		mAnimator->GetStartEvent(L"P_ShootLT") = std::bind(&Pistol::shootStartEvent, this);
		mAnimator->GetStartEvent(L"P_ShootRB") = std::bind(&Pistol::shootStartEvent, this);
		mAnimator->GetStartEvent(L"P_ShootLB") = std::bind(&Pistol::shootStartEvent, this);

		mAnimator->GetCompleteEvent(L"P_ThrowingBombR") = std::bind(&Pistol::attackEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_ThrowingBombL") = std::bind(&Pistol::attackEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_KnifeR") = std::bind(&Pistol::attackEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_KnifeL") = std::bind(&Pistol::attackEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_ShootR") = std::bind(&Pistol::attackEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_ShootL") = std::bind(&Pistol::attackEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_ShootRT") = std::bind(&Pistol::attackEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_ShootLT") = std::bind(&Pistol::attackEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_ShootRB") = std::bind(&Pistol::attackEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_ShootLB") = std::bind(&Pistol::attackEndEvent, this);

		playerBottom->GetAnimator()->GetCompleteEvent(L"KnifeDeathR") = std::bind(&Pistol::deathEndEvent, this);
		playerBottom->GetAnimator()->GetCompleteEvent(L"KnifeDeathL") = std::bind(&Pistol::deathEndEvent, this);

		playerBottom->GetAnimator()->GetCompleteEvent(L"P_Resurrection") = std::bind(&Pistol::resurrectionEndEvent, this);

		
		
		mAnimator->Play(L"P_paraglider", false);
	}
	void Pistol::Update()
	{
		mState = player->GetMarcoState();

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

		player->SetMarcoState(mState);

		if (player->GetState() == GameObject::eState::Pause &&
			mState != Marco::eMarcoState::Death &&
			mAnimator->GetUseinvincibility() == false)
		{
			player->SetState(GameObject::eState::Active);
		}
	}

	void Pistol::paraglider()
	{
		eDirection mDirection = mTransform->GetDirection();

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
			playerBottom->SetIsGround(true);
			mRigidbody->SetGravity(Vector2(0.0f, 1500.0f));

			if (Input::GetKey(eKeyCode::Right))
			{
				mAnimator->Play(L"P_MoveR", true);
				mDirection = eDirection::Right;
				mState = Marco::eMarcoState::Move;
			}
			else if(Input::GetKey(eKeyCode::Left))
			{
				mAnimator->Play(L"P_MoveL", true);
				mDirection = eDirection::Left;
				mState = Marco::eMarcoState::Move;
			}
			else 
			{
				mAnimator->Play(L"P_IdleR", true);
				mState = Marco::eMarcoState::Idle;
			}
		}

		mTransform->SetDirection(mDirection);
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
			if (mDirection == eDirection::Left)
				mAnimator->Play(L"P_IdleL", true);
			if (mDirection == eDirection::Right)
				mAnimator->Play(L"P_IdleR", true);
			

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

			if (player->GetIsKnife()) {
				if (mDirection == eDirection::Right || mDirection == eDirection::RTop)
					mAnimator->Play(L"P_KnifeR", false);
				else if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
					mAnimator->Play(L"P_KnifeL", false);
			}
			else {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_ShootR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_ShootL", false);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"P_ShootRT", false);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"P_ShootLT", false);
			}
		}
		if (Input::GetKeyDown(eKeyCode::F)) {
			if (mDirection == eDirection::Right || mDirection == eDirection::RTop)
				mAnimator->Play(L"P_ThrowingBombR", false);
			else if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
				mAnimator->Play(L"P_ThrowingBombL", false);	
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
		if (mAnimator->GetUseinvincibility() == false &&
			isBackToLife)
		{
			isBackToLife = false;
			playerBottom->GetComponent<Transform>()->SetDisToBottom(Vector2{ 0.0f, -210.0f });
			playerBottom->GetAnimator()->Play(L"P_Resurrection", false);

		}
	}

	void Pistol::idle()
	{

		eDirection mDirection = mTransform->GetDirection();


		// To move
	
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			if (mDirection == eDirection::RTop || mDirection == eDirection::LTop)
			{
				mDirection = eDirection::RTop;
				mAnimator->Play(L"P_IdleRT", true);
			}
		
			else if (mDirection == eDirection::Right || mDirection == eDirection::Left)
			{
				mDirection = eDirection::Right;
				mAnimator->Play(L"P_MoveR", true);
			}
			
			mState = Marco::eMarcoState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			if (mDirection == eDirection::RTop || mDirection == eDirection::LTop)
			{
				mDirection = eDirection::LTop;
				mAnimator->Play(L"P_IdleLT", true);
			}
			else if (mDirection == eDirection::Right || mDirection == eDirection::Left)
			{
				mDirection = eDirection::Left;
				mAnimator->Play(L"P_MoveL", true);
			}

			mState = Marco::eMarcoState::Move;
		}

		//Idle
		if (Input::GetKey(eKeyCode::Up) && (mDirection == eDirection::Right)) {
			mDirection = eDirection::RTop;
			mAnimator->Play(L"P_IdleRT", true);
		}
		else if (Input::GetKey(eKeyCode::Up) && (mDirection == eDirection::Left)) {
			mDirection = eDirection::LTop;
			mAnimator->Play(L"P_IdleLT", true);
		}

		if (Input::GetKeyNone(eKeyCode::Up) && (mDirection == eDirection::RTop)) {
			mDirection = eDirection::Right;
			mAnimator->Play(L"P_IdleR", true);
		}
		else if (Input::GetKeyNone(eKeyCode::Up) && (mDirection == eDirection::LTop)) {
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
			
			if (mDirection == eDirection::Right || mDirection == eDirection::RTop)
				mAnimator->Play(L"P_JumpIdleR", false);
			if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
				mAnimator->Play(L"P_JumpIdleL", false);
			

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
					mAnimator->Play(L"P_KnifeR", false);
				else if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
					mAnimator->Play(L"P_KnifeL", false);
			}
			else {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_ShootR", false);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_ShootL", false);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"P_ShootRT", false);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"P_ShootLT", false);
			}
		}
		if (Input::GetKeyDown(eKeyCode::F)) {
			if (mDirection == eDirection::Right || mDirection == eDirection::RTop)
				mAnimator->Play(L"P_ThrowingBombR", false);
			else if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
				mAnimator->Play(L"P_ThrowingBombL", false);
		}
	}

	void Pistol::sit()
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
				if(!playerBottom->GetIsShooting())
					pos.x += 80.0f * Time::DeltaTime();
				mDirection = eDirection::Right;

			}


		if (Input::GetKeyUp(eKeyCode::Down)) {
			// 둘다 눌려있을때 
			if (Input::GetKey(eKeyCode::Right) && Input::GetKey(eKeyCode::Left))
			{
				if (mDirection == eDirection::Right)
				{
					mAnimator->Play(L"P_MoveR", true);
					mState = Marco::eMarcoState::Move;
				}
				else if (mDirection == eDirection::Left)
				{
					mAnimator->Play(L"P_MoveL", true);
					mState = Marco::eMarcoState::Move;
				}
			}
			else if (Input::GetKey(eKeyCode::Right))
			{
				mAnimator->Play(L"P_MoveR", true);
				mState = Marco::eMarcoState::Move;
			}
			else if (Input::GetKey(eKeyCode::Left))
			{
				mAnimator->Play(L"P_MoveL", true);
				mState = Marco::eMarcoState::Move;
			}
			else if (Input::GetKeyNone(eKeyCode::Right)
					&& Input::GetKeyNone(eKeyCode::Left)) {

				if (mDirection == eDirection::Right || mDirection == eDirection::RSit || mDirection == eDirection::RBottom) {
					mAnimator->Play(L"P_IdleR", true);
					mDirection = eDirection::Right;
				}

				if (mDirection == eDirection::Left || mDirection == eDirection::LSit || mDirection == eDirection::LBottom) {
					mAnimator->Play(L"P_IdleL", true);
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
				mAnimator->Play(L"P_JumpDownR", false);
			}
			if (mDirection == eDirection::Left ||mDirection == eDirection::LBottom) {
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

	void Pistol::jump()
	{
		
		eDirection mDirection = mTransform->GetDirection();
		Vector2 pos = mTransform->GetPos();


		//Junp
		if (mRigidbody->GetGround())
		{
			if (Input::GetKey(eKeyCode::Down)) 
			{
				if (mDirection == eDirection::Right || mDirection == eDirection::RBottom)
				{
					mAnimator->Play(L"None", false);
				}
				else if (mDirection == eDirection::Left || mDirection == eDirection::LBottom) 
				{
					mAnimator->Play(L"None", false);
				}

				playerBottom->SetIsGround(true);
				mState = Marco::eMarcoState::Sit;
			}
			else if (Input::GetKeyNone(eKeyCode::Down))
			{
				if (Input::GetKeyNone(eKeyCode::Left) && 
					Input::GetKeyNone(eKeyCode::Right))
				{
					if (mDirection == eDirection::RTop)
						mAnimator->Play(L"P_IdleRT", true);
					else if (mDirection == eDirection::LTop)
						mAnimator->Play(L"P_IdleLT", true);
					else if(mDirection == eDirection::Right)
						mAnimator->Play(L"P_IdleR", true);
					else if (mDirection == eDirection::Left)
						mAnimator->Play(L"P_IdleL", true);

					playerBottom->SetIsGround(true);
					mState = Marco::eMarcoState::Idle; 
				}

				else if (Input::GetKey(eKeyCode::Left) && Input::GetKey(eKeyCode::Right))
				{
					if (mDirection == eDirection::LTop)
						mAnimator->Play(L"P_IdleLT", true);
					else if (mDirection == eDirection::Left)
						mAnimator->Play(L"P_MoveL", true);
					else if (mDirection == eDirection::RTop)
						mAnimator->Play(L"P_IdleRT", true);
					else if (mDirection == eDirection::Right)
						mAnimator->Play(L"P_MoveR", true);

					playerBottom->SetIsGround(true);
					mState = Marco::eMarcoState::Move;
				}
				else if (Input::GetKey(eKeyCode::Left))
				{
					if (mDirection == eDirection::LTop)
						mAnimator->Play(L"P_IdleLT", true);
					else if(mDirection == eDirection::Left)
						mAnimator->Play(L"P_MoveL", true);
					
					playerBottom->SetIsGround(true);
					mState = Marco::eMarcoState::Move;
				}
				else if(Input::GetKey(eKeyCode::Right))
				{
					if (mDirection == eDirection::RTop) 
						mAnimator->Play(L"P_IdleRT", true);
					else if(mDirection == eDirection::Right)
						mAnimator->Play(L"P_MoveR", true);

					playerBottom->SetIsGround(true);
					mState = Marco::eMarcoState::Move;

				}
			}
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
			
			if (player->GetIsKnife()) {
				if (mDirection == eDirection::Right || mDirection == eDirection::RTop || mDirection == eDirection::RBottom)
					mAnimator->Play(L"P_KnifeR", false);
				else if (mDirection == eDirection::Left || mDirection == eDirection::LTop || mDirection == eDirection::LBottom)
					mAnimator->Play(L"P_KnifeL", false);
			}
			else {
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
			}
		
		}
		if (Input::GetKeyDown(eKeyCode::F)) {
			if (mDirection == eDirection::Right || mDirection == eDirection::RTop || mDirection == eDirection::RBottom)
				mAnimator->Play(L"P_ThrowingBombR", false);
			else if (mDirection == eDirection::Left || mDirection == eDirection::LTop || mDirection == eDirection::LBottom)
				mAnimator->Play(L"P_ThrowingBombL", false);
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
		Vector2 mPos = mTransform->GetPos();

		Scene* curScene = SceneManager::GetActiveScene();
		
		Animation* activeAnimation = mAnimator->GetActiveAnimation();
		Animation* prevAnimation = mAnimator->GetPrevAniamtion();

		if (mState == Marco::eMarcoState::Sit) {
			if (activeAnimation->GetName() == L"P_ThrowingBombR" ||
				activeAnimation->GetName() == L"P_ThrowingBombL" || 
				isBomb)
			{
				isBomb = false;

				PlayerBomb* bomb = new PlayerBomb();
				curScene->AddGameObject(bomb, eLayerType::PlayerBomb);
				bomb->Initialize();
				bomb->GetComponent<Transform>()->SetPos(mPos + Vector2(0.0f, 0.0f));
				bomb->PlayAnimation(mDirection);
			}
			else if (player->GetIsKnife())
			{
			}
			else
			{
				PistolBullet* pistolBullet = new PistolBullet();

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
			if (activeAnimation->GetName() == L"P_ThrowingBombR" ||
				activeAnimation->GetName() == L"P_ThrowingBombL"
				)
			{
				PlayerBomb* bomb = new PlayerBomb();
				curScene->AddGameObject(bomb, eLayerType::PlayerBomb);
				bomb->Initialize();
				bomb->GetComponent<Transform>()->SetPos(mPos + Vector2(0.0f, -30.0f));
				bomb->PlayAnimation(mDirection);
			}
			else if (player->GetIsKnife())
			{
			}
			else
			{
				PistolBullet* pistolBullet = new PistolBullet();

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
		
		

		

		if (prevAnimation->GetName() != L"P_ShootR" &&
			prevAnimation->GetName() != L"P_ShootRT" &&
			prevAnimation->GetName() != L"P_ShootL" &&
			prevAnimation->GetName() != L"P_ShootLT" &&
			prevAnimation->GetName() != L"P_ShootRB" &&
			prevAnimation->GetName() != L"P_ShootLB" &&
			prevAnimation->GetName() != L"P_KnifeR" &&
			prevAnimation->GetName() != L"P_KnifeL" &&
			prevAnimation->GetName() != L"P_ThrowingBombR" &&
			prevAnimation->GetName() != L"P_ThrowingBombL")
				mPrevAnimation = prevAnimation;

		//if(activeAnimation->GetName() != L"P_")
	}


	void Pistol::attackEndEvent()
	{
		Animation* activeAnimation = mAnimator->GetActiveAnimation();

			
		if (mRigidbody->GetGround() == false)
		{
			if (Input::GetKey(eKeyCode::Up))
			{
				if (Input::GetKey(eKeyCode::Right))
					mAnimator->Play(L"P_IdleRT", true);
				else if (Input::GetKey(eKeyCode::Left))
					mAnimator->Play(L"P_IdleLT", true);
			}
		}
		else 
			mAnimator->Play(mPrevAnimation->GetName(), true);
	}

	void Pistol::deathEndEvent()
	{
		if (!isBackToLife)
		{
			isBackToLife = true;
			mAnimator->SetUseinvincibility(true);
			playerBottom->GetAnimator()->SetUseinvincibility(true);
		}
	}

	void Pistol::resurrectionEndEvent()
	{
		eDirection mDirection = mTransform->GetDirection();
		eDirection mBottomDirection = playerBottom->GetComponent<Transform>()->GetDirection();
		playerBottom->GetComponent<Transform>()->SetDisToBottom(Vector2{ 0.0f, 50.0f });

		if (Input::GetKey(eKeyCode::Down))
		{
			if (Input::GetKey(eKeyCode::Right))
			{
				mAnimator->Play(L"None", true);
				playerBottom->GetAnimator()->Play(L"P_SitMoveR", true);
				mDirection = eDirection::RSit;
				mBottomDirection = eDirection::Right;
			}
			else if (Input::GetKey(eKeyCode::Left))
			{
				mAnimator->Play(L"None", true);
				playerBottom->GetAnimator()->Play(L"P_SitMoveL", true);
				mDirection = eDirection::LSit;
				mBottomDirection = eDirection::Left;

			}
			else if (Input::GetKeyNone(eKeyCode::Right) &&
					Input::GetKeyNone(eKeyCode::Left))
			{
				mAnimator->Play(L"None", true);
				playerBottom->GetAnimator()->Play(L"P_SitR", true);
				mDirection = eDirection::RSit;	
				mBottomDirection = eDirection::Right;

			}
			mTransform->SetDirection(mDirection);
			playerBottom->GetComponent<Transform>()->SetDirection(mBottomDirection);
			player->SetMarcoState(Marco::eMarcoState::Sit);
			playerBottom->SetBottomState(MarcoBottom::eMarcoState::Sit);
		}
		else if (Input::GetKeyNone(eKeyCode::Down))
		{
			if (Input::GetKey(eKeyCode::Right))
			{
				if (Input::GetKey(eKeyCode::Up))
				{
					mAnimator->Play(L"P_IdleRT", true);
					playerBottom->GetAnimator()->Play(L"MoveR", true);
					mDirection = eDirection::RTop;
					mBottomDirection = eDirection::Right;

				}
				else if (Input::GetKeyNone(eKeyCode::Up))
				{
					mAnimator->Play(L"P_MoveR", true);
					playerBottom->GetAnimator()->Play(L"MoveR", true);
					mDirection = eDirection::Right;
					mBottomDirection = eDirection::Right;
				}
				mTransform->SetDirection(mDirection);
				playerBottom->GetComponent<Transform>()->SetDirection(mBottomDirection);
				player->SetMarcoState(Marco::eMarcoState::Move);
				playerBottom->SetBottomState(MarcoBottom::eMarcoState::Move);
			}
			else if (Input::GetKey(eKeyCode::Left))
			{
				if (Input::GetKey(eKeyCode::Up))
				{
					mAnimator->Play(L"P_IdleLT", true);
					playerBottom->GetAnimator()->Play(L"MoveL", true);
					mDirection = eDirection::LTop;
					mBottomDirection = eDirection::Left;
				}
				else if (Input::GetKeyNone(eKeyCode::Up))
				{
					mAnimator->Play(L"P_MoveL", true);
					playerBottom->GetAnimator()->Play(L"MoveL", true);
					mDirection = eDirection::Left;
					mBottomDirection = eDirection::Left;
				}
				mTransform->SetDirection(mDirection);
				playerBottom->GetComponent<Transform>()->SetDirection(mBottomDirection);
				player->SetMarcoState(Marco::eMarcoState::Move);
				playerBottom->SetBottomState(MarcoBottom::eMarcoState::Move);
			}
			else if (Input::GetKeyNone(eKeyCode::Right) &&
					Input::GetKeyNone(eKeyCode::Left))
			{

				if (Input::GetKey(eKeyCode::Up))
				{
					mAnimator->Play(L"P_IdleRT", true);
					playerBottom->GetAnimator()->Play(L"IdleR", true);
					mDirection = eDirection::RTop;
					mBottomDirection = eDirection::Right;
				}
				else if (Input::GetKeyNone(eKeyCode::Up))
				{
					mAnimator->Play(L"P_IdleR", true);
					playerBottom->GetAnimator()->Play(L"IdleR", true);
					mDirection = eDirection::Right;
					mBottomDirection = eDirection::Right;
				}
				mTransform->SetDirection(mDirection);
				playerBottom->GetComponent<Transform>()->SetDirection(mBottomDirection);
				player->SetMarcoState(Marco::eMarcoState::Idle);
				playerBottom->SetBottomState(MarcoBottom::eMarcoState::Idle);

			}
		}
		mAnimator->SetUseinvincibility(true);
		playerBottom->GetAnimator()->SetUseinvincibility(true);
		
	}

	
}