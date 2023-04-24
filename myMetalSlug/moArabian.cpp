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
	Arabian::Arabian(Marco* marco, Scene* scene, eArabianState state)
		: player(marco)
		, curScene(scene)
		, time(0.0f)
		, mState(state)
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
		mRigidbody->SetGravity(Vector2(0.0f, 1000.0f));

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"IdleL", mImageL, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 20, 15, 6, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"KnifeDeathL", mImageL, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 20, 15, 11, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"MoveL", mImageL, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 20, 15, 12, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"ThrowingL", mImageL, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 20, 15, 19, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"AttackL", mImageL, Vector2(120.0f * 0, 120.0f * 4), 120.0f, 20, 15, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"TurnL", mImageL, Vector2(120.0f * 0, 120.0f * 5), 120.0f, 20, 15, 2, Vector2::Zero, 0.02);
		mAnimator->CreateAnimation(L"BackJumpL", mImageL, Vector2(120.0f * 0, 120.0f * 6), 120.0f, 20, 15, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"ReadyAttackL", mImageL, Vector2(120.0f * 0, 120.0f * 7), 120.0f, 20, 15, 4, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"BulletDeathL", mImageL, Vector2(120.0f * 0, 120.0f * 8), 120.0f, 20, 15, 20, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"JumpL", mImageL, Vector2(120.0f * 0, 120.0f * 9), 120.0f, 20, 15, 13, Vector2::Zero, 0.07);


		mAnimator->CreateAnimation(L"IdleR", mImageR, Vector2(120.0f * 19, 120.0f * 0), -120.0f, 20, 15, 6, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"KnifeDeathR", mImageR, Vector2(120.0f * 19, 120.0f * 1), -120.0f, 20, 15, 11, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"MoveR", mImageR, Vector2(120.0f * 19, 120.0f * 2), -120.0f, 20, 15, 12, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"ThrowingR", mImageR, Vector2(120.0f * 19, 120.0f * 3), -120.0f, 20, 15, 19, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"AttackR", mImageR, Vector2(120.0f * 19, 120.0f * 4), -120.0f, 20, 15, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"TurnR", mImageR, Vector2(120.0f * 19, 120.0f * 5), -120.0f, 20, 15, 2, Vector2::Zero, 0.02);
		mAnimator->CreateAnimation(L"BackJumpR", mImageR, Vector2(120.0f * 19, 120.0f * 6), -120.0f, 20, 15, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"ReadyAttackR", mImageR, Vector2(120.0f * 19, 120.0f * 7), -120.0f, 20, 15, 4, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"BulletDeathR", mImageR, Vector2(120.0f * 19, 120.0f * 8), -120.0f, 20, 15, 20, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"JumpR", mImageL, Vector2(120.0f * 0, 120.0f * 9), 120.0f, 20, 15, 13, Vector2::Zero, 0.07);

		if(mState == eArabianState::Move)
			mAnimator->Play(L"MoveL", true);
		else 
			mAnimator->Play(L"IdleL", true);

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 60.0f, 100.0f });
		mCollider->SetLeftTop(Vector2{ -30.50f, -100.0f });

		GameObject::Initialize();
	}

	void Arabian::Update()
	{

		if (GetState() == eState::Pause )
		{
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
		case mo::Arabian::eArabianState::Jump:
			jump();
			break;
		default:
			break;
		}
		
		RigidBody* mRigidbody = GetComponent<RigidBody>();
		if (mState == eArabianState::Move && mRigidbody->GetFall())
		{

			Transform* tr = GetComponent<Transform>();
			eDirection mDir = tr->GetDirection();

			if (mDir == eDirection::Left)
			{
				mAnimator->Play(L"JumpL", false);
			}
			else
			{
				mAnimator->Play(L"JumpR", false);
			}

			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 300.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			mState = eArabianState::Jump;
		}
		
		GameObject::Update();
	}

	void Arabian::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}

	void Arabian::OnCollisionEnter(Collider* other)
	{	
		Transform* tr = GetComponent<Transform>();
		eDirection mDir = tr->GetDirection();


		if (other->GetOwner()->GetLayerType() == eLayerType::PlayerPistol)
		{

			if (mDir == eDirection::Left)
			{
				mAnimator->Play(L"BulletDeathL", false);
			}
			else 
			{
				mAnimator->Play(L"BulletDeathR", false);
			}
			SetState(eState::Pause);
		}
		 if (other->GetOwner()->GetLayerType() == eLayerType::PlayerBomb)
		{
			if (mDir == eDirection::Left)
			{
				mAnimator->Play(L"KnifeDeathL", false);
			}
			else
			{
				mAnimator->Play(L"KnifeDeathR", false);
			}
			SetState(eState::Pause);
		}
		 if (other->GetOwner()->GetLayerType() == eLayerType::PlayerMachinegun)
		{

			if (mDir == eDirection::Left)
			{
				mAnimator->Play(L"BulletDeathL", false);
			}
			else
			{
				mAnimator->Play(L"BulletDeathR", false);
			}
			SetState(eState::Pause);
		}
	}

	void Arabian::OnCollisionStay(Collider* other)
	{
	}

	void Arabian::OnCollisionExit(Collider* other)
	{
	}

	void Arabian::SetArabianIdle()
	{
		mState = eArabianState::Idle;
		mAnimator->Play(L"Idle", true);
	}

	void Arabian::move()
	{
		Transform* tr = GetComponent<Transform>();
		eDirection mDir = tr->GetDirection();
		Vector2 mPos = tr->GetPos();
		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();



		if (mDir == eDirection::Left)
		{
			if (mPos.y < playerPos.y - 20.0f)
			{
				mPos.x -= 250.0f * Time::DeltaTime();
				tr->SetPos(mPos);
			}
			else
			{
				if (mPos.x <= playerPos.x)
				{
					mAnimator->Play(L"TurnL", false);
					mDir = eDirection::Right;
					tr->SetDirection(mDir);
					mState = eArabianState::Turn;
				}
				else if (mPos.x <= playerPos.x + 100.0f && mPos.x > playerPos.x)
				{
					mAnimator->Play(L"ReadyAttackL", false);
					readyToAttack = true;
					mState = eArabianState::Attack;
				}
				else if (mPos.x <= playerPos.x + 250.0f && mPos.x > playerPos.x + 100.0f)
				{
					mPos.x -= 250.0f * Time::DeltaTime();
					tr->SetPos(mPos);
				}
				else if (mPos.x <= playerPos.x + 300.0f && mPos.x > playerPos.x + 250.0f)
				{
					mAnimator->Play(L"ThrowingL", false);
					mState = eArabianState::Throwing;
				}
				else if (mPos.x > playerPos.x + 300.0f)
				{
					mPos.x -= 250.0f * Time::DeltaTime();
					tr->SetPos(mPos);
				}
			}
		}
		else if (mDir == eDirection::Right)
		{
			if (mPos.y < playerPos.y - 20.0f)
			{
				mPos.x += 250.0f * Time::DeltaTime();
				tr->SetPos(mPos);
			}
			else
			{
				if (mPos.x > playerPos.x)
				{
					mAnimator->Play(L"TurnR", false);
					mDir = eDirection::Left;
					tr->SetDirection(mDir);
					mState = eArabianState::Turn;
				}
				else if (mPos.x > playerPos.x - 100.0f && mPos.x <= playerPos.x)
				{
					mAnimator->Play(L"ReadyAttackR", false);
					readyToAttack = true;
					mState = eArabianState::Attack;
				}
				else if (mPos.x > playerPos.x - 250.0f && mPos.x <= playerPos.x - 100.0f)
				{
					mPos.x += 250.0f * Time::DeltaTime();
					tr->SetPos(mPos);
				}
				else if (mPos.x > playerPos.x - 300.0f && mPos.x <= playerPos.x - 250.0f)
				{
					mAnimator->Play(L"ThrowingR", false);
					mState = eArabianState::Throwing;
				}
				else if (mPos.x <= playerPos.x - 300.0f)
				{
					mPos.x += 250.0f * Time::DeltaTime();
					tr->SetPos(mPos);
				}
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

			if (readyToAttack)
			{
				readyToAttack = false;
				if (mDir == eDirection::Left)
				{
					mAnimator->Play(L"AttackL", false);
					EnemyAttackCollider* enemyKnife = new EnemyAttackCollider(mPos, Vector2(-100.0f, -100.0f), Vector2(10.0f, 80.0f), 0.5);
					curScene->AddGameObject(enemyKnife, eLayerType::EnemyBullet);
					enemyKnife->Initialize();
				}
				else
				{
					mAnimator->Play(L"AttackR", false);
					EnemyAttackCollider* enemyKnife = new EnemyAttackCollider(mPos, Vector2(0.0f, -100.0f), Vector2(100.0f, 80.0f), 0.5);
					curScene->AddGameObject(enemyKnife, eLayerType::EnemyBullet);
					enemyKnife->Initialize();
				}
			}
			else
			{
				if (mDir == eDirection::Left)
				{

					if (mPos.x <= playerPos.x)
					{
						mAnimator->Play(L"TurnL", false);
						mDir = eDirection::Right;
						tr->SetDirection(mDir);
						mState = eArabianState::Turn;
					}
					else if (mPos.x <= playerPos.x + 100.0f && mPos.x > playerPos.x)
					{
						mAnimator->Play(L"ReadyAttackL", false);
						readyToAttack = true;
					}
					else if (mPos.x <= playerPos.x + 250.0f && mPos.x > playerPos.x + 100.0f)
					{
						mAnimator->Play(L"MoveL", true);
						mState = eArabianState::Move;
					}
					else if (mPos.x <= playerPos.x + 300.0f && mPos.x > playerPos.x + 250.0f)
					{
						mAnimator->Play(L"ThrowingL", false);
						mState = eArabianState::Throwing;
					}
					else if (mPos.x > playerPos.x + 300.0f)
					{
						mAnimator->Play(L"MoveL", true);
						mState = eArabianState::Move;
					}
				}
				else if (mDir == eDirection::Right)
				{
					if (mPos.x > playerPos.x)
					{
						mAnimator->Play(L"TurnR", false);
						mDir = eDirection::Left;
						tr->SetDirection(mDir);
						mState = eArabianState::Turn;
					}
					else if (mPos.x > playerPos.x - 100.0f && mPos.x <= playerPos.x)
					{	
						mAnimator->Play(L"ReadyAttackR", false);
						readyToAttack = true;
					}
					else if (mPos.x > playerPos.x - 250.0f && mPos.x <= playerPos.x - 100.0f)
					{
						mAnimator->Play(L"MoveR", true);
						mState = eArabianState::Move;
					}
					else if (mPos.x > playerPos.x - 300.0f && mPos.x <= playerPos.x - 250.0f)
					{
						mAnimator->Play(L"ThrowingR", false);
						mState = eArabianState::Throwing;
					}
					else if (mPos.x <= playerPos.x - 300.0f)
					{
						mAnimator->Play(L"MoveR", true);
						mState = eArabianState::Move;
					}
				}
				if (player->GetState() == eState::Pause && !player->GetComponent<Animator>()->GetUseinvincibility())
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
		Vector2 cPos = Camera::CaluatePos(mPos);
		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();

		if (cPos.x <= 950.0f)
		{
			mAnimator->Play(L"MoveL", true);
			mState = eArabianState::Move;
		}


	}
	void Arabian::throwing()
	{
		Transform* tr = GetComponent<Transform>();
		eDirection mDir = tr->GetDirection();
		Vector2 mPos = tr->GetPos();
		//Vector2 playerPos = player->GetComponent<Transform>()->GetPos();

		time += Time::DeltaTime();
		if (player->GetState() == eState::Pause && !player->GetComponent<Animator>()->GetUseinvincibility())
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
				mAnimator->Play(L"MoveL", true);
				mState = eArabianState::Move;
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
				mAnimator->Play(L"MoveR", true);
				mState = eArabianState::Move;
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
				mAnimator->Play(L"MoveR", true);
				mState = eArabianState::Move;

			}
			else if (mDir == eDirection::Left)
			{
				mAnimator->Play(L"MoveL", true);
				mState = eArabianState::Move;
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

	void Arabian::jump()
	{
		Transform* tr = GetComponent<Transform>();
		eDirection mDir = tr->GetDirection();
		Vector2 mPos = tr->GetPos();
		RigidBody* mRigidbody = GetComponent<RigidBody>();

		if (mDir == eDirection::Left)
		{
			mPos.x -= 100.0f * Time::DeltaTime();
		
			if (mRigidbody->GetGround())
			{
				mAnimator->Play(L"MoveL", true);
				mState = eArabianState::Move;
			}
		}
		else
		{

			mPos.x += 100.0f * Time::DeltaTime();
			
			if (mRigidbody->GetGround())
			{
				mAnimator->Play(L"MoveR", true);
				mState = eArabianState::Move;
			}
		}

		tr->SetPos(mPos);
	}
	
}