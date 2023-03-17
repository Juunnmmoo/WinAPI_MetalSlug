#include "moMarcoBottom.h"
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
	MarcoBottom::MarcoBottom()
		: isJump(false)
	{
	}
	MarcoBottom::~MarcoBottom()
	{
	}
	void MarcoBottom::Initialize()
	{
		Image* mImageR = Resources::Load<Image>(L"MarcoBottomRight", L"..\\Resources\\Player\\MarcoBottomRight.bmp");
		Image* mImageL = Resources::Load<Image>(L"MarcoBottomLeft", L"..\\Resources\\Player\\MarcoBottomLeft.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->SetAlpha(true);


		// Coulmn : 행	row : 열
		mAnimator->CreateAnimation(L"IdleR", mImageR, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 15, 15, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"MoveR", mImageR, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 15, 15, 12, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"IdleL", mImageL, Vector2(120.0f * 14, 120.0f * 0), -120.0f, 15, 15, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"MoveL", mImageL, Vector2(120.0f * 14, 120.0f * 2), -120.0f, 15, 15, 12, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"ReadySitR", mImageR, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 15, 15, 3, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"ReadySitL", mImageL, Vector2(120.0f * 14, 120.0f * 3), -120.0f, 15, 15, 3, Vector2::Zero, 0.03);

		mAnimator->CreateAnimation(L"SitR", mImageR, Vector2(120.0f * 0, 120.0f * 4), 120.0f, 15, 15, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"SitL", mImageL, Vector2(120.0f * 14, 120.0f * 4), -120.0f, 15, 15, 4, Vector2::Zero, 0.1);

		mAnimator->CreateAnimation(L"SitMoveR", mImageR, Vector2(120.0f * 0, 120.0f * 5), 120.0f, 15, 15, 7, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"SitMoveL", mImageL, Vector2(120.0f * 14, 120.0f * 5), -120.0f, 15, 15, 7, Vector2::Zero, 0.15);

		mAnimator->CreateAnimation(L"SitShootR", mImageR, Vector2(120.0f * 0, 120.0f * 6), 120.0f, 15, 15, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"SitShootL", mImageL, Vector2(120.0f * 14, 120.0f * 6), -120.0f, 15, 15, 10, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"JumpIdleR", mImageR, Vector2(120.0f * 0, 120.0f * 7), 120.0f, 15, 15, 6, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"JumpIdleL", mImageL, Vector2(120.0f * 14, 120.0f * 7), -120.0f, 15, 15, 6, Vector2::Zero, 0.15);

		mAnimator->CreateAnimation(L"JumpMoveR", mImageR, Vector2(120.0f * 0, 120.0f * 8), 120.0f, 15, 15, 6, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"JumpMoveL", mImageL, Vector2(120.0f * 14, 120.0f * 8), -120.0f, 15, 15, 6, Vector2::Zero, 0.15);


		mAnimator->Play(L"IdleR", true);

		mState = eMarcoState::Idle;



		GameObject::Initialize();
	}
	void MarcoBottom::Update()
	{

		switch (mState) {

		case mo::MarcoBottom::eMarcoState::Move:
			move();
			break;
		case mo::MarcoBottom::eMarcoState::Shoot:
			shoot();
			break;
		case mo::MarcoBottom::eMarcoState::Death:
			death();
			break;
		case mo::MarcoBottom::eMarcoState::Idle:
			idle();
			break;
		case mo::MarcoBottom::eMarcoState::Sit:
			sit();
			break;
		case mo::MarcoBottom::eMarcoState::Jump:
			jump();
			break;
		default:
			break;
		}

		GameObject::Update();
	}
	void MarcoBottom::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}



	void MarcoBottom::move()
	{

		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();

		// 좌우 애니메이션
		if (Input::GetKey(eKeyCode::Right)) {
			if (Input::GetKeyDown(eKeyCode::Left)) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"IdleR", true);
			}
			if (Input::GetKeyUp(eKeyCode::Left)) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"MoveR", true);
			}
		}

		if (Input::GetKey(eKeyCode::Left)) {
			if (Input::GetKeyDown(eKeyCode::Right)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"IdleL", true);
			}
			if (Input::GetKeyUp(eKeyCode::Right)) {
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
		if ((Input::GetKeyNone(eKeyCode::Right)
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

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"ReadySitL", false);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"ReadySitR", false);
			mState = eMarcoState::Sit;

		}

		// ToJunp
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (Input::GetKey(eKeyCode::Right))
				mAnimator->Play(L"JumpMoveR", false);
			if (Input::GetKey(eKeyCode::Left))
				mAnimator->Play(L"JumpMoveL", false);

			isJump = true;
			mState = eMarcoState::Jump;
		}


	}
	void MarcoBottom::shoot()
	{
	}
	void MarcoBottom::death()
	{
	}
	void MarcoBottom::idle()
	{

		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();

		// To move
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

		// To Sit
		if (Input::GetKeyDown(eKeyCode::Down)) {

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"ReadySitL", false);
			else if (mDirection == eDirection::Right)
				mAnimator->Play(L"ReadySitR", false);
			mState = eMarcoState::Sit;

		}
		tr->SetDirection(mDirection);

		//Junp
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDirection == eDirection::Right)
				mAnimator->Play(L"JumpIdleR", false);
			if (mDirection == eDirection::Left)
				mAnimator->Play(L"JumpIdleL", false);

			isJump = true;
			mState = eMarcoState::Jump;
		}

		


	}
	void MarcoBottom::sit()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();

		// 넘어 왔을때
		if ((mAnimator->GetActiveAnimation()->GetName() == L"ReadySitL" || mAnimator->GetActiveAnimation()->GetName() == L"ReadySitR")
			&& mAnimator->IsComplte())
		{
			if (Input::GetKey(eKeyCode::Right))
				mAnimator->Play(L"SitMoveR", true);
			if (Input::GetKey(eKeyCode::Left))
				mAnimator->Play(L"SitMoveL", true);

			if (Input::GetKeyNone(eKeyCode::Right) && Input::GetKeyNone(eKeyCode::Left)) {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"SitR", true);
				else
					mAnimator->Play(L"SitL", true);
			}
		}

		//이동중
		if (Input::GetKey(eKeyCode::Right)) {
			mDirection = eDirection::Right;

			if (Input::GetKeyUp(eKeyCode::Down)) {
				mAnimator->Play(L"MoveR", true);
				mState = eMarcoState::Move;
			}
			if (Input::GetKeyDown(eKeyCode::Left))
				mAnimator->Play(L"SitR", true);


			if (Input::GetKeyUp(eKeyCode::Left))
				mAnimator->Play(L"SitMoveR", true);

		}
		if (Input::GetKey(eKeyCode::Left)) {
			mDirection = eDirection::Left;

			if (Input::GetKeyUp(eKeyCode::Down)) {
				mAnimator->Play(L"MoveL", true);
				mState = eMarcoState::Move;
			}
			if (Input::GetKeyDown(eKeyCode::Right))
				mAnimator->Play(L"SitL", true);

			if (Input::GetKeyUp(eKeyCode::Right))
				mAnimator->Play(L"SitMoveL", true);

		}

		if (Input::GetKeyNone(eKeyCode::Left)) {
			if (Input::GetKeyDown(eKeyCode::Right))
				mAnimator->Play(L"SitMoveR", true);
			if (Input::GetKeyUp(eKeyCode::Right))
				mAnimator->Play(L"SitR", true);
		}

		if (Input::GetKeyNone(eKeyCode::Right)) {
			if (Input::GetKeyDown(eKeyCode::Left))
				mAnimator->Play(L"SitMoveL", true);
			if (Input::GetKeyUp(eKeyCode::Left))
				mAnimator->Play(L"SitL", true);
		}

		// To Idle
		if (Input::GetKeyUp(eKeyCode::Down)
			&& Input::GetKeyNone(eKeyCode::Right)
			&& Input::GetKeyNone(eKeyCode::Left)

			)
		{
			if (mDirection == eDirection::Right)
				mAnimator->Play(L"IdleR", true);
			else if (mDirection == eDirection::Left)
				mAnimator->Play(L"IdleL", true);
			mState = eMarcoState::Idle;
		}

		


		tr->SetDirection(mDirection);

		if (Input::GetKeyDown(eKeyCode::D)
			&& Input::GetKeyNone(eKeyCode::Right)
			&& Input::GetKeyNone(eKeyCode::Left)) {
			if (mDirection == eDirection::Right)
				mAnimator->Play(L"SitShootR", false);
			if (mDirection == eDirection::Left)
				mAnimator->Play(L"SitShootL", false);
		}

		// ToJunp
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (Input::GetKey(eKeyCode::Right))
				mAnimator->Play(L"JumpMoveR", false);
			else if (Input::GetKey(eKeyCode::Left))
				mAnimator->Play(L"JumpMoveL", false);
			else {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"JumpIdleR", false);
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"JumpIdleL", false);
			}
			isJump = true;
			mState = eMarcoState::Jump;
		}
	}

	void MarcoBottom::jump()
	{

		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();

		if (isJump == false) {

		/*	if (Input::GetKey(eKeyCode::Down)) {
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"ReadySitL", false);
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"ReadySitR", false);

				mState = eMarcoState::Sit;
			}*/
			
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"MoveL", true);
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"MoveR", true);
				mState = eMarcoState::Move;
			
		}

			if (Input::GetKeyDown(eKeyCode::Left))
				mDirection = eDirection::Left;

			if (Input::GetKeyDown(eKeyCode::Right))
				mDirection = eDirection::Right;


			/*if (Input::GetKeyDown(eKeyCode::D)) {
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"JumpIdleL", false);
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"JumpIdleR", false);
			}*/
		
			tr->SetDirection(mDirection);
		
	}
}