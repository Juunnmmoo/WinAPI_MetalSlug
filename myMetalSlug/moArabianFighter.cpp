#include "moArabianFighter.h"
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
#include "moCamel.h"
#include "moCamelArabian02.h"
#include "moEnemyPistolBullet.h"
#include "moSound.h"
namespace mo {
	ArabianFighter::ArabianFighter(Marco* p, Vector2 stop, int max, eArabianFighterState state)
		: player(p)
		, stopPos(stop)
		, heart(8)
		, maxTurn(max)
		, runCnt(0)
		, mState(state)
	{
	}
	ArabianFighter::~ArabianFighter()
	{
	}
	void ArabianFighter::Initialize()
	{

		EnemyDeathSound4 = Resources::Load<Sound>(L"EnemyDeathSound1", L"..\\Resources\\Sound\\EnemyDeathSound1.wav");
		EnemyDeathSound4->SetVolume(80);

		Image* mImageL = Resources::Load<Image>(L"ArabianFighterLeft", L"..\\Resources\\Enemy\\ArabianFighterLeft.bmp");
		Image* mImageR = Resources::Load<Image>(L"ArabianFighterRight", L"..\\Resources\\Enemy\\ArabianFighterRight.bmp");


		Transform* tr;
		tr = GetComponent<Transform>();
		//tr->SetPos(Vector2(1100.0f, 600.0f));
		tr->SetScale(Vector2{ 3.0f, 3.0f });
		tr->SetDirection(eDirection::Left);

		RigidBody* mRigidbody = AddComponent<RigidBody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2(0.0f, 600.0f));

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"SitL", mImageL, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 10, 10, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"StandL", mImageL, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 10, 10, 4, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"ReadyFowordL", mImageL, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 10, 10, 3, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"FowordL", mImageL, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 10, 10, 6, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"TurnL", mImageL, Vector2(120.0f * 0, 120.0f * 4), 120.0f, 10, 10, 3, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"AttackL", mImageL, Vector2(120.0f * 0, 120.0f * 5), 120.0f, 10, 10, 6, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"DeathL", mImageL, Vector2(120.0f * 0, 120.0f * 6), 120.0f, 10, 10, 9, Vector2::Zero, 0.05);

		mAnimator->CreateAnimation(L"SitR", mImageR, Vector2(120.0f * 9, 120.0f * 0), -120.0f, 10, 10, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"StandR", mImageR, Vector2(120.0f * 9, 120.0f * 1), -120.0f, 10, 10, 4, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"ReadyFowordR", mImageR, Vector2(120.0f * 9, 120.0f * 2), -120.0f, 10, 10, 3, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"FowordR", mImageR, Vector2(120.0f * 9, 120.0f * 3), -120.0f, 10, 10, 6, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"TurnR", mImageR, Vector2(120.0f * 9, 120.0f * 4), -120.0f, 10, 10, 3, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"AttackR", mImageR, Vector2(120.0f * 9, 120.0f * 5), -120.0f, 10, 10, 6, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"DeathR", mImageR, Vector2(120.0f * 9, 120.0f * 6), -120.0f, 10, 10, 9, Vector2::Zero, 0.05);
		
		if(mState == eArabianFighterState::Move || mState == eArabianFighterState::Foword)
			mAnimator->Play(L"FowordL", true);
		else if(mState == eArabianFighterState::Idle)
			mAnimator->Play(L"SitL", true);


		Collider* mCollider = AddComponent<Collider>();		
		mCollider->SetLeftTop(Vector2{ -30.50f, -100.0f });
		mCollider->SetSize(Vector2{ 60.0f, 100.0f });

		GameObject::Initialize();
	}
	void ArabianFighter::Update()
	{
		time += Time::DeltaTime();

		if (!startFoword && time >= 5.0f)
		{
			startFoword = true;
		}

		switch (mState) {
		case::mo::ArabianFighter::eArabianFighterState::Idle:
			idle();
			break;
		case::mo::ArabianFighter::eArabianFighterState::Move:
			move();
			break;
		case::mo::ArabianFighter::eArabianFighterState::Sit:
			sit();
			break;
		case::mo::ArabianFighter::eArabianFighterState::Foword:
			foword();
			break;
		case::mo::ArabianFighter::eArabianFighterState::Attack:
			attack();
			break;
		case::mo::ArabianFighter::eArabianFighterState::Death:
			death();
			break;
		case::mo::ArabianFighter::eArabianFighterState::Turn:
			turn();
			break; 
		case::mo::ArabianFighter::eArabianFighterState::MoveAway:
			moveAway();
			break;
		default:
			break;
		}

		if (mState != eArabianFighterState::Death && heart == 0)
		{
			Transform* tr;
			tr = GetComponent<Transform>();

			SetState(eState::Pause);
			EnemyDeathSound4->Play(false);
			if (tr->GetDirection() == eDirection::Left)
			{
				mAnimator->Play(L"DeathL", false);
				mState = eArabianFighterState::Death;
			}
			else
			{
				mAnimator->Play(L"DeathR", false);
				mState = eArabianFighterState::Death;
			}
		}

		GameObject::Update();
	}
	void ArabianFighter::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}
	void ArabianFighter::OnCollisionEnter(Collider* other)
	{
		if ((other->GetOwner()->GetLayerType() == eLayerType::PlayerPistol || other->GetOwner()->GetLayerType() == eLayerType::PlayerMachinegun)&&
			heart > 0)
		{
			heart--;
		}
		if ((other->GetOwner()->GetLayerType() == eLayerType::PlayerBomb || other->GetOwner()->GetLayerType() == eLayerType::PlayerShotgun)&&heart > 0)
		{
			heart = 0;
		}
	}
	void ArabianFighter::OnCollisionStay(Collider* other)
	{
	}
	void ArabianFighter::OnCollisionExit(Collider* other)
	{
	}
	void ArabianFighter::idle()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 cPos = Camera::CaluatePos(pos);

	
		if (Camera::GetStop() && cPos.x < 1100.0f && cPos.x >= 0.0f)
		{

			mAnimator->Play(L"FowordL", true);
			mState = eArabianFighterState::Foword;
		}
		
	}
	void ArabianFighter::move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x -= 200.0f * Time::DeltaTime();
		tr->SetPos(pos);

		if (pos.x <= stopPos.x)
		{
			mAnimator->Play(L"SitL", true);
			mState = eArabianFighterState::Sit;
		}
	}
	void ArabianFighter::sit()
	{
		if (startFoword)
		{
			mAnimator->Play(L"FowordL", true);
			mState = eArabianFighterState::Foword;
		}
	}
	void ArabianFighter::foword()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		eDirection mDir = tr->GetDirection();
		Vector2 cPos = Camera::CaluatePos(pos);

		
		Transform* playerTR = player->GetComponent<Transform>();
		Vector2 playerPos = playerTR->GetPos();

	

		if (mDir == eDirection::Left)
		{
			pos.x -= 200.0f * Time::DeltaTime();
			tr->SetPos(pos);

			if (pos.x <= playerPos.x + 80.0f && pos.x > playerPos.x )
			{
				
				
					mAnimator->Play(L"AttackL", false);

					Scene* curScene;
					curScene = SceneManager::GetActiveScene();
					EnemyAttackCollider* enemyKnife = new EnemyAttackCollider(pos, Vector2(-120.0f, -100.0f), Vector2(120.0f, 80.0f), 0.3);
					curScene->AddGameObject(enemyKnife, eLayerType::EnemyBullet);
					enemyKnife->Initialize();

					mState = eArabianFighterState::Attack;
				
			}
			
			if (cPos.x <= 50.0f) {

				runCnt++;
				if (runCnt >= maxTurn)
				{

					mState = eArabianFighterState::MoveAway;
				}
				else
				{
					mAnimator->Play(L"TurnL", false);
					tr->SetDirection(eDirection::Right);
					mState = eArabianFighterState::Turn;
				}
			}
			
		}
		else
		{
			pos.x += 200.0f * Time::DeltaTime();
			tr->SetPos(pos);

			if (pos.x >= playerPos.x - 80.0f && pos.x < playerPos.x)
			{
				mAnimator->Play(L"AttackR", false);

				Scene* curScene;
				curScene = SceneManager::GetActiveScene();
				EnemyAttackCollider* enemyKnife = new EnemyAttackCollider(pos, Vector2(0.0f, -100.0f), Vector2(120.0f, 80.0f), 0.3);
				curScene->AddGameObject(enemyKnife, eLayerType::EnemyBullet);
				enemyKnife->Initialize();

				mState = eArabianFighterState::Attack;
			}
			if (cPos.x >= 700.0f) {
				mAnimator->Play(L"TurnR", false);
				tr->SetDirection(eDirection::Left);
				mState = eArabianFighterState::Turn;
			}
		}

	}
	void ArabianFighter::attack()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		eDirection mDir = tr->GetDirection();
		Vector2 cPos = Camera::CaluatePos(pos);

		if (mDir == eDirection::Left)
		{
			pos.x -= 200.0f * Time::DeltaTime();
			tr->SetPos(pos);

			if (mAnimator->IsComplte())
			{
				mAnimator->Play(L"FowordL", true);
				mState = eArabianFighterState::Foword;
			}
			if (cPos.x <= 50.0f) {
				mAnimator->Play(L"TurnL", false);
				tr->SetDirection(eDirection::Right);
				mState = eArabianFighterState::Turn;
			}
		}
		else
		{
			pos.x += 200.0f * Time::DeltaTime();
			tr->SetPos(pos);
			if (mAnimator->IsComplte())
			{
				mAnimator->Play(L"FowordR", true);
				mState = eArabianFighterState::Foword;
			}
			if (cPos.x >= 800.0f) {
				mAnimator->Play(L"TurnR", false);
				tr->SetDirection(eDirection::Left);
				mState = eArabianFighterState::Turn;
			}
		}

		
	}
	void ArabianFighter::death()
	{
		if (mAnimator->IsComplte())
		{
			object::Destory(this);
		}
	}
	void ArabianFighter::moveAway()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		eDirection mDir = tr->GetDirection();
		Vector2 cPos = Camera::CaluatePos(pos);

		pos.x -= 200.0f * Time::DeltaTime();
		tr->SetPos(pos);

		if (cPos.x <= -100.0f)
			object::Destory(this);


	}
	void ArabianFighter::turn()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		eDirection mDir = tr->GetDirection();
		Vector2 cPos = Camera::CaluatePos(pos);
		
		if (mAnimator->IsComplte())
		{
			if (mDir == eDirection::Left)
			{
				mAnimator->Play(L"FowordL", true);
				mState = eArabianFighterState::Foword;
			}
			else
			{
				mAnimator->Play(L"FowordR", true);
				mState = eArabianFighterState::Foword;
			}
		}
	}

}