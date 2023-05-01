#include "moBoss2_Weapon.h"
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
	Boss2_Weapon::Boss2_Weapon()
	{
	}
	Boss2_Weapon::~Boss2_Weapon()
	{
	}
	void Boss2_Weapon::Initialize()
	{
		Image* mImage = Resources::Load<Image>(L"Boss2_Laser", L"..\\Resources\\Enemy\\Boss2\\Boss2_Laser.bmp");

		Transform* tr;
		tr = GetComponent<Transform>();
		tr->SetScale(Vector2(3.5f, 3.5f));

		mAnimator = AddComponent<Animator>();

		mAnimator->SetUnUseCameraY(true);
		mAnimator->CreateAnimation(L"Idle", mImage, Vector2(272.0f * 0, 160.0f * 0), 272.0f, 25, 4, 4, Vector2::Zero, 0.03);

		mAnimator->Play(L"Idle", true);

		GameObject::Initialize();
	}
	void Boss2_Weapon::Update()
	{
		GameObject::Update();

	}
	void Boss2_Weapon::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void Boss2_Weapon::OnCollisionEnter(Collider* other)
	{
	}
	void Boss2_Weapon::OnCollisionStay(Collider* other)
	{
	}
	void Boss2_Weapon::OnCollisionExit(Collider* other)
	{
	}
}