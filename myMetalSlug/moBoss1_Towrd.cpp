#include "moBoss1_Towrd.h"
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
#include "moBoss1_CurtainIdle.h"
#include "moBoss1_WindowOpen.h"
#include "moScene.h"
#include "moAnimator.h"
#include "moBoss1_CurtainOpen.h"
#include "moBoss1_Attackor.h"
#include "moBulletSFX.h"
#include "moBoss1_Missile.h"


namespace mo {
	Boss1_Towrd::Boss1_Towrd(Marco* marco, Scene* scene, TowrdDir dir)
		: mTowrdDir(dir)	
		, mPlayer(marco)
		, curScene(scene)
	{
	}
	Boss1_Towrd::~Boss1_Towrd()
	{
	}
	void Boss1_Towrd::Initialize()
	{
		Transform* tr = GetComponent<Transform>();


		mTowrdImage = Resources::Load<Image>(L"Boss_Towrds", L"..\\Resources\\Enemy\\Boss1\\Boss1_Towrds.bmp");
		mTowrdOpenImage = Resources::Load<Image>(L"Boss_TowrdsOpen", L"..\\Resources\\Enemy\\Boss1\\Boss1_TowrdsOpen.bmp");
		mTowrdDestroyedImage = Resources::Load<Image>(L"Boss_TowrdsDestroyed", L"..\\Resources\\Enemy\\Boss1\\Boss1_TowrdsDestroyed.bmp");
		
		mTowrdState = TowrdState::Nomal;
		mFsmState = eTowrdFSM::None;

		mCurtainIdle = new Boss1_CurtainIdle();
		mDoor = new Boss1_WindowOpen();
		mCurtainOpen = new Boss1_CurtainOpen();
		mAttackor = new Boss1_Attackor();

		curScene->AddGameObject(mCurtainIdle, eLayerType::front);
		curScene->AddGameObject(mDoor, eLayerType::front);
		curScene->AddGameObject(mCurtainOpen, eLayerType::front);
		curScene->AddGameObject(mAttackor, eLayerType::Enemy_F);

		mCurtainIdle->Initialize();
		mDoor->Initialize();
		mCurtainOpen->Initialize();
		mAttackor->Initialize();

	
		if (mTowrdDir == TowrdDir::Left)
		{
			mCurtainIdle->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-15.0f, -255.0f));
			mDoor->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-18.0f, -130.0f));
			mCurtainOpen->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-16.0f, -220.0f));
			mAttackor->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-16.0f, -265.0f));
			mCurtainIdle->GetAnimator()->Play(L"IdleLeft", true);


		}
		else if (mTowrdDir == TowrdDir::Middle)
		{
			mCurtainIdle->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(5.0f, -255.0f));
			mDoor->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(0.0f, -130.0f));
			mCurtainOpen->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(0.0f, -220.0f));
			mAttackor->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-1.0f, -265.0f));
			mCurtainIdle->GetAnimator()->Play(L"IdleMiddle", true);

		}
		else
		{
			mCurtainIdle->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(25.0f, -255.0f));
			mDoor->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(18.0f, -130.0f));
			mCurtainOpen->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(16.0f, -220.0f));
			mAttackor->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(14.0f, -265.0f));
			mCurtainIdle->GetAnimator()->Play(L"IdleRight", true);

		}



		GameObject::Initialize();
	}
	void Boss1_Towrd::Update()
	{
		switch (mFsmState) {
		case mo::Boss1_Towrd::eTowrdFSM::Up:
			up();
			break;
		case mo::Boss1_Towrd::eTowrdFSM::DoorOpen:
			dooropen();
			break;
		case mo::Boss1_Towrd::eTowrdFSM::CurtainOpen:
			curtainopen();
			break;
		case mo::Boss1_Towrd::eTowrdFSM::Attack:
			attack();
			break;
		case mo::Boss1_Towrd::eTowrdFSM::Destroyed:
			destroyed();
			break;

		}


		if (mFsmState == eTowrdFSM::None)
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			Vector2 cPos = Camera::CaluatePos(pos);

			if (Camera::GetStop() && cPos.x < 1100.0f && cPos.x >= 0.0f)
			{

				mFsmState = eTowrdFSM::Up;
			}
		}

		Transform* tr = GetComponent<Transform>();

		if (mTowrdDir == TowrdDir::Left)
		{
			mCurtainIdle->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-14.0f, -260.0f));
			mDoor->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-15.0f, -133.0f));
			mCurtainOpen->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-14.0f, -225.0f));
			mAttackor->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-16.0f, -275.0f));


		}
		else if (mTowrdDir == TowrdDir::Middle)
		{
			mCurtainIdle->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(5.0f, -260.0f));
			mDoor->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(0.0f, -133.0f));
			mCurtainOpen->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(2.0f, -225.0f));
			mAttackor->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(0.0f, -275.0f));

		}
		else
		{
			mCurtainIdle->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(22.0f, -260.0f));
			mDoor->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(15.0f, -133.0f));
			mCurtainOpen->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(14.0f, -225.0f));
			mAttackor->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(16.0f, -275.0f));

		}

		if (mAttackor->GetState() == eState::Pause && mTowrdState != TowrdState::Destroyed)
		{
			if (mTowrdDir == TowrdDir::Left)
			{
				Scene* curScene = SceneManager::GetActiveScene();
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, tr->GetPos() + Vector2(-16.0f, -240.0f), Vector2(4.0f, 4.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();

			}
			else if (mTowrdDir == TowrdDir::Middle)
			{
				Scene* curScene = SceneManager::GetActiveScene();
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, tr->GetPos() + Vector2(0.0f, -240.0f), Vector2(4.0f, 4.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else
			{
				Scene* curScene = SceneManager::GetActiveScene();
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, tr->GetPos() + Vector2(16.0f, -240.0f), Vector2(4.0f, 4.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();

			}

			

			mTowrdState = TowrdState::Destroyed;
			SetState(eState::Pause);
		}

		GameObject::Update();
	}
	void Boss1_Towrd::Render(HDC mHdc)	
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 cPos = Camera::CaluatePos(pos);

		if (mTowrdDir == TowrdDir::Left)
		{
			if (mTowrdState == TowrdState::Nomal)
			{
				TransparentBlt(mHdc, cPos.x - mTowrdImage->GetWidth() / 6, pos.y - mTowrdImage->GetHeight(), mTowrdImage->GetWidth()/3, mTowrdImage->GetHeight(),
					mTowrdImage->GetHdc(), 0, 0, mTowrdImage->GetWidth()/3, mTowrdImage->GetHeight(), RGB(153, 217, 234));

			}
			else if (mTowrdState == TowrdState::Open)
			{
				TransparentBlt(mHdc, cPos.x - mTowrdOpenImage->GetWidth() / 6, pos.y - mTowrdOpenImage->GetHeight(), mTowrdOpenImage->GetWidth() / 3, mTowrdOpenImage->GetHeight(),
					mTowrdOpenImage->GetHdc(), 0, 0, mTowrdOpenImage->GetWidth() / 3, mTowrdOpenImage->GetHeight(), RGB(153, 217, 234));
			}
			else 
			{
				TransparentBlt(mHdc, cPos.x - mTowrdDestroyedImage->GetWidth() / 6, pos.y - mTowrdDestroyedImage->GetHeight(), mTowrdDestroyedImage->GetWidth() / 3, mTowrdDestroyedImage->GetHeight(),
					mTowrdDestroyedImage->GetHdc(), 0, 0, mTowrdDestroyedImage->GetWidth() / 3, mTowrdDestroyedImage->GetHeight(), RGB(153, 217, 234));
			}
		}
		else if (mTowrdDir == TowrdDir::Middle)
		{
			if (mTowrdState == TowrdState::Nomal)
			{
				TransparentBlt(mHdc, cPos.x - mTowrdImage->GetWidth() / 6, pos.y - mTowrdImage->GetHeight(), mTowrdImage->GetWidth() / 3, mTowrdImage->GetHeight(),
					mTowrdImage->GetHdc(), mTowrdImage->GetWidth() / 3, 0, mTowrdImage->GetWidth() / 3, mTowrdImage->GetHeight(), RGB(153, 217, 234));
			}
			else if (mTowrdState == TowrdState::Open)
			{
				TransparentBlt(mHdc, cPos.x - mTowrdOpenImage->GetWidth() / 6, pos.y - mTowrdOpenImage->GetHeight(), mTowrdOpenImage->GetWidth() / 3, mTowrdOpenImage->GetHeight(),
					mTowrdOpenImage->GetHdc(), mTowrdOpenImage->GetWidth() / 3, 0, mTowrdOpenImage->GetWidth() / 3, mTowrdOpenImage->GetHeight(), RGB(153, 217, 234));
			}
			else
			{
				TransparentBlt(mHdc, cPos.x - mTowrdDestroyedImage->GetWidth() / 6, pos.y - mTowrdDestroyedImage->GetHeight(), mTowrdDestroyedImage->GetWidth() / 3, mTowrdDestroyedImage->GetHeight(),
					mTowrdDestroyedImage->GetHdc(), mTowrdDestroyedImage->GetWidth() / 3, 0, mTowrdDestroyedImage->GetWidth() / 3, mTowrdDestroyedImage->GetHeight(), RGB(153, 217, 234));
			}
		}
		else
		{
			if (mTowrdState == TowrdState::Nomal)
			{
				TransparentBlt(mHdc, cPos.x - mTowrdImage->GetWidth() / 6, pos.y - mTowrdImage->GetHeight(), mTowrdImage->GetWidth() / 3, mTowrdImage->GetHeight(),
					mTowrdImage->GetHdc(), mTowrdImage->GetWidth() / 3*2, 0, mTowrdImage->GetWidth() / 3, mTowrdImage->GetHeight(), RGB(153, 217, 234));
			}
			else if (mTowrdState == TowrdState::Open)
			{
				TransparentBlt(mHdc, cPos.x - mTowrdOpenImage->GetWidth() / 6, pos.y - mTowrdOpenImage->GetHeight(), mTowrdOpenImage->GetWidth() / 3, mTowrdOpenImage->GetHeight(),
					mTowrdOpenImage->GetHdc(), mTowrdOpenImage->GetWidth() / 3 * 2, 0, mTowrdOpenImage->GetWidth() / 3, mTowrdOpenImage->GetHeight(), RGB(153, 217, 234));
			}
			else
			{
				TransparentBlt(mHdc, cPos.x - mTowrdDestroyedImage->GetWidth() / 6, pos.y - mTowrdDestroyedImage->GetHeight(), mTowrdDestroyedImage->GetWidth() / 3, mTowrdDestroyedImage->GetHeight(),
					mTowrdDestroyedImage->GetHdc(), mTowrdDestroyedImage->GetWidth() / 3 * 2, 0, mTowrdDestroyedImage->GetWidth() / 3, mTowrdDestroyedImage->GetHeight(), RGB(153, 217, 234));
			}
		}

		GameObject::Render(mHdc);
	}
	void Boss1_Towrd::OnCollisionEnter(Collider* other)
	{
	}
	void Boss1_Towrd::OnCollisionStay(Collider* other)
	{
	}
	void Boss1_Towrd::OnCollisionExit(Collider* other)
	{
	}
	void Boss1_Towrd::up()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 cPos = Camera::CaluatePos(pos);

		if (mTowrdDir == TowrdDir::Left)
		{
			pos.x -= 12.0f * Time::DeltaTime();
			pos.y -= 16.0f * Time::DeltaTime();
		}
		else if (mTowrdDir == TowrdDir::Middle)
		{
			pos.y -= 16.0f * Time::DeltaTime();
		}
		else
		{
			pos.x += 12.0f * Time::DeltaTime();
			pos.y -= 16.0f * Time::DeltaTime();
		}
		tr->SetPos(pos);
	}
	void Boss1_Towrd::dooropen()
	{
		if (!isPlayed)
		{
			isPlayed = true;
			mDoor->GetAnimator()->Play(L"Open", false);
		}
		if (isPlayed && mDoor->GetAnimator()->IsComplte())
		{
			isPlayed = false;
			mFsmState = eTowrdFSM::CurtainOpen;
		}
	}
	void Boss1_Towrd::curtainopen()
	{
		if (!isPlayed)
		{

			isPlayed = true;
			mTowrdState = TowrdState::Open;
			mDoor->GetAnimator()->Play(L"None", false);
			mCurtainIdle->GetAnimator()->Play(L"None", false);


			if (mTowrdDir == TowrdDir::Left)
			{
				mCurtainOpen->GetAnimator()->Play(L"OpenLeft", false);
			}
			else if (mTowrdDir == TowrdDir::Middle)
			{
				mCurtainOpen->GetAnimator()->Play(L"OpenMiddle", false);
			}
			else
			{
				mCurtainOpen->GetAnimator()->Play(L"OpenRight", false);

			}
		}
		if (isPlayed && mCurtainOpen->GetAnimator()->IsComplte())
		{
			
			mTime += Time::DeltaTime();

			if (mTowrdDir == TowrdDir::Left)
			{
				if (mTime >= 1.6f)
				{
					isPlayed = false;

					mTime = 0.0f;
					mFsmState = eTowrdFSM::Attack;
				}
			}
			else if (mTowrdDir == TowrdDir::Middle)
			{
				if (mTime >= 0.8f)
				{
					isPlayed = false;

					mTime = 0.0f;
					mFsmState = eTowrdFSM::Attack;
				}
			}
			else
			{
				if (mTime >= 2.4f)
				{
					isPlayed = false;

					mTime = 0.0f;
					mFsmState = eTowrdFSM::Attack;
				}
			}

		}

	}
	void Boss1_Towrd::attack()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (!isPlayed)
		{
			isPlayed = true;
			mTime = 0.0f;
			mCurtainOpen->GetAnimator()->Play(L"None", false);
			mAttackor->GetAnimator()->Play(L"Attack", false);

		}
		if (isPlayed && mAttackor->GetAnimator()->IsComplte())
		{

			mTime += Time::DeltaTime();

			if (!useSfx)
			{
				useSfx = true;
				Scene* curScene = SceneManager::GetActiveScene();
				
				if (mTowrdDir == TowrdDir::Left)
				{
					Boss1_Missile* missile = new Boss1_Missile(mPlayer);
					curScene->AddGameObject(missile, eLayerType::EnemyBullet);
					missile->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(-14.0f, -275.0f));
					missile->Initialize();
					missile->GetComponent<Transform>()->SetDirection(eDirection::Right);

					BulletSFX* bulletSFX = new BulletSFX(eSfxType::Boss1SFX, tr->GetPos() + Vector2(-16.0f, -425.0f), Vector2(3.5f, 3.5f), Vector2(0.0f, 60.0f));
					curScene->AddGameObject(bulletSFX, eLayerType::Effect);
					bulletSFX->Initialize();
					bulletSFX->PlayAnimation();
				}
				else if (mTowrdDir == TowrdDir::Middle)
				{
					Boss1_Missile* missile = new Boss1_Missile(mPlayer);
					curScene->AddGameObject(missile, eLayerType::EnemyBullet);
					missile->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(2.0f, -275.0f));
					missile->Initialize();

					BulletSFX* bulletSFX = new BulletSFX(eSfxType::Boss1SFX, tr->GetPos() + Vector2(0.0f, -425.0f), Vector2(3.5f, 3.5f), Vector2(0.0f, 60.0f));
					curScene->AddGameObject(bulletSFX, eLayerType::Effect);
					bulletSFX->Initialize();
					bulletSFX->PlayAnimation();

				}
				else
				{
					Boss1_Missile* missile = new Boss1_Missile(mPlayer);
					curScene->AddGameObject(missile, eLayerType::EnemyBullet);
					missile->GetComponent<Transform>()->SetPos(tr->GetPos() + Vector2(16.0f, -275.0f));
					missile->Initialize();

					BulletSFX* bulletSFX = new BulletSFX(eSfxType::Boss1SFX, tr->GetPos() + Vector2(14.0f, -425.0f), Vector2(3.5f, 3.5f), Vector2(0.0f, 60.0f));
					curScene->AddGameObject(bulletSFX, eLayerType::Effect);
					bulletSFX->Initialize();
					bulletSFX->PlayAnimation();

				}
			}


			if (mTime >= 4.0f)
			{
				useSfx = false;
				isPlayed = false;
			}

		

			
			

		}
	}
	void Boss1_Towrd::destroyed()
	{
	}
}
