#include "moBoss1_Base.h"
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
#include "moBoss1_towrd.h"
#include "moBulletSFX.h"
#include "moArabianFighter.h"
#include "moAbulAbbas.h"
#include "moSound.h"

namespace mo {
	Boss1_Base::Boss1_Base(Marco* marco, Scene* scene, Boss1_Towrd* LeftTowrd, Boss1_Towrd* MiddleTowrd, Boss1_Towrd* RightTowrd, ArabianFighter* fighter)
		: curScene(scene)
		, mPlayer(marco)
		, mLeftTowrd(LeftTowrd)
		, mMiddleTowrd(MiddleTowrd)
		, mRightTowrd(RightTowrd)
		, fighter3(fighter)

	{
	}
	Boss1_Base::~Boss1_Base()
	{
		
	}
	void Boss1_Base::Initialize()
	{

		deathSound = Resources::Load<Sound>(L"Boss1DeathSound", L"..\\Resources\\Sound\\Boss1DeathSound.wav");
		deathSound->SetVolume(80);


		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(6950.0f, 730.0f));

		image = Resources::Load<Image>(L"Boss_Base", L"..\\Resources\\Enemy\\Boss1\\Boss1_Base.bmp");
		destroyImage = Resources::Load<Image>(L"Boss_BaseDestroyed", L"..\\Resources\\Enemy\\Boss1\\Boss1_Destroyed.bmp");

		

	

		abul = new AbulAbbas(Vector2(5800.0f, 0.0f), mo::AbulAbbas::eAbulAbbasState::Idle);
		curScene->AddGameObject(abul, eLayerType::EnemyR_F);
		abul->Initialize();
		abul->GetComponent<Transform>()->SetPos(Vector2(7520.0f, 0.0f));


		GameObject::Initialize();
	}
	void Boss1_Base::Update()
	{
		if (mMiddleTowrd->GetTowrdFsm() == mo::Boss1_Towrd::eTowrdFSM::Up)
		{
			if (Camera::GetLookPosition().y >= 405)
			{

				Vector2 cameraPos = Camera::GetLookPosition();
				cameraPos.y -= 20.0f * Time::DeltaTime();
				Camera::SetLookPosition(cameraPos);
			}
			else
			{
				mLeftTowrd->SetTowrdFsm(mo::Boss1_Towrd::eTowrdFSM::DoorOpen);
				mMiddleTowrd->SetTowrdFsm(mo::Boss1_Towrd::eTowrdFSM::DoorOpen);
				mRightTowrd->SetTowrdFsm(mo::Boss1_Towrd::eTowrdFSM::DoorOpen);
			}
		}



		if (mLeftTowrd->GetState() == eState::Pause &&
			mRightTowrd->GetState() == eState::Pause &&
			mMiddleTowrd->GetState() == eState::Pause &&
			GetState() != eState::Pause)
		{

			startEndEvent = true;
			//SetState(eState::Pause);
		}

		if (startEndEvent)
			EndEvent();

		if (fighter3->GetFighterState() == mo::ArabianFighter::eArabianFighterState::Foword)
			abul->StartAttack();

		if (fighter3 != nullptr)
		{
			if (fighter3->GetState() == eState::Pause)
			{
				abul->StartRun();
			}
		}
		else
		{
			abul->StartRun();
		}

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 cPos = Camera::CaluatePos(pos);
		if (GetState() == eState::Pause && cPos.x < -700.0f)
		{

			object::Destory(mLeftTowrd);
			object::Destory(mRightTowrd);
			object::Destory(mMiddleTowrd);
			object::Destory(this);
		}

		GameObject::Update();
	}
	void Boss1_Base::Render(HDC mHdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 cPos = Camera::CaluatePos(pos);

		if (GetState() == eState::Active)
			TransparentBlt(mHdc, cPos.x - image->GetWidth() / 2, cPos.y - image->GetHeight(), image->GetWidth(), image->GetHeight(), image->GetHdc(), 0, 0, image->GetWidth(), image->GetHeight(), RGB(153, 217, 234));
		else
			TransparentBlt(mHdc, cPos.x - destroyImage->GetWidth() / 2, cPos.y - destroyImage->GetHeight(), destroyImage->GetWidth(), destroyImage->GetHeight(), destroyImage->GetHdc(), 0, 0, destroyImage->GetWidth(), destroyImage->GetHeight(), RGB(153, 217, 234));

		GameObject::Render(mHdc);

	}
	void Boss1_Base::EndEvent()
	{

		mTime += Time::DeltaTime();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Camera::GetLookPosition().y >= 435.0f)
		{

			Vector2 cameraPos = Camera::GetLookPosition();
			cameraPos.y -= 500.0f * Time::DeltaTime();
			Camera::SetLookPosition(cameraPos);
		}
		else
		{
			Vector2 cameraPos = Camera::GetLookPosition();
			cameraPos.y += 500.0f * Time::DeltaTime();
			Camera::SetLookPosition(cameraPos);

		}





		if (mTime >= 0.2f)
		{
			curScene = SceneManager::GetActiveScene();
			mTime = 0.0f;


			if (charNum == 0)
			{
				deathSound->Play(false);
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(-300.0f, -300.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else if (charNum == 1)
			{
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(200.0f, -500.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else if (charNum == 2)
			{
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(-150.0f, 0.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else if (charNum == 3)
			{
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(0.0f, -400.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}

			else if (charNum == 4)
			{
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(-140.0f, -600.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else if (charNum == 5)
			{
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(-300.0f, -200.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else if (charNum == 6)
			{
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(-400.0f, -600.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else if (charNum == 7)
			{
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(340.0f, 0.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else if (charNum == 8)
			{
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(-150.0f, -400.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else if (charNum == 9)
			{
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(-140.0f, 0.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else if (charNum == 10)
			{
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(-240.0f, 0.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else if (charNum == 11)
			{
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(340.0f, 0.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else if (charNum == 12)
			{
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(0.0f, -400.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else if (charNum == 13)
			{

				startEndEvent = false;
				Vector2 cameraPos = Camera::GetLookPosition();
				cameraPos.y = 465.0f;
				Camera::SetLookPosition(cameraPos);

				Camera::SetStop(false);
				SetState(eState::Pause);



			}
			charNum++;
		}
	}
	void Boss1_Base::OnCollisionEnter(Collider* other)
	{
	}
	void Boss1_Base::OnCollisionStay(Collider* other)
	{
	}
	void Boss1_Base::OnCollisionExit(Collider* other)
	{
	}
}

