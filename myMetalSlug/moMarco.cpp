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
		Animator* mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"TestPlayerStay", mImage, Vector2::Zero, 10, 2, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"TestPlayerDrink", mImage, Vector2(0.0f, 130.0f), 10, 2, 10, Vector2::Zero, 0.1);

		mAnimator->Play(L"TestPlayerStay", true);

		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 50.0f, 50.0f });

		GameObject::Initialize();
	}
	void Marco::Update()
	{

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Animator* mAnimator = GetComponent<Animator>();

		if (Input::GetKeyState(eKeyCode::A) == eKeyState::Pressed)
		{
			pos.x -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::Pressed)
		{
			pos.x += 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::W) == eKeyState::Pressed)
		{
			pos.y -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::Q) == eKeyState::Down)
		{
			mAnimator->Play(L"TestPlayerDrink", true);
		}
		if (Input::GetKeyState(eKeyCode::Q) == eKeyState::Up)
		{
			mAnimator->Play(L"TestPlayerStay", true);
		}
		if (Input::GetKeyState(eKeyCode::S) == eKeyState::Pressed)
		{
			pos.y += 100.0f * Time::DeltaTime();
		}
		tr->SetPos(pos);
		GameObject::Update();
	}
	void Marco::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}
}