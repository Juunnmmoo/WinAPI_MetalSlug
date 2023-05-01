#include "moMachinegunBullet.h"
#include "moImage.h"
#include "moResources.h"
#include "moApplication.h"
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
#include "moMarco.h"
#include "moBoss1_Missile.h"
#include "moSound.h"
#include "moSlave.h"
extern mo::Application application;
namespace mo {
	MachinegunBullet::MachinegunBullet(Marco* marco)
		:time(0.0f)
		,mTime(0.0f)
		,mPlayer(marco)
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
		mAnimator->CreateAnimation(L"MachinegunBulletT", mImage, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 10, 4, 1, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MachinegunBulletB", mImage, Vector2(120.0f * 0, 120.0f * 3), -120.0f, 10, 4, 1, Vector2::Zero, 0.05);

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
		mCollider->SetSize(Vector2{ 30.0f, 30.0f });
		mCollider->SetLeftTop(Vector2(0.0f, -30.0f));

		SetBulletType(eBulletType::Bullet);

		Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2(-100.0f, -100.0f));
		tr->SetScale(Vector2(3.0f, 3.0f));
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
			BulletSFX* bulletSFX = new BulletSFX(eSfxType::PlayerBulletGroundSFX, pos, Vector2(2.0f, 2.0f), Vector2(0.0f, 49.0f));
			curScene->AddGameObject(bulletSFX, eLayerType::Effect);
			bulletSFX->Initialize();
			bulletSFX->PlayAnimation();
			object::Destory(this);
		}
		// ÀÚµ¿ isChanged
		Vector2 cPos = Camera::CaluatePos(pos);
		if (cPos.x <  -100.0f  || cPos.x > application.GetWidth() + 100.0f|| cPos.y < -100.0f)
			object::Destory(this);

		GameObject::Update();
	}

	void MachinegunBullet::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}

	void MachinegunBullet::OnCollisionEnter(Collider* other)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (other->GetOwner()->GetLayerType() == eLayerType::EnemyR || other->GetOwner()->GetLayerType() == eLayerType::Enemy ||
			other->GetOwner()->GetLayerType() == eLayerType::EnemyR_F || other->GetOwner()->GetLayerType() == eLayerType::Enemy_F)
		{
			Scene* curScene = SceneManager::GetActiveScene();
			BulletSFX* bulletSFX = new BulletSFX(eSfxType::PlayerBulletEnemySFX, pos, Vector2(2.5f, 2.5f), Vector2(0.0f, 60.0f));
			curScene->AddGameObject(bulletSFX, eLayerType::Effect);
			bulletSFX->Initialize();
			bulletSFX->PlayAnimation();
			object::Destory(this);
		}

		Slave* slave = dynamic_cast<Slave*>(other->GetOwner());
		if (slave != nullptr && !slave->GetIsRelease())
		{
			Scene* curScene = SceneManager::GetActiveScene();
			BulletSFX* bulletSFX = new BulletSFX(eSfxType::PlayerBulletEnemySFX, pos, Vector2(2.5f, 2.5f), Vector2(0.0f, 60.0f));
			curScene->AddGameObject(bulletSFX, eLayerType::Effect);
			bulletSFX->Initialize();
			bulletSFX->PlayAnimation();
			object::Destory(this);
		}

		Boss1_Missile* missile = dynamic_cast<Boss1_Missile*>(other->GetOwner());
		if (missile != nullptr)
		{
			Scene* curScene = SceneManager::GetActiveScene();
			BulletSFX* bulletSFX = new BulletSFX(eSfxType::PlayerBulletEnemySFX, pos, Vector2(2.5f, 2.5f), Vector2(0.0f, 60.0f));
			curScene->AddGameObject(bulletSFX, eLayerType::Effect);
			bulletSFX->Initialize();
			bulletSFX->PlayAnimation();
			object::Destory(this);
		}

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
		Transform* marcoTR = mPlayer->GetComponent<Transform>();
		Transform* tr = GetComponent<Transform>();
		

		if (mDirection == eDirection::Left)
		{	
			if (animationNum == 0)
			{
				mAnimator->Play(L"MachinegunBulletL", false);
			}
			else if (animationNum == 1)
			{
				mAnimator->Play(L"MachinegunBulletTL_1", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(-35.0f, -90.0f));
			}
			else if (animationNum == 2)
			{
				mAnimator->Play(L"MachinegunBulletTL_2", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(-40.0f, -60.0f));
			}
			else if (animationNum == 3)
			{
				mAnimator->Play(L"MachinegunBulletTL_3", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(-50.0f, -30.0f));
			}
			else if (animationNum == 4)
			{
				mAnimator->Play(L"MachinegunBulletTL_4", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(-50.0f, -15.0f));
			}

			
		}	
		else if (mDirection == eDirection::Right)
		{
			if (animationNum == 0)
			{
				mAnimator->Play(L"MachinegunBulletR", false);
			}
			else if (animationNum == 1)
			{
				mAnimator->Play(L"MachinegunBulletTR_1", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(35.0f, -90.0f));
			}
			else if (animationNum == 2)
			{
				mAnimator->Play(L"MachinegunBulletTR_2", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(40.0f, -60.0f));
			}
			else if (animationNum == 3)
			{
				mAnimator->Play(L"MachinegunBulletTR_3", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(50.0f, -30.0f));
			}
			else if (animationNum == 4)
			{
				mAnimator->Play(L"MachinegunBulletTR_4", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(50.0f, -15.0f));
			}
		}	
		else if (mDirection == eDirection::RTop)
		{
			if (animationNum == 0)
			{
				mAnimator->Play(L"MachinegunBulletT", false);
			}
			else if (animationNum == 1)
			{
				mAnimator->Play(L"MachinegunBulletRT_1", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(50.0f, -35.0f));
			}
			else if (animationNum == 2)
			{
				mAnimator->Play(L"MachinegunBulletRT_2", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(50.0f, -65.0f));
			}
			else if (animationNum == 3)
			{
				mAnimator->Play(L"MachinegunBulletRT_3", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(40.0f, -80.0f));
			}
			else if (animationNum == 4)
			{
				mAnimator->Play(L"MachinegunBulletRT_4", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(35.0f, -105.0f));
			}
		}	
		else if (mDirection == eDirection::LTop)
		{
			if (animationNum == 1)
			{
				mAnimator->Play(L"MachinegunBulletLT_1", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(-50.0f, -35.0f));
			}
			else if (animationNum == 2)
			{
				mAnimator->Play(L"MachinegunBulletLT_2", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(-50.0f, -65.0f));
			}
			else if (animationNum == 3)
			{
				mAnimator->Play(L"MachinegunBulletLT_3", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(-50.0f, -65.0f));
			}
			else if (animationNum == 4)
			{
				mAnimator->Play(L"MachinegunBulletLT_4", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(-35.0f, -105.0f));
			}
		}
		else if (mDirection == eDirection::RBottom)
		{
			if (animationNum == 0)
			{
				mAnimator->Play(L"MachinegunBulletB", false);
			}
			else if (animationNum == 1)
			{
				mAnimator->Play(L"MachinegunBulletRB_1", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(50.0f, 35.0f));
			}
			else if (animationNum == 2)
			{
				mAnimator->Play(L"MachinegunBulletRB_2", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(50.0f, 65.0f));
			}
			else if (animationNum == 3)
			{
				mAnimator->Play(L"MachinegunBulletRB_3", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(40.0f, 80.0f));
			}
			else if (animationNum == 4)
			{
				mAnimator->Play(L"MachinegunBulletRB_4", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(35.0f, 105.0f));
			}
		}
		else if (mDirection == eDirection::LBottom)
		{
			if (animationNum == 1)
			{
				mAnimator->Play(L"MachinegunBulletLB_1", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(-50.0f, 35.0f));
			}
			else if (animationNum == 2)
			{
				mAnimator->Play(L"MachinegunBulletLB_2", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(-50.0f, 65.0f));
			}
			else if (animationNum == 3)
			{
				mAnimator->Play(L"MachinegunBulletLB_3", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(-40.0f, 80.0f));
			}
			else if (animationNum == 4)
			{
				mAnimator->Play(L"MachinegunBulletLB_4", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(-35.0f, 105.0f));
			}
		}
		else if (mDirection == eDirection::LSit)
		{	
			if (animationNum == 1)
			{
				mAnimator->Play(L"MachinegunBulletBL_1", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(-35.0f, 105.0f));
			}
			else if (animationNum == 2)
			{
				mAnimator->Play(L"MachinegunBulletBL_2", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(-40.0f, 80.0f));
			}
			else if (animationNum == 3)
			{
				mAnimator->Play(L"MachinegunBulletBL_3", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(-50.0f, 65.0f));
			}
			else if (animationNum == 4)
			{
				mAnimator->Play(L"MachinegunBulletBL_4", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(-50.0f, 35.0f));
			}
		}
		else if (mDirection == eDirection::RSit)
		{
			if (animationNum == 1)
			{
				mAnimator->Play(L"MachinegunBulletBR_1", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(35.0f, 105.0f));
			}
			else if (animationNum == 2)
			{
				mAnimator->Play(L"MachinegunBulletBR_2", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(40.0f, 80.0f));
			}
			else if (animationNum == 3)
			{
				mAnimator->Play(L"MachinegunBulletBR_3", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(50.0f, 65.0f));
			}
			else if (animationNum == 4)
			{
				mAnimator->Play(L"MachinegunBulletBR_4", false);
				tr->SetPos(marcoTR->GetPos() + Vector2(50.0f, 35.0f));
			}
		}
	}
}