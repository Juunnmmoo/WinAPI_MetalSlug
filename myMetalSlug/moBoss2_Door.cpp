#include "moBoss2_Door.h"
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
#include "moSound.h"

namespace mo {
	Boss2_Door::Boss2_Door()
	{
	}
	Boss2_Door::~Boss2_Door()
	{
	}
	void Boss2_Door::Initialize()
	{
		Image* mImage = Resources::Load<Image>(L"Boss2_Door", L"..\\Resources\\Enemy\\Boss2\\Boss2_Door.bmp");

		
		Transform* tr;
		tr = GetComponent<Transform>();
		tr->SetScale(Vector2(3.5f, 3.5f));

		mAnimator = AddComponent<Animator>();

		mAnimator->SetUnUseCameraY(true);
		mAnimator->CreateAnimation(L"Open", mImage, Vector2(272.0f * 0, 224.0f * 0), 272.0f, 8, 1, 7, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"None", mImage, Vector2(272.0f * 7, 59.0f * 0), 272.0f, 8, 1, 1, Vector2::Zero, 0.1);

		mAnimator->Play(L"None", false);

		GameObject::Initialize();
	}
	void Boss2_Door::Update()
	{
		GameObject::Update();

	}
	void Boss2_Door::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void Boss2_Door::OnCollisionEnter(Collider* other)
	{
	}
	void Boss2_Door::OnCollisionStay(Collider* other)
	{
	}
	void Boss2_Door::OnCollisionExit(Collider* other)
	{
	}
}