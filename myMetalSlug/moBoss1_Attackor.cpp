#include "moBoss1_Attackor.h"
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
	Boss1_Attackor::Boss1_Attackor()
		:heart(60)
	{
	}
	Boss1_Attackor::~Boss1_Attackor()
	{
	}
	void Boss1_Attackor::Initialize()
	{
		Image* mImage = Resources::Load<Image>(L"Boss1_Attack", L"..\\Resources\\Enemy\\Boss1\\Boss1_Attack.bmp");

		deathSound = Resources::Load<Sound>(L"TowrdDeathSound", L"..\\Resources\\Sound\\TowrdDeathSound.wav");
		deathSound->SetVolume(80);
		Transform* tr;
		tr = GetComponent<Transform>();

		mAnimator = AddComponent<Animator>();

		mAnimator->SetUnUseCameraY(true);
		mAnimator->CreateAnimation(L"Attack", mImage, Vector2(116.0f * 0, 224.0f * 0), 116.0f, 6, 1, 5, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"None", mImage, Vector2(116.0f * 5, 59.0f * 0), 116.0f, 6, 1, 1, Vector2::Zero, 0.1);

		mAnimator->Play(L"None", false);

		Collider* collider = AddComponent<Collider>();
		collider->SetLeftTop(Vector2(-56.0f, -60.0f));
		collider->SetSize(Vector2(116.0f, 80.0f));


		GameObject::Initialize();
	}
	void Boss1_Attackor::Update()
	{
		if (heart <= 0)
		{
			if (GetState() != eState::Pause)
				deathSound->Play(false);

			mAnimator->Play(L"None", false);
			SetState(eState::Pause);
		}

		GameObject::Update();

	}
	void Boss1_Attackor::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void Boss1_Attackor::OnCollisionEnter(Collider* other)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (other->GetOwner()->GetLayerType() == eLayerType::PlayerPistol ||
			other->GetOwner()->GetLayerType() == eLayerType::PlayerMachinegun 
			)
		{
			heart--;
		}
	}
	void Boss1_Attackor::OnCollisionStay(Collider* other)
	{
	}
	void Boss1_Attackor::OnCollisionExit(Collider* other)
	{
	}
}
