#include "moBoss1_CurtainOpen.h"
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
	Boss1_CurtainOpen::Boss1_CurtainOpen()
	{
	}
	Boss1_CurtainOpen::~Boss1_CurtainOpen()
	{
	}
	void Boss1_CurtainOpen::Initialize()
	{
		Image* mImage = Resources::Load<Image>(L"Boss1_CurtainOpen", L"..\\Resources\\Enemy\\Boss1\\Boss1_CurtainOpen.bmp");


		Transform* tr;
		tr = GetComponent<Transform>();

		mAnimator = AddComponent<Animator>();

		mAnimator->SetUnUseCameraY(true);
		mAnimator->CreateAnimation(L"OpenMiddle", mImage, Vector2(224.0f * 0, 224.0f * 0), 224.0f, 14, 3, 13, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"OpenLeft", mImage, Vector2(224.0f * 0, 224.0f * 1), 224.0f, 14, 3, 13, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"OpenRight", mImage, Vector2(224.0f * 0, 224.0f * 2), 224.0f, 14, 3, 13, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"None", mImage, Vector2(224.0f * 13, 59.0f * 2), 224.0f, 14, 3, 1, Vector2::Zero, 0.07);

		mAnimator->Play(L"None", false);

		GameObject::Initialize();
	}
	void Boss1_CurtainOpen::Update()
	{
		GameObject::Update();

	}
	void Boss1_CurtainOpen::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void Boss1_CurtainOpen::OnCollisionEnter(Collider* other)
	{
	}
	void Boss1_CurtainOpen::OnCollisionStay(Collider* other)
	{
	}
	void Boss1_CurtainOpen::OnCollisionExit(Collider* other)
	{
	}
}
