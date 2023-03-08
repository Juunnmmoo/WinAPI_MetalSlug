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
	Marco::Marco()
	{
	}
	Marco::~Marco()
	{
	}
	void Marco::Initialize()
	{
		Image* mImageR = Resources::Load<Image>(L"MarcoTopRight", L"..\\Resources\\MarcoTopRight.bmp");
		Image* mImageL = Resources::Load<Image>(L"MarcoTopLeft", L"..\\Resources\\MarcoTopLeft.bmp");
		mAnimator = AddComponent<Animator>();
		Transform* tr;
		tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 100.0f, 500.0f });
		tr->SetScale(Vector2{ 2.5f, 2.5f });
		tr->SetTopDiff(Vector2{ 0.0f, 50.0f });
		
		// Coulmn : 행	row : 열
		mAnimator->CreateAnimation(L"IdleR", mImageR, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"ShootR", mImageR, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 30, 60, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"MoveR", mImageR, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 30, 60, 12, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"IdleL", mImageL, Vector2(120.0f * 29, 120.0f * 0), -120.0f, 30, 60, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"ShootL", mImageL, Vector2(120.0f * 29, 120.0f * 1), -120.0f, 30, 60, 10, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"MoveL", mImageL, Vector2(120.0f * 29, 120.0f * 2), -120.0f, 30, 60, 12, Vector2::Zero, 0.05);

		mAnimator->GetStartEvent(L"ShootR") = std::bind(&Marco::shootStartEvent, this);
		mAnimator->GetStartEvent(L"ShootL") = std::bind(&Marco::shootStartEvent, this);

		mAnimator->Play(L"IdleR", true);
		//mAnimatorL->Play(L"IdleL", true);
		mState = eMarcoState::Idle;

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{60.0f, 70.0f});
		mCollider->SetCenter(Vector2{ -30.50f, -70.0f });
		
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
		default:
			break;
		}

		GameObject::Update();
	}
	void Marco::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}

	void Marco::move()
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
		/*if ((Input::GetKeyNone(eKeyCode::Right)
			&& Input::GetKeyNone(eKeyCode::Left))
			|| (Input::GetKey(eKeyCode::Right)
				&& Input::GetKey(eKeyCode::Left)))
		{
			if (mDirection == eDirection::Right)
				mAnimator->Play(L"IdleR", true);
			else if (mDirection == eDirection::Left)
				mAnimator->Play(L"IdleL", true);

			mState = eMarcoState::Idle;

		}*/

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

		//(Input::GetKey(eKeyCode::Right)
		//	&& Input::GetKey(eKeyCode::Left))

		// Shooting
		if (Input::GetKeyDown(eKeyCode::D)) {

			if (mDirection == eDirection::Right)
				mAnimator->Play(L"ShootR", false);

			else if (mDirection == eDirection::Left)
				mAnimator->Play(L"ShootL", false);

		}



		Animator* mAnimator = GetComponent<Animator>();

		if (Input::GetKey(eKeyCode::Left))
		{
			pos.x -= 150.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::Right))
		{
			pos.x += 150.0f * Time::DeltaTime();
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

		
		// Shooting
		if (Input::GetKeyDown(eKeyCode::D)) {

			if (mDirection == eDirection::Right) 
				mAnimator->Play(L"ShootR", false);
			
			else if (mDirection == eDirection::Left) 
				mAnimator->Play(L"ShootL", false);

		}

		
	}

	void Marco::shootStartEvent()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();

		if (mDirection == eDirection::Right) {
		
			Scene* curScene = SceneManager::GetActiveScene();
			BaseBullet* bullet = new BaseBullet();
			bullet->SetDirection(eDirection::Right);

			Transform* tr;
			tr = GetComponent<Transform>();
			bullet->GetComponent<Transform>()->SetPos(tr->GetPos());
			curScene->AddGameObject(bullet, eLayerType::Bullet);
		}
		else if (mDirection == eDirection::Left) {
		
			Scene* curScene = SceneManager::GetActiveScene();
			BaseBullet* bullet = new BaseBullet();
			bullet->SetDirection(eDirection::Left);

			Transform* tr;
			tr = GetComponent<Transform>();
			bullet->GetComponent<Transform>()->SetPos(tr->GetPos());
			curScene->AddGameObject(bullet, eLayerType::Bullet);
		}

	}
}