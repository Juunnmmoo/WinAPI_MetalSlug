#include "moPlayerIdleBottom.h"
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
	PlayerIdleBottom::PlayerIdleBottom()
	{
	}
	PlayerIdleBottom::~PlayerIdleBottom()
	{
	}
	void PlayerIdleBottom::Initialize()
	{
		Image* mImageR = Resources::Load<Image>(L"MarcoBottomRight", L"..\\Resources\\Player\\MarcoBottomRight.bmp");
		
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"IdleR", mImageR, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 30, 30, 1, Vector2::Zero, 0.1);

		mAnimator->Play(L"IdleR", true);


		GameObject::Initialize();
	}
	void PlayerIdleBottom::Update()
	{
		GameObject::Update();

	}
	void PlayerIdleBottom::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void PlayerIdleBottom::OnCollisionEnter(Collider* other)
	{
	}
	void PlayerIdleBottom::OnCollisionStay(Collider* other)
	{
	}
	void PlayerIdleBottom::OnCollisionExit(Collider* other)
	{
	}
}