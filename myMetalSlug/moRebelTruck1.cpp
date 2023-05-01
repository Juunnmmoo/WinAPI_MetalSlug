#include "moRebelTruck1.h"
#include "moImage.h"
#include "moSceneManager.h"
#include "moResources.h"
#include "moTransform.h"
#include "moInput.h"
#include "moTime.h"
#include "moAnimator.h"
#include "Collider.h"
#include "moScene.h"
#include "moObject.h"
#include "moArabianWeapon.h"
#include "moMarco.h"
#include "moScene.h"
#include "moRigidBody.h"
#include "moEnemyAttackCollider.h"
#include "moCamera.h"
#include "moApplication.h"
#include "moEnemyPistolBullet.h"
#include "moRebelTruck2.h"
#include "moArabian.h"
#include "moBulletSFX.h"
#include "moArabianFighter.h"
#include "moAbulAbbas.h"
#include "moSound.h"

namespace mo {
	RebelTruck1::RebelTruck1(Marco* p, RebelTruck2* second, Scene* scene, Vector2 stop)
		: mSecond(second)
		, player(p)
		, curScene(scene)
		, stopPos(stop)
		, dropTime(0.0f)
		, heart(50)

	{
	}
	RebelTruck1::~RebelTruck1()
	{
	}
	void RebelTruck1::Initialize()
	{
		deathSound = Resources::Load<Sound>(L"TowrdDeathSound", L"..\\Resources\\Sound\\TowrdDeathSound.wav");
		deathSound->SetVolume(80);

		mT = GetComponent<Transform>();
		mT->SetScale(Vector2{ 3.2f, 3.2f });
		mT->SetDirection(eDirection::Left);

		secondT = mSecond->GetComponent<Transform>();
		secondT->SetPos(mT->GetPos() + Vector2(-147.2f, 0.0f));
		secondT->SetScale(Vector2{ 3.2f, 3.2f });
		secondT->SetDirection(eDirection::Left);

		Image* mImage = Resources::Load<Image>(L"RebelTruck", L"..\\Resources\\Enemy\\RebelTruck.bmp");

		mAnimator = AddComponent<Animator>();
		secondAnimator = mSecond->AddComponent<Animator>();

		mAnimator->CreateAnimation(L"Move", mImage, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 12, 8, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Drop", mImage, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 12, 8, 12, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Death", mImage, Vector2(120.0f * 0, 120.0f * 4), 120.0f, 12, 8, 6, Vector2::Zero, 0.1);

		mAnimator->Play(L"Move", true);
		

		secondAnimator->CreateAnimation(L"Move", mImage, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 12, 8, 4, Vector2::Zero, 0.1);
		secondAnimator->CreateAnimation(L"Drop", mImage, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 12, 8, 12, Vector2::Zero, 0.1);
		secondAnimator->CreateAnimation(L"None", mImage, Vector2(120.0f * 6, 120.0f * 1), 120.0f, 12, 8, 1, Vector2::Zero, 0.1);

		secondAnimator->Play(L"Move", true);

		mState = eRebelTruckState::Move;

		createCnt = 5;

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 200.0f, 200.0f });
		mCollider->SetLeftTop(Vector2{ -150.0f, -200.f });

		abul = new AbulAbbas(Vector2(5800.0f, 0.0f), mo::AbulAbbas::eAbulAbbasState::MoveFoword);
		curScene->AddGameObject(abul, eLayerType::EnemyR_F);
		abul->Initialize();
		abul->GetComponent<Transform>()->SetPos(Vector2(6320.0f, 750.0f));


		GameObject::Initialize();
	}
	void RebelTruck1::Update()
	{
		switch (mState) {
		case mo::RebelTruck1::eRebelTruckState::Move:
			move();
			break;
		case mo::RebelTruck1::eRebelTruckState::Drop:
			drop();
			break;
		case mo::RebelTruck1::eRebelTruckState::Death:
			death();
			break;
	
		default:
			break;
		}


		if (heart <= 0)
			mState = eRebelTruckState::Death;


	


		secondT->SetPos(mT->GetPos() + Vector2(-147.2f, 0.0f));

		GameObject::Update();

	}
	void RebelTruck1::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void RebelTruck1::OnCollisionEnter(Collider* other)
	{
		if ((other->GetOwner()->GetLayerType() == eLayerType::PlayerPistol ||
			other->GetOwner()->GetLayerType() == eLayerType::PlayerMachinegun)&&
			mState == eRebelTruckState::Drop)
		{
			heart--;
		}
		if (other->GetOwner()->GetLayerType() == eLayerType::PlayerBomb 
			 && mState == eRebelTruckState::Drop)
		{
			heart-= 10;
		}
	}
	void RebelTruck1::OnCollisionStay(Collider* other)
	{
	}
	void RebelTruck1::OnCollisionExit(Collider* other)
	{
	}

	void RebelTruck1::move()
	{
		Vector2 pos = mT->GetPos();
		pos.x -= 200.0f * Time::DeltaTime();
		mT->SetPos(pos);

		if (pos.x <= stopPos.x)
		{
			mAnimator->Play(L"Drop", false);
			secondAnimator->Play(L"Drop", false);
			mState = eRebelTruckState::Drop;
		}


	}
	void RebelTruck1::drop()
	{

		if (mAnimator->IsComplte())
		{
			Vector2 pos = mT->GetPos();
			dropTime += Time::DeltaTime();

			if (dropTime >= 2.5f)
			{
				dropTime = 0.0f;
				if (createCnt >= 0)
				{
					createCnt--;
					
					ArabianFighter* fighter1 = new ArabianFighter(player, Vector2(5600.0f, 0.0f) ,50, ArabianFighter::eArabianFighterState::Foword);
					curScene->AddGameObject(fighter1, eLayerType::EnemyR);
					fighter1->Initialize();
					fighter1->GetComponent<Transform>()->SetPos(pos + Vector2(0.0f, -60.0f));
				}
				
			}
		}
	}
	void RebelTruck1::death()
	{

		Vector2 pos = mT->GetPos();

		if (!useSfx)
		{
			deathSound->Play(false);
			useSfx = true;
			abul->StartRun();
			mAnimator->Play(L"Death", true);
			secondAnimator->Play(L"None", true);
			Scene* curScene = SceneManager::GetActiveScene();
			SetState(eState::Pause);

			for (int i = 0; i < 7; i++)
			{
				if (i == 0)
				{
					BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(-140.0f, 0.0f), Vector2(2.5f, 2.5f), Vector2(0.0f, 36.0f));
					curScene->AddGameObject(bulletSFX, eLayerType::Effect);
					bulletSFX->Initialize();
					bulletSFX->PlayAnimation();
				}	
				else if (i == 1)
				{
					BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(-90.0f, 30.0f), Vector2(2.5f, 2.5f), Vector2(0.0f, 36.0f));
					curScene->AddGameObject(bulletSFX, eLayerType::Effect);
					bulletSFX->Initialize();
					bulletSFX->PlayAnimation();
				}
				else if (i == 2)
				{
					BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(-50.0f, -70.0f), Vector2(2.5f, 2.5f), Vector2(0.0f, 36.0f));
					curScene->AddGameObject(bulletSFX, eLayerType::Effect);
					bulletSFX->Initialize();
					bulletSFX->PlayAnimation();
				}
				else if (i == 3)
				{
					BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(-10.0f, 90.0f), Vector2(2.5f, 2.5f), Vector2(0.0f, 36.0f));
					curScene->AddGameObject(bulletSFX, eLayerType::Effect);
					bulletSFX->Initialize();
					bulletSFX->PlayAnimation();
				}
				else if (i == 4)
				{
					BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(20.0f, -90.0f), Vector2(2.5f, 2.5f), Vector2(0.0f, 36.0f));
					curScene->AddGameObject(bulletSFX, eLayerType::Effect);
					bulletSFX->Initialize();
					bulletSFX->PlayAnimation();
				}	
				else if (i == 5)
				{
					BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(60.0f, 10.0f), Vector2(2.5f, 2.5f), Vector2(0.0f, 36.0f));
					curScene->AddGameObject(bulletSFX, eLayerType::Effect);
					bulletSFX->Initialize();
					bulletSFX->PlayAnimation();
				}
				else if (i == 6)
				{
					BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(120.0f, -110.0f), Vector2(2.5f, 2.5f), Vector2(0.0f, 36.0f));
					curScene->AddGameObject(bulletSFX, eLayerType::Effect);
					bulletSFX->Initialize();
					bulletSFX->PlayAnimation();
				}
				
			}
		}
		else
		{
			if (!isCameraStop)
			{
				isCameraStop = true;
				Camera::SetStop(false);
			}

			Vector2 cPos = Camera::CaluatePos(mT->GetPos());

			if (cPos.x < -100.0f)
				object::Destory(this);
			

		}

	}
}