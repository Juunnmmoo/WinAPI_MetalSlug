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

		
		Transform* tr;
		tr = GetComponent<Transform>();
		tr->SetPos(Vector2(1100.0f, 600.0f));
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
		mAnimator->CreateAnimation(L"TurnL", mImageL, Vector2(120.0f * 0, 120.0f * 5), 120.0f, 20, 15, 2, Vector2::Zero, 0.5);

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
		case mo::Arabian::eArabianState::Throwing:
			throwing();
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
		

		if (other->GetOwner()->GetLayerType() == eLayerType::PlayerPistol) {
			SetState(eState::Pause);
		}
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

		if (playerPos.x < mPos.x)
		{
			mPos.x -= 200.0f * Time::DeltaTime();
			tr->SetPos(mPos);
		}

		if (playerPos.x + 300.0f > mPos.x)
		{
			mAnimator->Play(L"ThrowingL", false);
			mState = eArabianState::Throwing;
		}
	}

	void Arabian::attack()
	{
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

		if (playerPos.x + 300.0f < mPos.x)
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
		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();

		time += Time::DeltaTime();

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
	
}