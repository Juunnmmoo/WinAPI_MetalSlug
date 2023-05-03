#include "moArmyRoket.h"
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
#include "moSound.h"
#include "moArmyRoketBullet.h"
namespace mo {
	ArmyRoket::ArmyRoket(Marco* p, Scene* scene, eDirection dir)
		: mDir(dir)
		, player(p)
		, curScene(scene)
		, mTime(0.0f)
	{
	}
	ArmyRoket::~ArmyRoket()
	{
	}
	void ArmyRoket::Initialize()
	{
		Image* mImage = Resources::Load<Image>(L"ArmyRoket", L"..\\Resources\\Enemy\\ArmyRoket.bmp");


		Transform* tr;
		tr = GetComponent<Transform>();
		//tr->SetPos(Vector2(1100.0f, 600.0f));
		tr->SetScale(Vector2{ 3.0f, 3.0f });
		//tr->SetDisToBottom(Vector2{ 0.0f, 40.0f });
		tr->SetDirection(mDir);

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"IdleL", mImage, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 20, 8, 6, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"MoveL", mImage, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 20, 8, 16, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"AttackL", mImage, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 20, 8, 6, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"TurnL", mImage, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 20, 8, 9, Vector2::Zero, 0.1);

		mAnimator->CreateAnimation(L"IdleR", mImage, Vector2(120.0f * 19, 120.0f * 4), -120.0f, 20, 8, 6, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"MoveR", mImage, Vector2(120.0f * 19, 120.0f * 5), -120.0f, 20, 8, 16, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"AttackR", mImage, Vector2(120.0f *	19, 120.0f * 6), -120.0f, 20, 8, 6, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"TurnR", mImage, Vector2(120.0f * 19, 120.0f * 7), -120.0f, 20, 8, 9, Vector2::Zero, 0.1);

		mAnimator->CreateAnimation(L"None", mImage, Vector2(120.0f * 10, 120.0f * 0), 120.0f, 20, 8, 1, Vector2::Zero, 0.1);

		
		mState = eArmyRoketFSM::None;

		GameObject::Initialize();
	}
	void ArmyRoket::Update()
	{

		switch (mState) {
		case mo::ArmyRoket::eArmyRoketFSM::None:
			none();
			break;
		case mo::ArmyRoket::eArmyRoketFSM::Idle:
			idle();
			break;
		case mo::ArmyRoket::eArmyRoketFSM::Move:
			move();
			break;
		case mo::ArmyRoket::eArmyRoketFSM::Attack:
			attack();
			break;
		case mo::ArmyRoket::eArmyRoketFSM::Turn:
			turn();
			break;
		}

		GameObject::Update();
	}
	void ArmyRoket::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void ArmyRoket::OnCollisionEnter(Collider* other)
	{
	}
	void ArmyRoket::OnCollisionStay(Collider* other)
	{
	}
	void ArmyRoket::OnCollisionExit(Collider* other)
	{
	}
	void ArmyRoket::ArmyAppear()
	{
		if (mDir == eDirection::Left)
		{
			mAnimator->Play(L"MoveL", true);
		}
		else
		{
			mAnimator->Play(L"MoveR", true);
		}
		mState = eArmyRoketFSM::Move;

	}
	void ArmyRoket::StopMove()
	{
		if (mDir == eDirection::Left)
		{
			mAnimator->Play(L"IdleL", true);
		}
		else
		{
			mAnimator->Play(L"IdleR", true);
		}
		mState = eArmyRoketFSM::Idle;
	}
	void ArmyRoket::none()
	{
	}
	void ArmyRoket::move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		eDirection dir = tr->GetDirection();

		if (dir == eDirection::Left)
		{
			pos.x -= 100.0f * Time::DeltaTime();
			tr->SetPos(pos);

		}
		else
		{
			pos.x += 100.0f * Time::DeltaTime();
			tr->SetPos(pos);

		}
		

	}
	void ArmyRoket::idle()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();
		eDirection dir = tr->GetDirection();

		mTime += Time::DeltaTime();

		if (mDir == eDirection::Left)
		{
			if (mTime >= 2.0f)
			{
				if (pos.x <= playerPos.x)
				{
					mAnimator->Play(L"AttackR", false);
					tr->SetDirection(eDirection::Right);
				}
				else 
				{
					mAnimator->Play(L"AttackL", false);
					tr->SetDirection(eDirection::Left);
				}
				mTime = 0.0f;
				mState = eArmyRoketFSM::Attack;
			}
		}
		else
		{
			if (mTime >= 3.0f)
			{
				if (pos.x <= playerPos.x)
				{
					mAnimator->Play(L"AttackR", false);
					tr->SetDirection(eDirection::Right);
				}
				else
				{
					mAnimator->Play(L"AttackL", false);
					tr->SetDirection(eDirection::Left);
				}
				mTime = 1.0f;
				mState = eArmyRoketFSM::Attack;
			}
		}
		
		
		
		if (mDir == eDirection::Left)
		{
			if (dir == eDirection::Left)
			{
				if (pos.x <= playerPos.x)
				{
					mAnimator->Play(L"IdleR", false);
					tr->SetDirection(eDirection::Right);
					mState = eArmyRoketFSM::Turn;
				}
			}
			else
			{
				if (pos.x > playerPos.x)
				{
					mAnimator->Play(L"IdleL", false);
					tr->SetDirection(eDirection::Left);
					mState = eArmyRoketFSM::Turn;
				}
			}
		}
		else
		{
			if (dir == eDirection::Left)
			{
				if (pos.x <= playerPos.x)
				{
					mAnimator->Play(L"IdleR", false);
					tr->SetDirection(eDirection::Right);
					mState = eArmyRoketFSM::Turn;
				}
			}
			else
			{
				if (pos.x > playerPos.x)
				{
					mAnimator->Play(L"IdleL", false);
					tr->SetDirection(eDirection::Left);
					mState = eArmyRoketFSM::Turn;
				}
			}
		}
		
	}
	void ArmyRoket::attack()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();
		eDirection dir = tr->GetDirection();

		Vector2 diff = playerPos - pos;
		
		if (!isShoot)
		{
			isShoot = true;
			ArmyRoketBullet* bullet = new ArmyRoketBullet();
			curScene->AddGameObject(bullet, eLayerType::EnemyBullet);
			bullet->GetComponent<Transform>()->SetPos(pos);
			bullet->Initialize();
			bullet->SetDir(diff);

		}

		if (mAnimator->IsComplte())
		{
			if (dir == eDirection::Left)
			{
				mAnimator->Play(L"IdleL", true);
			}
			else
			{
				mAnimator->Play(L"IdleR", true);
			}
			isShoot = false;
			mState = eArmyRoketFSM::Idle;
		}

	}
	void ArmyRoket::turn()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();
		eDirection dir = tr->GetDirection();

		if (mAnimator->IsComplte())
		{
			if (dir == eDirection::Left)
			{
				mAnimator->Play(L"IdleL", true);
			}
			else
			{
				mAnimator->Play(L"IdleR", true);
			}
			mState = eArmyRoketFSM::Idle;
		}
	}
	void ArmyRoket::death()
	{
	}
}