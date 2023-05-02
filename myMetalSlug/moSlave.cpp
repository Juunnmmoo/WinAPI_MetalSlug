#include "moSlave.h"
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
#include "moMachinegunBox.h"
#include "moBombBox.h"
#include "moSound.h"

namespace mo {
	Slave::Slave(Marco* p, Scene* scene, Vector2 pos, eMarcoWeapon weapon)
		: player(p)
		, curScene(scene)
		, mPos(pos)
		, weaponType(weapon)
	{
	}
	Slave::~Slave()
	{
	}
	void Slave::Initialize()
	{
		thankyouSound = Resources::Load<Sound>(L"thankyouSound", L"..\\Resources\\Sound\\thankyouSound.wav");

		Image* mImageL = Resources::Load<Image>(L"NpcLeft", L"..\\Resources\\NPC\\NpcLeft.bmp");
		Image* mImageR = Resources::Load<Image>(L"NpcRight", L"..\\Resources\\NPC\\NpcRight.bmp");

		Transform* tr;
		tr = GetComponent<Transform>();
		tr->SetPos(mPos);
		tr->SetScale(Vector2{ 3.0f, 3.0f });
		tr->SetDisToBottom(Vector2{ 0.0f, 60.0f });
		tr->SetDirection(eDirection::Left);

		RigidBody* mRigidbody = AddComponent<RigidBody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2(0.0f, 600.0f));

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"IdleL", mImageL, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 20, 40, 5, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"BeReleasedL", mImageL, Vector2(120.0f * 5, 120.0f * 0), 120.0f, 20, 40, 4, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"MoveL", mImageL, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 20, 40, 12, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"MoveR", mImageR, Vector2(120.0f * 19, 120.0f * 1), -120.0f, 20, 40, 12, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"TakeOutL", mImageL, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 20, 40, 11, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"SirL", mImageL, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 20, 40, 14, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"RunL", mImageL, Vector2(120.0f * 0, 120.0f * 4), 120.0f, 20, 40, 8, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"DownL", mImageL, Vector2(120.0f * 0, 120.0f * 5), 120.0f, 20, 40, 14, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"FlyingL", mImageL, Vector2(120.0f * 0, 120.0f * 6), 120.0f, 20, 40, 5, Vector2::Zero, 0.05);


		mAnimator->Play(L"IdleL", true);
		mState = eSlaveState::Idle;

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 60.0f, 100.0f });
		mCollider->SetLeftTop(Vector2{ -30.50f, -100.0f });

		GameObject::Initialize();
	}
	void Slave::Update()
	{
	
		switch (mState) {
		case mo::Slave::eSlaveState::Idle:
			idle();
			break;
		case mo::Slave::eSlaveState::BeReleased:
			beReleased();
			break;
		case mo::Slave::eSlaveState::MoveL:
			moveL();
			break;
		case mo::Slave::eSlaveState::MoveR:
			moveR();
			break;
		case mo::Slave::eSlaveState::Flying:
			flying();
			break;
		case mo::Slave::eSlaveState::BeforeTakeOut:
			beforeTakeOut();
			break;
		case mo::Slave::eSlaveState::TakeOut:
			takeOut();
			break;
		case mo::Slave::eSlaveState::Sir:
			sir();
			break;
		case mo::Slave::eSlaveState::Run:
			run();
			break;
		case mo::Slave::eSlaveState::Indicate:
			indicate();
			break;
		default:
			break;
		}


		RigidBody* mRigidbody = GetComponent<RigidBody>();

		if (mState == eSlaveState::MoveL ||
			mState == eSlaveState::MoveR)
		{
			if (mRigidbody->GetFall())
			{
				time = 0.0f;
				mAnimator->Play(L"FlyingL", true);
				mState = eSlaveState::Flying;
			}
		}

		GameObject::Update();

	}
	void Slave::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void Slave::IndicateRight()
	{
		mAnimator->Play(L"MoveR", true);
		isReleased = true;
		mState = eSlaveState::Indicate;

	}
	void Slave::OnCollisionEnter(Collider* other)
	{
		if ((other->GetOwner()->GetLayerType() == eLayerType::PlayerPistol ||
			other->GetOwner()->GetLayerType() == eLayerType::PlayerMachinegun ||
			other->GetOwner()->GetLayerType() == eLayerType::PlayerShotgun ||
			other->GetOwner()->GetLayerType() == eLayerType::PlayerShotgun) &&
			!isReleased
			)
		{

			isReleased = true;
			mAnimator->Play(L"BeReleasedL", false);
			mState = eSlaveState::BeReleased;
		}

		if ((mState == eSlaveState::MoveL || mState == eSlaveState::MoveR ||mState == eSlaveState::Indicate) &&
			other->GetOwner()->GetLayerType() == eLayerType::Player &&
			!isTakeOut &&
			isReleased)
		{
			thankyouSound->Play(false);

			isTakeOut = true;
			time = 0.0f;

			playerPos.x = other->GetOwner()->GetComponent<Transform>()->GetPos().x;
			
			Transform* tr;
			tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();

			if (pos.x <= playerPos.x + 100.0f)
			{
				mAnimator->Play(L"MoveR", true);
			}
			else if (pos.x > playerPos.x + 130.0f)
			{
				mAnimator->Play(L"MoveL", true);
			}
			mState = eSlaveState::BeforeTakeOut;
		}
	
	}
	void Slave::OnCollisionStay(Collider* other)
	{
	}
	void Slave::OnCollisionExit(Collider* other)
	{
	}
	void Slave::idle()
	{
	}
	void Slave::beReleased()
	{
		if (mAnimator->IsComplte())
		{
			mAnimator->Play(L"MoveL", true);
			mState = eSlaveState::MoveL;
		}
	}	
	void Slave::moveL()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		time += Time::DeltaTime();
		pos.x -= 230.0f * Time::DeltaTime();
		tr->SetPos(pos);

		if (time >= 1.0f)
		{
			time = 0.0f;
			mAnimator->Play(L"MoveR", true);
			mState = eSlaveState::MoveR;
		}
	}
	void Slave::moveR()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		time += Time::DeltaTime();
		pos.x += 230.0f * Time::DeltaTime();
		tr->SetPos(pos);

		if (time >= 1.0f)
		{
			time = 0.0f;
			mAnimator->Play(L"MoveL", true);
			mState = eSlaveState::MoveL;
		}

	}
	void Slave::flying()
	{
		RigidBody* mRigidbody = GetComponent<RigidBody>();

		if (mRigidbody->GetGround())
		{
			mAnimator->Play(L"MoveL", true);
			mState = eSlaveState::MoveL;
		}
	}
	void Slave::beforeTakeOut()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (pos.x <= playerPos.x + 100.0f)
		{
			pos.x += 400.0f * Time::DeltaTime();
			tr->SetPos(pos);
		}
		else if (pos.x > playerPos.x + 130.0f)
		{
			pos.x -= 400.0f * Time::DeltaTime();
			tr->SetPos(pos);
		}
		else if (pos.x > playerPos.x + 100.0f && pos.x <= playerPos.x + 130.0f)
		{
			mAnimator->Play(L"TakeOutL", false);
			mState = eSlaveState::TakeOut;
		}
	}
	void Slave::takeOut()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (mAnimator->IsComplte() && !isDrop)
		{
			isDrop = true;

			if (weaponType == eMarcoWeapon::Machinegun)
			{
				MachinegunBox* M_Box = new MachinegunBox();
				curScene->AddGameObject(M_Box, eLayerType::BulletBox);
				M_Box->GetComponent<Transform>()->SetPos(pos + Vector2(-60.0f, -50.0f));
				M_Box->Initialize();	
			}
			else if (weaponType == eMarcoWeapon::Bomb)
			{
				BombBox* bomb_Box = new BombBox();
				curScene->AddGameObject(bomb_Box, eLayerType::BulletBox);
				bomb_Box->GetComponent<Transform>()->SetPos(pos + Vector2(-60.0f, -50.0f));
				bomb_Box->Initialize();
			}
		}
		if (isDrop)
		{
			time += Time::DeltaTime();

		}
		if (time >= 1.5f)
		{
			mAnimator->Play(L"SirL", false);
			mState = eSlaveState::Sir;
		}

	}
	void Slave::sir()
	{
		if (mAnimator->IsComplte())
		{
			mAnimator->Play(L"RunL", true);
			mState = eSlaveState::Run;
		}
	}

	void Slave::run()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x -= 400.0f * Time::DeltaTime();

		tr->SetPos(pos);

		if (Camera::CaluatePos(pos).x <= -100.0f)
			object::Destory(this);
		
	}
	void Slave::indicate()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		time += Time::DeltaTime();
		pos.x += 230.0f * Time::DeltaTime();
		tr->SetPos(pos);
	}
}