#include "moBoss2_Propeller.h"
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
	Boss2_Propeller::Boss2_Propeller()
	{
	}
	Boss2_Propeller::~Boss2_Propeller()
	{
	}
	void Boss2_Propeller::Initialize()
	{
		Image* mImage = Resources::Load<Image>(L"Boss2_Energy", L"..\\Resources\\Enemy\\Boss2\\Boss2_Energy.bmp");
	
		Transform* tr;
		tr = GetComponent<Transform>();
		tr->SetScale(Vector2(3.5f, 3.5f));

		mAnimator = AddComponent<Animator>();

		mAnimator->SetUnUseCameraY(true);
		mAnimator->CreateAnimation(L"Idle", mImage, Vector2(272.0f * 0, 224.0f * 0), 272.0f, 9, 1, 3, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Attack", mImage, Vector2(272.0f * 3, 59.0f * 0), 272.0f, 9, 1, 6, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"None", mImage, Vector2(272.0f * 0, 272.0f * 1), 272.0f, 9, 1, 6, Vector2::Zero, 0.1);

		mAnimator->Play(L"Idle", true);

		GameObject::Initialize();
	}
	void Boss2_Propeller::Update()
	{
		GameObject::Update();

	}
	void Boss2_Propeller::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void Boss2_Propeller::OnCollisionEnter(Collider* other)
	{
	}
	void Boss2_Propeller::OnCollisionStay(Collider* other)
	{
	}
	void Boss2_Propeller::OnCollisionExit(Collider* other)
	{
	}
}