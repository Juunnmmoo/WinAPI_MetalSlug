#include "moPlayerIdle.h"
#include "moImage.h"
#include "moResources.h"
#include "moTransform.h"
#include "moTime.h"
#include "Collider.h"
#include "moObject.h"
#include "moInput.h"
#include "moCamera.h"
#include "moMarco.h"
#include "moObject.h"
#include "moRigidBody.h"
#include "moAnimator.h"

namespace mo {
	PlayerIdle::PlayerIdle()
	{
	}
	PlayerIdle::~PlayerIdle()
	{
	}
	void PlayerIdle::Initialize()
	{
		Image* mImageR = Resources::Load<Image>(L"PistolRight", L"..\\Resources\\Player\\PistolRight.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->SetunUseCameraPos(true);
		mAnimator->CreateAnimation(L"P_IdleR", mImageR, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 30, 30, 4, Vector2::Zero, 0.15);

		mAnimator->Play(L"P_IdleR", true);

		GameObject::Initialize();

	}
	void PlayerIdle::Update()
	{
		GameObject::Update();

	}
	void PlayerIdle::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void PlayerIdle::OnCollisionEnter(Collider* other)
	{
	}
	void PlayerIdle::OnCollisionStay(Collider* other)
	{
	}
	void PlayerIdle::OnCollisionExit(Collider* other)
	{
	}
}