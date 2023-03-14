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
	{
	}
	MarcoBottom::~MarcoBottom()
	{
	}
	void MarcoBottom::Initialize()
	{
		Image* mImageR = Resources::Load<Image>(L"MarcoBottomRight", L"..\\Resources\\MarcoBottomRight.bmp");
		Image* mImageL = Resources::Load<Image>(L"MarcoBottomLeft", L"..\\Resources\\MarcoBottomLeft.bmp");
		mAnimator = AddComponent<Animator>();
		Transform* tr;
		tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 100.0f, 600.0f });
		tr->SetScale(Vector2{ 3.0f, 3.0f });
		tr->SetTopDiff(Vector2{ 0.0f, 50.0f });

		// Coulmn : 행	row : 열
		mAnimator->CreateAnimation(L"IdleR", mImageR, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 15, 15, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"MoveR", mImageR, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 15, 15, 12, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"IdleL", mImageL, Vector2(120.0f * 14, 120.0f * 0), -120.0f, 15, 15, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"MoveL", mImageL, Vector2(120.0f * 14, 120.0f * 2), -120.0f, 15, 15, 12, Vector2::Zero, 0.05);


		mAnimator->Play(L"IdleR", true);
		//mAnimatorL->Play(L"IdleL", true);
		mState = eMarcoState::Idle;

		/*Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 60.0f, 70.0f });
		mCollider->SetLeftTop(Vector2{ -30.50f, -70.0f });*/

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
		Vector2 pos = tr->GetPos();

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
		else
		{
			if (Input::GetKeyDown(eKeyCode::Left)) {
				mDirection = eDirection::Left;
				mAnimator->Play(L"MoveL", true);
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
		else
		{
			if (Input::GetKeyDown(eKeyCode::Right)) {
				mDirection = eDirection::Right;
				mAnimator->Play(L"MoveR", true);
			}
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
		
		tr->SetDirection(mDirection);


	}
}