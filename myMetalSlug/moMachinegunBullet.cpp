#include "moMachinegunBullet.h"
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

namespace mo {
	MachinegunBullet::MachinegunBullet()
		:time(0.0f)
		,mTime(0.0f)
	{
	}
	MachinegunBullet::~MachinegunBullet()
	{
	}
	void MachinegunBullet::Initialize()
	{
		mImage = Resources::Load<Image>(L"MachinegunBullet", L"..\\Resources\\Weapon\\Bullet\\MachinegunBullet.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"MachinegunBulletR", mImage, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletL", mImage, Vector2(120.0f * 9, 120.0f * 0), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"MachinegunBulletRT_1", mImage, Vector2(120.0f * 1, 120.0f * 1), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletLT_1", mImage, Vector2(120.0f * 8, 120.0f * 1), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletRT_2", mImage, Vector2(120.0f * 2, 120.0f * 1), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletLT_2", mImage, Vector2(120.0f * 7, 120.0f * 1), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletRT_3", mImage, Vector2(120.0f * 3, 120.0f * 1), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletLT_3", mImage, Vector2(120.0f * 6, 120.0f * 1), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletRT_4", mImage, Vector2(120.0f * 4, 120.0f * 1), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletLT_4", mImage, Vector2(120.0f * 5, 120.0f * 1), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"MachinegunBulletRB_1", mImage, Vector2(120.0f * 1, 120.0f * 0), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletLB_1", mImage, Vector2(120.0f * 8, 120.0f * 0), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletRB_2", mImage, Vector2(120.0f * 2, 120.0f * 0), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletLB_2", mImage, Vector2(120.0f * 7, 120.0f * 0), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletRB_3", mImage, Vector2(120.0f * 3, 120.0f * 0), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletLB_3", mImage, Vector2(120.0f * 6, 120.0f * 0), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletRB_4", mImage, Vector2(120.0f * 4, 120.0f * 0), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletLB_4", mImage, Vector2(120.0f * 5, 120.0f * 0), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"MachinegunBulletTR_1", mImage, Vector2(120.0f * 1, 120.0f * 2), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletTL_1", mImage, Vector2(120.0f * 8, 120.0f * 2), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletTR_2", mImage, Vector2(120.0f * 2, 120.0f * 2), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletTL_2", mImage, Vector2(120.0f * 7, 120.0f * 2), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletTR_3", mImage, Vector2(120.0f * 3, 120.0f * 2), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletTL_3", mImage, Vector2(120.0f * 6, 120.0f * 2), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletTR_4", mImage, Vector2(120.0f * 4, 120.0f * 2), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletTL_4", mImage, Vector2(120.0f * 5, 120.0f * 2), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"MachinegunBulletBR_1", mImage, Vector2(120.0f * 1, 120.0f * 3), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletBL_1", mImage, Vector2(120.0f * 8, 120.0f * 3), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletBR_2", mImage, Vector2(120.0f * 2, 120.0f * 3), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletBL_2", mImage, Vector2(120.0f * 7, 120.0f * 3), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletBR_3", mImage, Vector2(120.0f * 3, 120.0f * 3), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletBL_3", mImage, Vector2(120.0f * 6, 120.0f * 3), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletBR_4", mImage, Vector2(120.0f * 4, 120.0f * 3), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletBL_4", mImage, Vector2(120.0f * 5, 120.0f * 3), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 20.0f, 20.0f });
		mCollider->SetLeftTop(Vector2(0.0f, -20.0f));
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.8f, 2.8f));
		tr->SetDisToBottom(Vector2(0.0f, 57.0f));

		GameObject::Initialize();

	}
	void MachinegunBullet::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		time += Time::DeltaTime();

		if (time >= mTime && !isPlayed)
		{
			isPlayed = true;
			PlayAnimation();
		}

		if (GetState() == eState::Active
			&& time >= mTime)
		{
			pos.y += 1200.0f * mDir.y * Time::DeltaTime();
			pos.x += 1200.0f * mDir.x * Time::DeltaTime();
			tr->SetPos(pos);
		}
		else if (GetState() == eState::Pause)
		{
			Scene* curScene = SceneManager::GetActiveScene();
			BulletSFX* bulletSFX = new BulletSFX(eLayerType::PlayerPistol, pos, Vector2(2.0f, 2.0f), Vector2(0.0f, 49.0f));
			curScene->AddGameObject(bulletSFX, eLayerType::Effect);
			bulletSFX->Initialize();
			bulletSFX->PlayAnimation();
			object::Destory(this);
		}

		GameObject::Update();
	}

	void MachinegunBullet::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}

	void MachinegunBullet::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Enemy)
			object::Destory(this);
	}

	void MachinegunBullet::OnCollisionStay(Collider* other)
	{
	}

	void MachinegunBullet::OnCollisionExit(Collider* other)
	{
	}
	void MachinegunBullet::SetDir(Vector2 dir)
	{
		mDir = dir;
		mDir.Normalize();
	}
	void MachinegunBullet::PlayAnimation()
	{
		if (mDirection == eDirection::Left)
			mAnimator->Play(L"MachinegunBulletL", false);
		else if (mDirection == eDirection::Right)
			mAnimator->Play(L"MachinegunBulletR", false);
	}
}