#include "moArmyRoketBullet.h"
#include "moImage.h"
#include "moResources.h"
#include "moTransform.h"
#include "moTime.h"
#include "Collider.h"
#include "moObject.h"
#include "moInput.h"
#include "moCamera.h"
#include "moAnimator.h"
#include "moRigidBody.h"
#include "moBulletSFX.h"
#include "moSceneManager.h"
#include "moScene.h"
#include "moCamera.h"
#include "moApplication.h"
#include "moBulletSFX.h"
namespace mo {
	ArmyRoketBullet::ArmyRoketBullet()
	{
	}
	ArmyRoketBullet::~ArmyRoketBullet()
	{
	}
	void ArmyRoketBullet::Initialize()
	{

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(3.5f, 3.5f));

		mImage = Resources::Load<Image>(L"weaponSFX", L"..\\Resources\\Weapon\\WeaponSFX.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"bullet", mImage, Vector2(120.0f * 0, 120.0f * 7), 120.0f, 30, 60, 4, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"bulletSFX", mImage, Vector2(120.0f * 0, 120.0f * 8), 120.0f, 30, 60, 16, Vector2::Zero, 0.05);
		mAnimator->Play(L"bullet", true);


		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 20.0f, 20.0f });
		mCollider->SetLeftTop(Vector2{ -10.0f, -20.0f });


		SetBulletType(eBulletType::Bomb);
		GameObject::Initialize();
	}
	void ArmyRoketBullet::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (pos.y<810.0f)
		{
			if (!isDeath)
			{
				pos.x += 200.0f * mDir.x * Time::DeltaTime();
				pos.y += 200.0f * mDir.y * Time::DeltaTime();
				tr->SetPos(pos);
			}
			else
			{

				if (mAnimator->IsComplte())

					object::Destory(this);
			}

		}
		else 
		{
			if (!isDeath)
			{
				isDeath = true;
				mAnimator->Play(L"bulletSFX", false);
			}
			else
			{
				if (mAnimator->IsComplte())
					object::Destory(this);
			}
		}

		GameObject::Update();
	}
	void ArmyRoketBullet::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void ArmyRoketBullet::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			isDeath = true;
			mAnimator->Play(L"bulletSFX", false);
		}
	}
	void ArmyRoketBullet::OnCollisionStay(Collider* other)
	{
	}
	void ArmyRoketBullet::OnCollisionExit(Collider* other)
	{
	}
}