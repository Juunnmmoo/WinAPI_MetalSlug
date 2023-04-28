#include "moBoss1_WindowOpen.h"
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
#include "moCamera.h"
#include "moScene.h"
#include "moMachinegun.h"
#include "moAnimator.h"

namespace mo {
	Boss1_WindowOpen::Boss1_WindowOpen()
	{
	}
	Boss1_WindowOpen::~Boss1_WindowOpen()
	{
	}
	void Boss1_WindowOpen::Initialize()
	{
		Image* mImage = Resources::Load<Image>(L"Boss1_Door", L"..\\Resources\\Enemy\\Boss1\\Boss1_DoorOpen.bmp");


		Transform* tr;
		tr = GetComponent<Transform>();

		mAnimator = AddComponent<Animator>();
		mAnimator->SetUnUseCameraY(true);

		mAnimator->CreateAnimation(L"Idle", mImage, Vector2(316.0f * 0, 316.0f * 0), 315.0f, 17, 1, 1, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"Open", mImage, Vector2(316.0f * 0, 316.0f * 0), 315.0f, 17, 1, 16, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"None", mImage, Vector2(316.0f * 16, 316.0f * 0), 315.0f, 17, 1, 1, Vector2::Zero, 0.07);


		mAnimator->Play(L"Idle", false);

		GameObject::Initialize();
	}
	void Boss1_WindowOpen::Update()
	{
		GameObject::Update();
	}
	void Boss1_WindowOpen::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}
	void Boss1_WindowOpen::OnCollisionEnter(Collider* other)
	{
	}
	void Boss1_WindowOpen::OnCollisionStay(Collider* other)
	{
	}
	void Boss1_WindowOpen::OnCollisionExit(Collider* other)
	{
	}
}
