#include "moBoss1_CurtainIdle.h"
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
	Boss1_CurtainIdle::Boss1_CurtainIdle()
	{
	}
	Boss1_CurtainIdle::~Boss1_CurtainIdle()
	{
	}
	void Boss1_CurtainIdle::Initialize()
	{
		Image* mImageIdle = Resources::Load<Image>(L"Boss1_CurtainIdle", L"..\\Resources\\Enemy\\Boss1\\Boss1_CurtainIdle.bmp");

		Transform* tr;
		tr = GetComponent<Transform>();
		tr->SetScale(Vector2(3.5f, 3.5f));

		mAnimator = AddComponent<Animator>();

		mAnimator->SetUnUseCameraY(true);
		mAnimator->CreateAnimation(L"IdleMiddle", mImageIdle, Vector2(48.0f * 0, 59.0f* 0), 48.0f, 7, 3, 6, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"IdleLeft", mImageIdle, Vector2(48.0f * 0, 59.0f * 1), 48.0f, 7, 3, 6, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"IdleRight", mImageIdle, Vector2(48.0f * 0, 59.0f * 2), 48.0f, 7, 3, 6, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"None", mImageIdle, Vector2(48.0f * 6, 59.0f * 2), 48.0f, 7, 3, 1, Vector2::Zero, 0.1);
			
		GameObject::Initialize();
	}
	void Boss1_CurtainIdle::Update()
	{
		GameObject::Update();

	}
	void Boss1_CurtainIdle::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void Boss1_CurtainIdle::OnCollisionEnter(Collider* other)
	{
	}
	void Boss1_CurtainIdle::OnCollisionStay(Collider* other)
	{
	}
	void Boss1_CurtainIdle::OnCollisionExit(Collider* other)
	{
	}
}
