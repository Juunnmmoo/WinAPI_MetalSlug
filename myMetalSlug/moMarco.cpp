#include "moMarco.h"
#include "moImage.h"
#include "moResources.h"
#include "moTransform.h"
#include "moInput.h"
#include "moTime.h"
#include "moAnimator.h"

namespace mo {
	Marco::Marco()
	{
	}
	Marco::~Marco()
	{
	}
	void Marco::Initialize()
	{
		Image* mImage = Resources::Load<Image>(L"TestPlayer", L"..\\Resources\\TestPlayerTop.bmp");
		mAnimator = AddComponent<Animator>();
		
		mAnimator->CreateAnimation(L"Idle", mImage, Vector2::Zero, 10, 2, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Move", mImage, Vector2::Zero, 10, 2, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Drink", mImage, Vector2(0.0f, 130.0f), 10, 2, 10, Vector2::Zero, 0.1);

		mAnimator->Play(L"Idle", true);
		mState = eMarcoState::Idle;

		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 50.0f, 50.0f });

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
		if (Input::GetKeyNone(eKeyCode::Up)
			&& Input::GetKeyNone(eKeyCode::Down)
			&& Input::GetKeyNone(eKeyCode::Right)
			&& Input::GetKeyNone(eKeyCode::Left))
		{
			mState = eMarcoState::Idle;
			mAnimator->Play(L"Drink", true);
		}
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Animator* mAnimator = GetComponent<Animator>();

		if (Input::GetKey(eKeyCode::Left))
		{
			pos.x -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::Right))
		{
			pos.x += 100.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::Up))
		{
			pos.y -= 100.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::Down))
		{
			pos.y += 100.0f * Time::DeltaTime();
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
		if (Input::GetKeyDown(eKeyCode::Up)
			|| Input::GetKeyDown(eKeyCode::Down)
			|| Input::GetKeyDown(eKeyCode::Right)
			|| Input::GetKeyDown(eKeyCode::Left))
		{
			mState = eMarcoState::Move;
			mAnimator->Play(L"Move", true);
		}
	}
}