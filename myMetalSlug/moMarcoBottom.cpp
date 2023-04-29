#include "moMarcoBottom.h"
#include "moImage.h"
#include "moSceneManager.h"
#include "moResources.h"
#include "moTransform.h"
#include "moInput.h"
#include "moTime.h"
#include "moAnimator.h"
#include "Collider.h"
#include "moScene.h"

namespace mo {
	MarcoBottom::MarcoBottom()
		: isGround(false)
		, mWeaponState(eMarcoWeapon::Pistol)
	{
	}
	MarcoBottom::~MarcoBottom()
	{
	}
	void MarcoBottom::Initialize()
	{
		Image* mImageR = Resources::Load<Image>(L"MarcoBottomRight", L"..\\Resources\\Player\\MarcoBottomRight.bmp");
		Image* mImageL = Resources::Load<Image>(L"MarcoBottomLeft", L"..\\Resources\\Player\\MarcoBottomLeft.bmp");
		Image* mImage = Resources::Load<Image>(L"PlayerResurrection", L"..\\Resources\\Player\\PlayerResurrection.bmp");
		
		mAnimator = AddComponent<Animator>();
		mAnimator->SetAlpha(true);

		mAnimator->CreateAnimation(L"P_Resurrection", mImage, Vector2(0.0f, 0.0f), 32.0f, 7, 1, 7, Vector2::Zero, 0.04);


		// Coulmn : 행	row : 열
		mAnimator->CreateAnimation(L"IdleR", mImageR, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 30, 30, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"MoveR", mImageR, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 30, 30, 12, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"IdleL", mImageL, Vector2(120.0f * 29, 120.0f * 0), -120.0f, 30, 30, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"MoveL", mImageL, Vector2(120.0f * 29, 120.0f * 2), -120.0f, 30, 30, 12, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"P_ReadySitR", mImageR, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 30, 30, 3, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"P_ReadySitL", mImageL, Vector2(120.0f * 29, 120.0f * 3), -120.0f, 30, 30, 3, Vector2::Zero, 0.03);

		mAnimator->CreateAnimation(L"P_SitR", mImageR, Vector2(120.0f * 0, 120.0f * 4), 120.0f, 30, 30, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"P_SitL", mImageL, Vector2(120.0f * 29, 120.0f * 4), -120.0f, 30, 30, 4, Vector2::Zero, 0.1);

		mAnimator->CreateAnimation(L"P_SitMoveR", mImageR, Vector2(120.0f * 0, 120.0f * 5), 120.0f, 30, 30, 7, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"P_SitMoveL", mImageL, Vector2(120.0f * 29, 120.0f * 5), -120.0f, 30, 30, 7, Vector2::Zero, 0.15);

		mAnimator->CreateAnimation(L"P_SitShootR", mImageR, Vector2(120.0f * 0, 120.0f * 6), 120.0f, 30, 30, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"P_SitShootL", mImageL, Vector2(120.0f * 29, 120.0f * 6), -120.0f, 30, 30, 10, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"M_ReadySitR", mImageR, Vector2(120.0f * 0, 120.0f * 12), 120.0f, 30, 30, 3, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"M_ReadySitL", mImageL, Vector2(120.0f * 29, 120.0f * 12), -120.0f, 30, 30, 3, Vector2::Zero, 0.03);

		mAnimator->CreateAnimation(L"M_SitR", mImageR, Vector2(120.0f * 0, 120.0f * 11), 120.0f, 30, 30, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"M_SitL", mImageL, Vector2(120.0f * 29, 120.0f * 11), -120.0f, 30, 30, 4, Vector2::Zero, 0.1);
	
		mAnimator->CreateAnimation(L"M_SitMoveR", mImageR, Vector2(120.0f * 0, 120.0f * 9), 120.0f, 30, 30, 7, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"M_SitMoveL", mImageL, Vector2(120.0f * 29, 120.0f * 9), -120.0f, 30, 30, 7, Vector2::Zero, 0.15);

		mAnimator->CreateAnimation(L"M_SitShootR", mImageR, Vector2(120.0f * 0, 120.0f * 10), 120.0f, 30, 30, 4, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"M_SitShootL", mImageL, Vector2(120.0f * 29, 120.0f * 10), -120.0f, 30, 30, 4, Vector2::Zero, 0.07);


		mAnimator->CreateAnimation(L"JumpIdleR", mImageR, Vector2(120.0f * 0, 120.0f * 7), 120.0f, 30, 30, 6, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"JumpIdleL", mImageL, Vector2(120.0f * 29, 120.0f * 7), -120.0f, 30, 30, 6, Vector2::Zero, 0.15);

		mAnimator->CreateAnimation(L"JumpMoveR", mImageR, Vector2(120.0f * 0, 120.0f * 8), 120.0f, 30, 30, 6, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"JumpMoveL", mImageL, Vector2(120.0f * 29, 120.0f * 8), -120.0f, 30, 30, 6, Vector2::Zero, 0.15);

		mAnimator->CreateAnimation(L"KnifeDeathR", mImageR, Vector2(120.0f * 0, 120.0f * 13), 120.0f, 30, 30, 19, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"KnifeDeathL", mImageL, Vector2(120.0f * 29, 120.0f * 13), -120.0f, 30, 30, 19, Vector2::Zero, 0.07);

		mAnimator->CreateAnimation(L"P_ThrowingBombR", mImageR, Vector2(120.0f * 0, 120.0f * 14), 120.0f, 30, 30, 6, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"P_ThrowingBombL", mImageL, Vector2(120.0f * 29, 120.0f * 14),-120.0f, 30, 30, 6, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"M_ThrowingBombR", mImageR, Vector2(120.0f * 0, 120.0f * 15), 120.0f, 30, 30, 6, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"M_ThrowingBombL", mImageL, Vector2(120.0f * 29, 120.0f * 15),-120.0f, 30, 30, 6, Vector2::Zero, 0.05);


		mAnimator->CreateAnimation(L"P_KnifeAttackR", mImageR, Vector2(120.0f * 0, 120.0f * 16), 120.0f, 30, 30, 7, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"P_KnifeAttackL", mImageL, Vector2(120.0f * 29, 120.0f * 16),-120.0f, 30, 30, 7, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"M_KnifeAttackR", mImageR, Vector2(120.0f * 0, 120.0f * 17), 120.0f, 30, 30, 7, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"M_KnifeAttackL", mImageL, Vector2(120.0f * 29, 120.0f * 17),-120.0f, 30, 30, 7, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"BombDeathR", mImageR, Vector2(120.0f * 0, 120.0f * 18), 120.0f, 30, 30, 19, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"BombDeathL", mImageL, Vector2(120.0f * 29, 120.0f * 18), -120.0f, 30, 30, 19, Vector2::Zero, 0.05);

		mAnimator->GetCompleteEvent(L"P_SitShootR") = std::bind(&MarcoBottom::shootEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_SitShootL") = std::bind(&MarcoBottom::shootEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_SitShootR") = std::bind(&MarcoBottom::shootEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_SitShootL") = std::bind(&MarcoBottom::shootEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_KnifeAttackR") = std::bind(&MarcoBottom::shootEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_KnifeAttackL") = std::bind(&MarcoBottom::shootEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_KnifeAttackR") = std::bind(&MarcoBottom::shootEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_KnifeAttackL") = std::bind(&MarcoBottom::shootEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_ThrowingBombR") = std::bind(&MarcoBottom::shootEndEvent, this);
		mAnimator->GetCompleteEvent(L"P_ThrowingBombL") = std::bind(&MarcoBottom::shootEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_ThrowingBombR") = std::bind(&MarcoBottom::shootEndEvent, this);
		mAnimator->GetCompleteEvent(L"M_ThrowingBombL") = std::bind(&MarcoBottom::shootEndEvent, this);
		//mAnimator->GetCompleteEvent(L"P_SitShootR") = std::bind(&MarcoBottom::shootEndEvent, this);
		//mAnimator->GetCompleteEvent(L"P_SitShootR") = std::bind(&MarcoBottom::shootEndEvent, this);
		//mAnimator->GetCompleteEvent(L"P_SitShootR") = std::bind(&MarcoBottom::shootEndEvent, this);
		//mAnimator->GetCompleteEvent(L"P_SitShootR") = std::bind(&MarcoBottom::shootEndEvent, this);


		mAnimator->Play(L"IdleR", true);

		mState = eMarcoState::Paraglider;



		GameObject::Initialize();
	}
	void MarcoBottom::Update()
	{

		switch (mState) {

		case mo::MarcoBottom::eMarcoState::Paraglider:
			paraglider();
			break;
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
			if(mWeaponState == eMarcoWeapon::Pistol)
				p_sit();
			else if (mWeaponState == eMarcoWeapon::Machinegun)
				m_sit();
			else if (mWeaponState == eMarcoWeapon::Shotgun)
				s_sit();
			else 				
				f_sit();
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

	void MarcoBottom::PlaySitAnimation()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();

		if (mWeaponState == eMarcoWeapon::Pistol) {

			if(mDirection == eDirection::Left)
				mAnimator->Play(L"P_SitMoveL", true);
			else
				mAnimator->Play(L"P_SitMoveR", true);
		}
		else if (mWeaponState == eMarcoWeapon::Machinegun) {

			if (mDirection == eDirection::Left)
				mAnimator->Play(L"M_SitMoveL", true);
			else
				mAnimator->Play(L"M_SitMoveR", true);
		}

	}



	void MarcoBottom::paraglider()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();

		if (isGround) {
			if (Input::GetKey(eKeyCode::Right))
			{
				mAnimator->Play(L"MoveR", true);
				mDirection = eDirection::Right;
				mState = eMarcoState::Move;
			}
			else if (Input::GetKey(eKeyCode::Left))
			{
				mAnimator->Play(L"MoveL", true);
				mDirection = eDirection::Left;
				mState = eMarcoState::Move;
			}
			else
			{
				mAnimator->Play(L"IdleR", true);
				mState = eMarcoState::Idle;
			}
		}

		tr->SetDirection(mDirection);
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
		if (Input::GetKeyUp(eKeyCode::Right))
			if (Input::GetKeyDown(eKeyCode::Left)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"MoveL", true);
			}
		if (Input::GetKeyUp(eKeyCode::Left))
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

			if (mWeaponState == eMarcoWeapon::Pistol) {
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_ReadySitL", false);
				else if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_ReadySitR", false);
			}
			else if (mWeaponState == eMarcoWeapon::Machinegun) {
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"M_ReadySitL", false);
				else if (mDirection == eDirection::Right)
					mAnimator->Play(L"M_ReadySitR", false);
			}

			mState = eMarcoState::Sit;
		}

		// ToJunp
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (Input::GetKey(eKeyCode::Right))
				mAnimator->Play(L"JumpMoveR", false);
			if (Input::GetKey(eKeyCode::Left))
				mAnimator->Play(L"JumpMoveL", false);

			isGround = false;
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

		// To Sit
		if (Input::GetKeyDown(eKeyCode::Down)) {

			if (mWeaponState == eMarcoWeapon::Pistol) {
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_ReadySitL", false);
				else if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_ReadySitR", false);
			}
			else if (mWeaponState == eMarcoWeapon::Machinegun) {
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"M_ReadySitL", false);
				else if (mDirection == eDirection::Right)
					mAnimator->Play(L"M_ReadySitR", false);
			}
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

			isGround = false;
			mState = eMarcoState::Jump;
		}

		


	}
	void MarcoBottom::p_sit()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();

		// 넘어 왔을때
		if ((mAnimator->GetActiveAnimation()->GetName() == L"P_ReadySitL" || mAnimator->GetActiveAnimation()->GetName() == L"P_ReadySitR")
			&& mAnimator->IsComplte())
		{
			isSitShooting = false;
			if(Input::GetKeyNone(eKeyCode::Right) && Input::GetKeyNone(eKeyCode::Left) ) {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_SitR", true);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_SitL", true);
			}

			else if (Input::GetKey(eKeyCode::Right) && Input::GetKey(eKeyCode::Left))
			{
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_SitMoveR", true);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_SitMoveL", true);
			}
			else if (Input::GetKey(eKeyCode::Right))
				mAnimator->Play(L"P_SitMoveR", true);
			else if (Input::GetKey(eKeyCode::Left))
				mAnimator->Play(L"P_SitMoveL", true);

		}
			//이동중
			if (Input::GetKey(eKeyCode::Right)) {
				mDirection = eDirection::Right;

				if (Input::GetKeyUp(eKeyCode::Down)) {
					mAnimator->Play(L"MoveR", true);
					mState = eMarcoState::Move;
				}
				if (Input::GetKeyDown(eKeyCode::Left))
					mAnimator->Play(L"P_SitR", true);


				if (Input::GetKeyUp(eKeyCode::Left))
					mAnimator->Play(L"P_SitMoveR", true);

			}
			if (Input::GetKey(eKeyCode::Left)) {
				mDirection = eDirection::Left;

				if (Input::GetKeyUp(eKeyCode::Down)) {
					mAnimator->Play(L"MoveL", true);
					mState = eMarcoState::Move;
				}
				if (Input::GetKeyDown(eKeyCode::Right))
					mAnimator->Play(L"P_SitL", true);

				if (Input::GetKeyUp(eKeyCode::Right))
					mAnimator->Play(L"P_SitMoveL", true);

			}

			if (Input::GetKeyNone(eKeyCode::Left) && !isSitShooting) {
				if (Input::GetKeyDown(eKeyCode::Right))
					mAnimator->Play(L"P_SitMoveR", true);
				if (Input::GetKeyUp(eKeyCode::Right))
					mAnimator->Play(L"P_SitR", true);
			}

			if (Input::GetKeyNone(eKeyCode::Right) && !isSitShooting) {
				if (Input::GetKeyDown(eKeyCode::Left))
					mAnimator->Play(L"P_SitMoveL", true);
				if (Input::GetKeyUp(eKeyCode::Left))
					mAnimator->Play(L"P_SitL", true);
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

		if (Input::GetKeyDown(eKeyCode::D)) 
		{
			isSitShooting = true;
			if (isKnife)
			{
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_KnifeAttackR", false);
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_KnifeAttackL", false);
			}
			else
			{
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_SitShootR", false);
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_SitShootL", false);
			}
		}
		if (Input::GetKeyDown(eKeyCode::F)) {
			isSitShooting = true;
			if (mDirection == eDirection::Right || mDirection == eDirection::RTop)
				mAnimator->Play(L"P_ThrowingBombR", false);
			else if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
				mAnimator->Play(L"P_ThrowingBombL", false);
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
			isGround = false;
			mState = eMarcoState::Jump;
		}
	}
	void MarcoBottom::m_sit()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();

		// 넘어 왔을때
		if ((mAnimator->GetActiveAnimation()->GetName() == L"M_ReadySitL" || mAnimator->GetActiveAnimation()->GetName() == L"M_ReadySitR")
			&& mAnimator->IsComplte())
		{
			isSitShooting = false;
			if (Input::GetKeyNone(eKeyCode::Right) && Input::GetKeyNone(eKeyCode::Left)) {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"M_SitR", true);
				else
					mAnimator->Play(L"M_SitL", true);
			}
			else if (Input::GetKey(eKeyCode::Right) && Input::GetKey(eKeyCode::Left))
			{
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"M_SitMoveR", true);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"M_SitMoveL", true);
			}
			else if (Input::GetKey(eKeyCode::Right))
				mAnimator->Play(L"M_SitMoveR", true);
			else if (Input::GetKey(eKeyCode::Left))
				mAnimator->Play(L"M_SitMoveL", true);
		}
	
		
			//이동중
			if (Input::GetKey(eKeyCode::Right)) {
				mDirection = eDirection::Right;

				if (Input::GetKeyUp(eKeyCode::Down)) {
					mAnimator->Play(L"MoveR", true);
					mState = eMarcoState::Move;
				}
				if (Input::GetKeyDown(eKeyCode::Left))
					mAnimator->Play(L"M_SitR", true);


				if (Input::GetKeyUp(eKeyCode::Left))
					mAnimator->Play(L"M_SitMoveR", true);

			}
			if (Input::GetKey(eKeyCode::Left)) {
				mDirection = eDirection::Left;

				if (Input::GetKeyUp(eKeyCode::Down)) {
					mAnimator->Play(L"MoveL", true);
					mState = eMarcoState::Move;
				}
				if (Input::GetKeyDown(eKeyCode::Right))
					mAnimator->Play(L"M_SitL", true);

				if (Input::GetKeyUp(eKeyCode::Right))
					mAnimator->Play(L"M_SitMoveL", true);

			}

			if (Input::GetKeyNone(eKeyCode::Left) && !isSitShooting) {
				if (Input::GetKeyDown(eKeyCode::Right))
					mAnimator->Play(L"M_SitMoveR", true);
				if (Input::GetKeyUp(eKeyCode::Right))
					mAnimator->Play(L"M_SitR", true);
			}

			if (Input::GetKeyNone(eKeyCode::Right) && !isSitShooting) {
				if (Input::GetKeyDown(eKeyCode::Left))
					mAnimator->Play(L"M_SitMoveL", true);
				if (Input::GetKeyUp(eKeyCode::Left))
					mAnimator->Play(L"M_SitL", true);
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

		if (Input::GetKeyDown(eKeyCode::D)) 
		{
			isSitShooting = true;
			if (isKnife)
			{
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"M_KnifeAttackR", false);
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"M_KnifeAttackL", false);
			}
			else
			{
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"M_SitShootR", false);
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"M_SitShootL", false);
			}
		}
		if (Input::GetKeyDown(eKeyCode::F)) {
			isSitShooting = true;
			if (mDirection == eDirection::Right || mDirection == eDirection::RTop)
				mAnimator->Play(L"M_ThrowingBombR", false);
			else if (mDirection == eDirection::Left || mDirection == eDirection::LTop)
				mAnimator->Play(L"M_ThrowingBombL", false);
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
			isGround = false;
			mState = eMarcoState::Jump;
		}
	}
	void MarcoBottom::s_sit()
	{
	}
	void MarcoBottom::f_sit()
	{
	}

	void MarcoBottom::jump()
	{

		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();


		if (isGround) {
			if (Input::GetKey(eKeyCode::Down))
			{
				if (mWeaponState == eMarcoWeapon::Pistol) {
					if (mDirection == eDirection::Left)
						mAnimator->Play(L"P_ReadySitL", false);
					else if (mDirection == eDirection::Right)
						mAnimator->Play(L"P_ReadySitR", false);
				}
				else if (mWeaponState == eMarcoWeapon::Machinegun) {
					if (mDirection == eDirection::Left)
						mAnimator->Play(L"M_ReadySitL", false);
					else if (mDirection == eDirection::Right)
						mAnimator->Play(L"M_ReadySitR", false);
				}
				mState = eMarcoState::Sit;
			}
			else 
			{

				if (Input::GetKeyNone(eKeyCode::Left) &&
					Input::GetKeyNone(eKeyCode::Right))
				{
					
					if (mDirection == eDirection::Right)
						mAnimator->Play(L"IdleR", true);
					else if (mDirection == eDirection::Left)
						mAnimator->Play(L"IdleL", true);

					mState = eMarcoState::Idle;
				}
				else if (Input::GetKey(eKeyCode::Left) && Input::GetKey(eKeyCode::Right))
				{
					if (mDirection == eDirection::Left)
						mAnimator->Play(L"MoveL", true);
					else if (mDirection == eDirection::Right)
						mAnimator->Play(L"MoveR", true);

					mState = eMarcoState::Move;
				}
				else if (Input::GetKey(eKeyCode::Left)) {
					mAnimator->Play(L"MoveL", true);
					mState = eMarcoState::Move;
				}
				else if (Input::GetKey(eKeyCode::Right)) {
					mAnimator->Play(L"MoveR", true);
					mState = eMarcoState::Move;
				}
					
			}
			
		}

		if (Input::GetKey(eKeyCode::Right)) {
			if (Input::GetKeyUp(eKeyCode::Left)) 
				mDirection = eDirection::Right;
		}
		if (Input::GetKey(eKeyCode::Left)) {
			if (Input::GetKeyUp(eKeyCode::Right)) 
				mDirection = eDirection::Left;
		}

		if (Input::GetKeyNone(eKeyCode::Right))
			if (Input::GetKeyDown(eKeyCode::Left)) {
				mDirection = eDirection::Left;
			}
		if (Input::GetKeyNone(eKeyCode::Left))
			if (Input::GetKeyDown(eKeyCode::Right)) {
				mDirection = eDirection::Right;
			}

			tr->SetDirection(mDirection);
		
	}
	void MarcoBottom::shootEndEvent()
	{
		isSitShooting = false;

		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();

		if (mWeaponState == eMarcoWeapon::Pistol)
		{
			if (Input::GetKeyNone(eKeyCode::Right) && Input::GetKeyNone(eKeyCode::Left)) {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_SitR", true);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_SitL", true);
			}
			else if (Input::GetKey(eKeyCode::Right))
				mAnimator->Play(L"P_SitMoveR", true);
			else if (Input::GetKey(eKeyCode::Left))
				mAnimator->Play(L"P_SitMoveL", true);
		}
		else if (mWeaponState == eMarcoWeapon::Machinegun)  
		{
			if (Input::GetKeyNone(eKeyCode::Right) && Input::GetKeyNone(eKeyCode::Left)) {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"M_SitR", true);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"M_SitL", true);
			}
			else if (Input::GetKey(eKeyCode::Right))
				mAnimator->Play(L"M_SitMoveR", true);
			else if (Input::GetKey(eKeyCode::Left))
				mAnimator->Play(L"M_SitMoveL", true);
		}
		/*else if (mWeaponState == eMarcoWeapon::Shotgun)
		{
			if (Input::GetKeyNone(eKeyCode::Right) && Input::GetKeyNone(eKeyCode::Left)) {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_SitR", true);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_SitL", true);
			}
			else if (Input::GetKey(eKeyCode::Right))
				mAnimator->Play(L"P_SitMoveR", true);
			else if (Input::GetKey(eKeyCode::Left))
				mAnimator->Play(L"P_SitMoveL", true);
		}
		else if (mWeaponState == eMarcoWeapon::Firegun)
		{
			if (Input::GetKeyNone(eKeyCode::Right) && Input::GetKeyNone(eKeyCode::Left)) {
				if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_SitR", true);
				else if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_SitL", true);
			}
			else if (Input::GetKey(eKeyCode::Right))
				mAnimator->Play(L"P_SitMoveR", true);
			else if (Input::GetKey(eKeyCode::Left))
				mAnimator->Play(L"P_SitMoveL", true);
		}*/
		
	}
}