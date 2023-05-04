#include "moBoss2_Base.h"
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
#include "moAnimator.h"
#include "moBoss2_Door.h"
#include "moBoss2_Weapon.h"
#include "moBoss2_Propeller.h"
#include "moArabian.h"
#include "moBoss2LaserCollider.h"
#include "moMissionComplete.h"
#include "moArmyRoket.h"

namespace mo {
	Boss2_Base::Boss2_Base(Marco* marco, Scene* scene, Boss2_Door* door, Boss2_Weapon* energy, Boss2_Propeller* propeller, Boss2LaserCollider* left, Boss2LaserCollider* right
	, ArmyRoket* leftRoket, ArmyRoket* rightRoket, AbulAbbas* abul)
		: mDoor(door)
		, mPropeller(propeller)
		, mWeapon(energy)
		, mPlayer(marco)
		, curScene(scene)
		, mTime(0.0f)
		, heart(330)
		//, heart(1)
		, mLeft(left)
		, mRight(right)
		, mLeftRoket(leftRoket)
		, mRightRoket(rightRoket)
		, mAbul(abul)
	{
	}
	Boss2_Base::~Boss2_Base()
	{
	}
	void Boss2_Base::Initialize()
	{
		BossBGM = Resources::Load<Sound>(L"Boss2Sound", L"..\\Resources\\Sound\\Boss2Sound.wav");
		BossBGM->Play(true);
		deathSound = Resources::Load<Sound>(L"Boss1DeathSound", L"..\\Resources\\Sound\\Boss1DeathSound.wav");
		deathSound->SetVolume(80);
		downSound = Resources::Load<Sound>(L"Boss2DownSound", L"..\\Resources\\Sound\\Boss2DownSound.wav");
		downSound->SetVolume(80);
		missionComplete = Resources::Load<Sound>(L"missionComplete", L"..\\Resources\\Sound\\missionComplete.wav");
		missionComplete->SetVolume(80);

		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(12512.0f, 350.0f));
		tr->SetScale(Vector2(3.5f, 3.5f));
		tr->SetDirection(eDirection::Left);
		Vector2 cPos = Camera::CaluatePos(tr->GetPos());

		image = Resources::Load<Image>(L"Boss2_Base", L"..\\Resources\\Enemy\\Boss2\\Boss2_Base.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Base1", image, Vector2(272.0f * 0, 100.0f * 0), 272.0f, 9, 1, 1, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Base2", image, Vector2(272.0f * 1, 100.0f * 0), 272.0f, 9, 1, 1, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Base3", image, Vector2(272.0f * 2, 100.0f * 0), 272.0f, 9, 1, 1, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Base4", image, Vector2(272.0f * 3, 100.0f * 0), 272.0f, 9, 1, 1, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Base5", image, Vector2(272.0f * 4, 100.0f * 0), 272.0f, 9, 1, 1, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Base6", image, Vector2(272.0f * 5, 100.0f * 0), 272.0f, 9, 1, 1, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Base7", image, Vector2(272.0f * 6, 100.0f * 0), 272.0f, 9, 1, 1, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Base8", image, Vector2(272.0f * 7, 100.0f * 0), 272.0f, 9, 1, 1, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"Destroyed", image, Vector2(272.0f * 8, 100.0f * 0), 272.0f, 9, 1, 1, Vector2::Zero, 0.03);

		mAnimator->Play(L"Base1", false);

		Collider* collider = AddComponent<Collider>();
		collider->SetLeftTop(Vector2(-200.0f, -750.0f));
		collider->SetSize(Vector2(400.0f, 200.0f));

		/*abul = new AbulAbbas(Vector2(5800.0f, 0.0f), mo::AbulAbbas::eAbulAbbasState::Idle);
		curScene->AddGameObject(abul, eLayerType::EnemyR);
		abul->Initialize();
		abul->GetComponent<Transform>()->SetPos(Vector2(7520.0f, 0.0f));*/

		GameObject::Initialize();
	}
	void Boss2_Base::Update()
	{


		switch (mState)
		{
		case mo::Boss2_Base::eBoss2FSM::None:
			none();
			break;
		case mo::Boss2_Base::eBoss2FSM::Down:
			down();
			break;
		case mo::Boss2_Base::eBoss2FSM::DropArabian:
			dropArabian();
			break;
		case mo::Boss2_Base::eBoss2FSM::DropArmy:
			dropArmy();
			break;
		case mo::Boss2_Base::eBoss2FSM::BeforeAttack:
			beforeAttack();
			break;
		case mo::Boss2_Base::eBoss2FSM::Attack:
			attack();
			break;
		case mo::Boss2_Base::eBoss2FSM::AfterAttack:
			afterAttack();
			break;
		case mo::Boss2_Base::eBoss2FSM::Death:
			death();
			break;

		}

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		mDoor->GetComponent<Transform>()->SetPos(pos + Vector2(0.0f, -85.0f));
		mPropeller->GetComponent<Transform>()->SetPos(pos + Vector2(0.0f, -85.0f));
		mWeapon->GetComponent<Transform>()->SetPos(pos + Vector2(0.0f, 434.0f - 85.0f));
		mLeft->GetComponent<Transform>()->SetPos(pos + Vector2(-340.0f, -550.0f));
		mRight->GetComponent<Transform>()->SetPos(pos + Vector2(280.0f, -550.0f));

		if (heart <= 300 && heart > 270)
		{
			mAnimator->Play(L"Base2", false);
		}
		else if (heart <= 270 && heart > 240)
		{
			mAnimator->Play(L"Base3", false);
		}
		else if (heart <= 240 && heart > 200)
		{
			mAnimator->Play(L"Base4", false);
		}
		else if (heart <= 200 && heart > 160)
		{
			mAnimator->Play(L"Base5", false);
		}
		else if (heart <= 160 && heart > 120)
		{
			mAnimator->Play(L"Base6", false);
		}
		else if (heart <= 120 && heart > 80)
		{
			mAnimator->Play(L"Base7", false);
		}
		else if (heart <= 80 && heart > 40)
		{
			mAnimator->Play(L"Base8", false);
		}
		else if (heart <= 0 && !gotoDeath)
		{
			gotoDeath = true;
			mState = eBoss2FSM::Death;
			//mAnimator->Play(L"Base1", false);
		}

		mPlayer->SetBossX(pos.x);

		GameObject::Update();

	}
	void Boss2_Base::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void Boss2_Base::EndEvent()
	{
	}
	void Boss2_Base::OnCollisionEnter(Collider* other)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (other->GetOwner()->GetLayerType() == eLayerType::PlayerPistol ||
			other->GetOwner()->GetLayerType() == eLayerType::PlayerMachinegun
			)
		{
			heart--;
		}
		if (other->GetOwner()->GetLayerType() == eLayerType::PlayerBomb)
		{
			heart -= 10;
		}
	}
	void Boss2_Base::OnCollisionStay(Collider* other)
	{
	}
	void Boss2_Base::OnCollisionExit(Collider* other)
	{
	}
	void Boss2_Base::none()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 cPos = Camera::CaluatePos(pos);

		if (cPos.x > 0.0f)
		{
			mAbul->StartAttack();
			downSound->Play(false);
			mState = eBoss2FSM::Down;
		}
	}
	void Boss2_Base::down()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 cPos = Camera::CaluatePos(pos);

		pos.y += 100.0f * Time::DeltaTime();
		tr->SetPos(pos);
		if (pos.y >= 950.0f)
		{
			mState = eBoss2FSM::DropArabian;
		}
	}
	void Boss2_Base::dropArabian()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		mTime += Time::DeltaTime();

		if (mTime >= 3.0f)
		{
			if (!isOpened)
			{
				isOpened = true;
				mTime = 1.0f;

				mDoor->GetAnimator()->Play(L"Open", false);
			}
			else
			{
				mTime = 0.0f;

				Arabian* arabianR = new Arabian(mPlayer, curScene, Arabian::eArabianState::Move);

				curScene->AddGameObject(arabianR, eLayerType::EnemyR);
				arabianR->Initialize();
				arabianR->GetAnimator()->Play(L"MoveR", true);
				arabianR->GetComponent<Transform>()->SetDirection(eDirection::Right);
				arabianR->GetComponent<Transform>()->SetPos(pos + Vector2(50.0f, -750.0f));


				Arabian* arabianL = new Arabian(mPlayer, curScene, Arabian::eArabianState::Move);

				curScene->AddGameObject(arabianL, eLayerType::EnemyR);
				arabianL->Initialize();
				arabianL->GetComponent<Transform>()->SetPos(pos + Vector2(-50.0f, -750.0f));
			}

		}

		if (heart <= 240)
		{
			mTime = 0.0f;
			isOpened = false;
			mDoor->GetAnimator()->Play(L"Close", false);
			mState = eBoss2FSM::DropArmy;
		}

	}
	void Boss2_Base::dropArmy()
	{


		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (pos.y >= 900.0f)
		{
			pos.y -= 50.0f * Time::DeltaTime();
			tr->SetPos(pos);
		}
		else
		{
			mTime += Time::DeltaTime();
			if (!isOpened)
			{
				isOpened = true;
				mDoor->GetAnimator()->Play(L"Open", false);
			}
			if (mTime >= 0.5f && !outArmyOnce)
			{
				outArmyOnce = true;
				mLeftRoket->ArmyAppear();
				mRightRoket->ArmyAppear();

			}
			if (mTime >= 3.0f)
			{
				
				mLeftRoket->StopMove();
				mRightRoket->StopMove();

				mPropeller->GetAnimator()->Play(L"Attack", true);
				mWeapon->GetAnimator()->Play(L"BeforeAttack", false);

				mLeft->SetState(eState::Active);
				mRight->SetState(eState::Active);

				mTime = 0.0f;
				mState = eBoss2FSM::BeforeAttack;

			}


		}
	}
	void Boss2_Base::beforeAttack()
	{

		if (mWeapon->GetAnimator()->IsComplte())
		{


			mWeapon->GetAnimator()->Play(L"Attack", true);
			Camera::SetBoss2Move(true);
			mState = eBoss2FSM::Attack;
		}
	}
	void Boss2_Base::attack()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 lPos = mLeftRoket->GetComponent<Transform>()->GetPos();
		Vector2 rPos = mRightRoket->GetComponent<Transform>()->GetPos();


		mTime += Time::DeltaTime();

		if (tr->GetDirection() == eDirection::Left)
		{
			if (pos.x > 12000.0f)
			{
				pos.x -= 150.0f * Time::DeltaTime();
				lPos.x -= 150.0f * Time::DeltaTime();
				rPos.x -= 150.0f * Time::DeltaTime();
				tr->SetPos(pos);
				mLeftRoket->GetComponent<Transform>()->SetPos(lPos);
				mRightRoket->GetComponent<Transform>()->SetPos(rPos);
			}
			else
			{
				tr->SetDirection(eDirection::Right);
			}
		}
		else
		{
			if (pos.x <= 12500.0f)
			{
				pos.x += 150.0f * Time::DeltaTime();
				lPos.x += 150.0f * Time::DeltaTime();
				rPos.x += 150.0f * Time::DeltaTime();
				tr->SetPos(pos);
				mLeftRoket->GetComponent<Transform>()->SetPos(lPos);
				mRightRoket->GetComponent<Transform>()->SetPos(rPos);
			}
			else
			{
				tr->SetDirection(eDirection::Left);
			}
		}

		if (mTime >= 15.0f)
		{
			mTime = 0.0f;
			mWeapon->GetAnimator()->Play(L"AfterAttack", false);

			mLeft->SetState(eState::Pause);
			mRight->SetState(eState::Pause);


			Camera::SetBoss2Move(false);
			mState = eBoss2FSM::AfterAttack;
		}
	}
	void Boss2_Base::afterAttack()
	{

		if (mWeapon->GetAnimator()->IsComplte())
		{
			mWeapon->GetAnimator()->Play(L"Idle", true);
		}

		mTime += Time::DeltaTime();
		if (mTime >= 5.0f)
		{
			mTime = 0.0f;

			mLeft->SetState(eState::Active);
			mRight->SetState(eState::Active);

			mWeapon->GetAnimator()->Play(L"BeforeAttack", false);
			mState = eBoss2FSM::BeforeAttack;
		}
	}
	void Boss2_Base::death()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 cPos = Camera::CaluatePos(pos);


		if (pos.y < 1250.0f)
		{
			pos.y += 100.0f * Time::DeltaTime();
			tr->SetPos(pos);
		}


		mTime += Time::DeltaTime();

		if (mTime >= 0.2f)
		{
			curScene = SceneManager::GetActiveScene();
			mTime = 0.0f;


			if (charNum == 0)
			{
				mAbul->StartGiveUp();
				mWeapon->GetAnimator()->Play(L"None", false);
				mDoor->GetAnimator()->Play(L"None", false);
				mPropeller->GetAnimator()->Play(L"None", false);
				mLeft->SetState(eState::Pause);
				mRight->SetState(eState::Pause);

				object::Destory(mLeftRoket);
				object::Destory(mRightRoket);


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
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(340.0f, -800.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else if (charNum == 14)
			{
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(200.0f, -300.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else if (charNum == 15)
			{
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(-300.0f, -400.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else if (charNum == 16)
			{
				BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos + Vector2(0.0f, -600.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 36.0f));
				curScene->AddGameObject(bulletSFX, eLayerType::Effect);
				bulletSFX->Initialize();
				bulletSFX->PlayAnimation();
			}
			else if (charNum == 17)
			{
					mAnimator->Play(L"Destroyed", false);

					BulletSFX* bulletSFX1 = new BulletSFX(eSfxType::Boss2SFX, pos + Vector2(-200.0f, -600.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 0.0f));
					curScene->AddGameObject(bulletSFX1, eLayerType::Effect);
					bulletSFX1->Initialize();
					bulletSFX1->PlayAnimation();
				
					BulletSFX* bulletSFX2 = new BulletSFX(eSfxType::Boss2SFX, pos + Vector2(0.0f, -600.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 0.0f));
					curScene->AddGameObject(bulletSFX2, eLayerType::Effect);
					bulletSFX2->Initialize();
					bulletSFX2->PlayAnimation();

					BulletSFX* bulletSFX3 = new BulletSFX(eSfxType::Boss2SFX, pos + Vector2(200.0f, -600.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 0.0f));
					curScene->AddGameObject(bulletSFX3, eLayerType::Effect);
					bulletSFX3->Initialize();
					bulletSFX3->PlayAnimation();

					BulletSFX* bulletSFX4 = new BulletSFX(eSfxType::Boss2SFX, pos + Vector2(-100.0f, -300.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 0.0f));
					curScene->AddGameObject(bulletSFX4, eLayerType::Effect);
					bulletSFX4->Initialize();
					bulletSFX4->PlayAnimation();

					BulletSFX* bulletSFX5 = new BulletSFX(eSfxType::Boss2SFX, pos + Vector2(100.0f, -300.0f), Vector2(5.0f, 5.0f), Vector2(0.0f, 0.0f));
					curScene->AddGameObject(bulletSFX5, eLayerType::Effect);
					bulletSFX5->Initialize();
					bulletSFX5->PlayAnimation();

					mPlayer->MissionComplete();
			}
			else if (charNum == 25)
			{


				SetState(eState::Pause);

				MissionComplete* startUi = new MissionComplete(eSceneType::Mission1);
				curScene->AddGameObject(startUi, eLayerType::UI);
				startUi->Initialize();
				BossBGM->Stop(true);
				missionComplete->Play(false);
			}
			charNum++;
		}

	}
}