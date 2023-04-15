#include "moArabian.h"
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
extern mo::Application application;

namespace mo{
	Arabian::Arabian(Marco* marco, Scene* scene)
		: player(marco)
		, curScene(scene)
		, time(0.0f)
	{
	}

	Arabian::~Arabian()
	{
	}

	void Arabian::Initialize()
	{

		Image* mImageL = Resources::Load<Image>(L"ArabianLeft", L"..\\Resources\\Enemy\\ArabianLeft.bmp");
		Image* mImageR = Resources::Load<Image>(L"ArabianRight", L"..\\Resources\\Enemy\\ArabianRight.bmp");

		
		Transform* tr;
		tr = GetComponent<Transform>();
		//tr->SetPos(Vector2(1100.0f, 600.0f));
		tr->SetScale(Vector2{ 3.0f, 3.0f });
		tr->SetDisToBottom(Vector2{ 0.0f, 40.0f });
		tr->SetDirection(eDirection::Left);

		RigidBody* mRigidbody = AddComponent<RigidBody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2(0.0f, 600.0f));

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"IdleL", mImageL, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 20, 15, 6, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"DeathL", mImageL, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 20, 15, 11, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"MoveL", mImageL, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 20, 15, 12, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"ThrowingL", mImageL, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 20, 15, 19, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"AttackL", mImageL, Vector2(120.0f * 0, 120.0f * 4), 120.0f, 20, 15, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"TurnL", mImageL, Vector2(120.0f * 0, 120.0f * 5), 120.0f, 20, 15, 2, Vector2::Zero, 0.02);
		mAnimator->CreateAnimation(L"BackJumpL", mImageL, Vector2(120.0f * 0, 120.0f * 6), 120.0f, 20, 15, 8, Vector2::Zero, 0.5);

		mAnimator->CreateAnimation(L"IdleR", mImageR, Vector2(120.0f * 19, 120.0f * 0), -120.0f, 20, 15, 6, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"DeathR", mImageR, Vector2(120.0f * 19, 120.0f * 1), -120.0f, 20, 15, 11, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"MoveR", mImageR, Vector2(120.0f * 19, 120.0f * 2), -120.0f, 20, 15, 12, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"ThrowingR", mImageR, Vector2(120.0f * 19, 120.0f * 3), -120.0f, 20, 15, 19, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"AttackR", mImageR, Vector2(120.0f * 19, 120.0f * 4), -120.0f, 20, 15, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"TurnR", mImageR, Vector2(120.0f * 19, 120.0f * 5), -120.0f, 20, 15, 2, Vector2::Zero, 0.02);
		mAnimator->CreateAnimation(L"BackJumpR", mImageR, Vector2(120.0f * 19, 120.0f * 6), -120.0f, 20, 15, 8, Vector2::Zero, 0.5);

		mAnimator->Play(L"MoveL", true);
		mState = eArabianState::Move;

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 60.0f, 100.0f });
		mCollider->SetLeftTop(Vector2{ -30.50f, -100.0f });

		GameObject::Initialize();
	}

	void Arabian::Update()
	{

		if (GetState() == eState::Pause &&
			(
			mAnimator->GetActiveAnimation()->GetName() != L"DeathL" //|| mAnimator->GetActiveAnimation()->GetName() != L"DeathR"
			))
		{
			mAnimator->Play(L"DeathL", false);
			mState = eArabianState::Death;
		}

		switch (mState) {
		case mo::Arabian::eArabianState::Move:
			move();
			break;
		case mo::Arabian::eArabianState::Attack:
			attack();
			break;
		case mo::Arabian::eArabianState::Death:
			death();
			break;
		case mo::Arabian::eArabianState::Idle:
			idle();
			break;
		case mo::Arabian::eArabianState::Turn:
			turn();
			break;
		case mo::Arabian::eArabianState::Throwing:
			throwing();
			break; 
		case mo::Arabian::eArabianState::Run:
			run();
			break;
		default:
			break;
		}
		

		
		GameObject::Update();
	}

	void Arabian::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}

	void Arabian::OnCollisionEnter(Collider* other)
	{	
		

		if (other->GetOwner()->GetLayerType() == eLayerType::PlayerPistol) 
			SetState(eState::Pause);
		else if(other->GetOwner()->GetLayerType() == eLayerType::PlayerBomb)
			SetState(eState::Pause);
		else if (other->GetOwner()->GetLayerType() == eLayerType::PlayerMachinegun)
			SetState(eState::Pause);
	}

	void Arabian::OnCollisionStay(Collider* other)
	{
	}

	void Arabian::OnCollisionExit(Collider* other)
	{
	}

	void Arabian::move()
	{
		Transform* tr = GetComponent<Transform>();
		eDirection mDir = tr->GetDirection();
		Vector2 mPos = tr->GetPos();
		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();

		if (mDir == eDirection::Left)
		{
			if (playerPos.x + 300.0f < mPos.x)
			{
				mPos.x -= 200.0f * Time::DeltaTime();
				tr->SetPos(mPos);
			}
			else if (playerPos.x + 300.0f>= mPos.x && playerPos.x + 250.0f < mPos.x)
			{
				mAnimator->Play(L"ThrowingL", false);
				mState = eArabianState::Throwing;
			}
			else if (playerPos.x + 150.0f >= mPos.x)
			{
				mAnimator->Play(L"AttackL", false);
				EnemyAttackCollider* enemyKnife = new EnemyAttackCollider(mPos, Vector2(-120.0f, -100.0f), Vector2(120.0f, 80.0f));
				curScene->AddGameObject(enemyKnife, eLayerType::EnemyBullet);
				enemyKnife->Initialize();
				mState = eArabianState::Attack;
			}
		}
		else if (mDir == eDirection::Right)
		{
			if (playerPos.x - 300.0f >= mPos.x)
			{
				mPos.x += 200.0f * Time::DeltaTime();
				tr->SetPos(mPos);
			}
			else if (playerPos.x - 300.0f < mPos.x && playerPos.x - 250.0f >= mPos.x)
			{
				mAnimator->Play(L"ThrowingR", false);
				mState = eArabianState::Throwing;
			}
			else if (playerPos.x - 150.0f < mPos.x)
			{
				mAnimator->Play(L"AttackR", false);
				EnemyAttackCollider* enemyKnife = new EnemyAttackCollider(mPos, Vector2(120.0f, -100.0f), Vector2(120.0f, 80.0f));
				curScene->AddGameObject(enemyKnife, eLayerType::EnemyBullet);
				enemyKnife->Initialize();
				mState = eArabianState::Attack;
			}

		}
	}

	void Arabian::attack()
	{
		Transform* tr = GetComponent<Transform>();
		eDirection mDir = tr->GetDirection();
		Vector2 mPos = tr->GetPos();
		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();

		if (mAnimator->IsComplte())
		{
			if (mDir == eDirection::Left)
			{
				if (playerPos.x >= mPos.x)
				{
					mAnimator->Play(L"TurnL", false); 
					mDir = eDirection::Right;
					tr->SetDirection(mDir);
					mState = eArabianState::Turn;
				}
				else if (playerPos.x + 250.0f >= mPos.x)
				{
					mAnimator->Play(L"MoveR", true);
					mDir = eDirection::Right;
					tr->SetDirection(mDir);
					mState = eArabianState::Run;
				}
				else if (playerPos.x + 300.0f >= mPos.x && playerPos.x + 250.0f < mPos.x)
				{
					mAnimator->Play(L"ThrowingL", false);
					mState = eArabianState::Throwing;
				}
				else if (playerPos.x + 300.0f < mPos.x)
				{
					mAnimator->Play(L"MoveL", true);
					mState = eArabianState::Move;
				}
			}
			else if (mDir == eDirection::Right)
			{
				if (playerPos.x < mPos.x)
				{
					mAnimator->Play(L"TurnR", false);
					mDir = eDirection::Left;
					tr->SetDirection(mDir);
					mState = eArabianState::Turn;
				}
				else if (playerPos.x - 250.0f < mPos.x)
				{
					mAnimator->Play(L"MoveL", true);
					mDir = eDirection::Left;
					tr->SetDirection(mDir);
					mState = eArabianState::Run;
				}
				else if (playerPos.x - 300.0f < mPos.x && playerPos.x - 250.0f >= mPos.x)
				{
					mAnimator->Play(L"ThrowingR", false);
					mState = eArabianState::Throwing;
				}
				else if (playerPos.x - 300.0f >= mPos.x)
				{
					mAnimator->Play(L"MoveR", true);
					mState = eArabianState::Move;
				}
			}
		}
	}

	void Arabian::death()
	{
		if(mAnimator->IsComplte())
			object::Destory(this);
	}

	void Arabian::idle()
	{
		Transform* tr = GetComponent<Transform>();
		eDirection mDir = tr->GetDirection();
		Vector2 mPos = tr->GetPos();
		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();

		if (mDir == eDirection::Left)
		{
			if (playerPos.x >= mPos.x)
			{
				mAnimator->Play(L"TurnL", false);
				mDir = eDirection::Right;
				tr->SetDirection(mDir);
				mState = eArabianState::Turn;
			}
			else if (playerPos.x + 300.0f < mPos.x)
			{
				mAnimator->Play(L"MoveL", true);
				mState = eArabianState::Move;
			}
		/*	else if (playerPos.x + 300.0f >= mPos.x && playerPos.x + 250.0f < mPos.x)
			{
				mAnimator->Play(L"ThrowingL", false);
				mState = eArabianState::Throwing;
			}*/
			else if (playerPos.x + 150.0f >= mPos.x)
			{
				mAnimator->Play(L"AttackL", false);
				EnemyAttackCollider* enemyKnife = new EnemyAttackCollider(mPos, Vector2(-120.0f, -100.0f), Vector2(120.0f, 80.0f));
				curScene->AddGameObject(enemyKnife, eLayerType::EnemyBullet);
				enemyKnife->Initialize();
				mState = eArabianState::Attack;
			}
		}
		else if (mDir == eDirection::Right)
		{
			if (playerPos.x < mPos.x)
			{
				mAnimator->Play(L"TurnR", false);
				mDir = eDirection::Left;
				tr->SetDirection(mDir);
				mState = eArabianState::Turn;
			}
			else if (playerPos.x - 300.0f > mPos.x)
			{
				mAnimator->Play(L"MoveR", true);
				mState = eArabianState::Move;
			}
		/*	else if (playerPos.x - 300.0f < mPos.x && playerPos.x - 250.0f >= mPos.x)
			{
				mAnimator->Play(L"ThrowingR", false);
				mState = eArabianState::Throwing;
			}*/
			else if (playerPos.x - 150.0f < mPos.x)
			{
				mAnimator->Play(L"AttackR", false);
				EnemyAttackCollider* enemyKnife = new EnemyAttackCollider(mPos, Vector2(120.0f, -100.0f), Vector2(120.0f, 80.0f));
				curScene->AddGameObject(enemyKnife, eLayerType::EnemyBullet);
				enemyKnife->Initialize();
				mState = eArabianState::Attack;
			}
		
		}
		
		if (player->GetState() == eState::Pause)
		{
			if (mDir == eDirection::Left)
			{
				mAnimator->Play(L"MoveR", true);
				mDir = eDirection::Right;
				tr->SetDirection(mDir);
				mState = eArabianState::Run;
			}
			else if (mDir == eDirection::Right)
			{
				mAnimator->Play(L"MoveL", true);
				mDir = eDirection::Left;
				tr->SetDirection(mDir);
				mState = eArabianState::Run;
			}
		}

	}
	void Arabian::throwing()
	{
		Transform* tr = GetComponent<Transform>();
		eDirection mDir = tr->GetDirection();
		Vector2 mPos = tr->GetPos();
		//Vector2 playerPos = player->GetComponent<Transform>()->GetPos();

		time += Time::DeltaTime();
		if (player->GetState() == eState::Pause)
		{
			if (mDir == eDirection::Left)
			{
				mAnimator->Play(L"MoveR", true);
				mDir = eDirection::Right;
				tr->SetDirection(mDir);
				mState = eArabianState::Run;
			}
			else if (mDir == eDirection::Right)
			{
				mAnimator->Play(L"MoveL", true);
				mDir = eDirection::Left;
				tr->SetDirection(mDir);
				mState = eArabianState::Run;
			}
		}

		if (mDir == eDirection::Left)
		{
			if (!isThrowing && time >=0.5)
			{
				isThrowing = true;
				
				ArabianWeapon* weapon = new ArabianWeapon();
				curScene->AddGameObject(weapon, eLayerType::EnemyBulletR);
				weapon->Initialize();
				weapon->GetComponent<Transform>()->SetPos(mPos + Vector2(0.0f, -30.0f));
				weapon->PlayAnimation(mDir);
			}
			if (mAnimator->IsComplte())
			{
				
				time = 0.0f;
				isThrowing = false;
				mAnimator->Play(L"IdleL", true);
				mState = eArabianState::Idle;
			}
		}
		else if (mDir == eDirection::Right)
		{
			if (!isThrowing && time >= 0.5)
			{
				isThrowing = true;

				ArabianWeapon* weapon = new ArabianWeapon();
				curScene->AddGameObject(weapon, eLayerType::EnemyBulletR);
				weapon->Initialize();
				weapon->GetComponent<Transform>()->SetPos(mPos + Vector2(0.0f, -30.0f));
				weapon->PlayAnimation(mDir);
			}
			if (mAnimator->IsComplte())
			{
				
				time = 0.0f;
				isThrowing = false;
				mAnimator->Play(L"IdleR", true);
				mState = eArabianState::Idle;
			}
		}
	}

	void Arabian::turn()
	{
		Transform* tr = GetComponent<Transform>();
		eDirection mDir = tr->GetDirection();
		if (mAnimator->IsComplte())
		{
			if (mDir == eDirection::Right)
			{
				mAnimator->Play(L"IdleR", true);
				mState = eArabianState::Idle;

			}
			else if (mDir == eDirection::Left)
			{
				mAnimator->Play(L"IdleL", true);
				mState = eArabianState::Idle;
			}
			
		}
	}

	void Arabian::run()
	{
		Transform* tr = GetComponent<Transform>();
		eDirection mDir = tr->GetDirection();
		Vector2 mPos = tr->GetPos();
		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();

		if (mDir == eDirection::Right)
		{
			mPos.x += 400.0f * Time::DeltaTime();
			tr->SetPos(mPos);
			if (playerPos.x + 1100.0f <= mPos.x)
				object::Destory(this);
		}
		else if (mDir == eDirection::Left)
		{
			mPos.x -= 400.0f * Time::DeltaTime();
			tr->SetPos(mPos);
			if (playerPos.x - 500.0f >= mPos.x)
				object::Destory(this);
		}

	
	}

	
	
}