#include "moAbulAbbas.h"
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

namespace mo {
	AbulAbbas::AbulAbbas(Vector2 stop, eAbulAbbasState state)
		:stopPos(stop)
		, mState(state)
	{
	}
	AbulAbbas::~AbulAbbas()
	{
	}
	void AbulAbbas::Initialize()
	{
		Image* mImageL = Resources::Load<Image>(L"AbulAbbas", L"..\\Resources\\NPC\\AbulAbbas.bmp");


		Transform* tr;	
		tr = GetComponent<Transform>();
		tr->SetScale(Vector2{ 3.0f, 3.0f });
		tr->SetDirection(eDirection::Left);

		RigidBody* mRigidbody = AddComponent<RigidBody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2(0.0f, 600.0f));

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"IdleL", mImageL, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 11, 6, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"AttackSign", mImageL, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 11, 6, 9, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"MoveR", mImageL, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 11, 6, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"MoveL", mImageL, Vector2(120.0f * 5, 120.0f * 3), -120.0f, 11, 6, 4, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"BeforeGiveUp", mImageL, Vector2(120.0f * 0, 120.0f * 4), 120.0f, 11, 6, 6, Vector2::Zero, 0.07);
		mAnimator->CreateAnimation(L"GiveUp", mImageL, Vector2(120.0f * 0, 120.0f * 5), 120.0f, 11, 6, 11, Vector2::Zero, 0.07);

		if(mState ==eAbulAbbasState::Idle)
			mAnimator->Play(L"IdleL", true);
		else if (mState == eAbulAbbasState::MoveFoword)
			mAnimator->Play(L"MoveL", true);

		GameObject::Initialize();
	}
	void AbulAbbas::Update()
	{
		switch (mState) {
		case mo::AbulAbbas::eAbulAbbasState::Idle:
			idle();
			break;
		case mo::AbulAbbas::eAbulAbbasState::MoveFoword:
			moveFoword();
			break;
		case mo::AbulAbbas::eAbulAbbasState::AttackSign:
			attackSign();
			break;
		case mo::AbulAbbas::eAbulAbbasState::Run:
			run();
			break;
		case mo::AbulAbbas::eAbulAbbasState::BeforeGiveUp:
			beforeGiveUp();
			break;
		case mo::AbulAbbas::eAbulAbbasState::GiveUp:
			giveUp();
			break;
		case mo::AbulAbbas::eAbulAbbasState::None:
			break;
		default:
			break;
		}
		GameObject::Update();
	}
	void AbulAbbas::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void AbulAbbas::OnCollisionEnter(Collider* other)
	{
	}
	void AbulAbbas::OnCollisionStay(Collider* other)
	{
	}
	void AbulAbbas::OnCollisionExit(Collider* other)
	{
	}
	void AbulAbbas::idle()
	{
		if (startAttack)
		{
			mAnimator->Play(L"AttackSign", true);
			mState = eAbulAbbasState::AttackSign;
		}
	}
	void AbulAbbas::moveFoword()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		pos.x -= 100.0f * Time::DeltaTime();
		tr->SetPos(pos);

		if (pos.x < stopPos.x)
		{
			mAnimator->Play(L"AttackSign", true);
			mState = eAbulAbbasState::AttackSign;
		}
	}
	void AbulAbbas::attackSign()
	{
		if (startRun)
		{
			mAnimator->Play(L"MoveR", true);
			mState = eAbulAbbasState::Run;
		}
		if (startGiveUp)
		{
			mAnimator->Play(L"BeforeGiveUp", false);
			mState = eAbulAbbasState::BeforeGiveUp;
		}
	}
	void AbulAbbas::run()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 cPos = Camera::CaluatePos(pos);

		pos.x += 300.0f * Time::DeltaTime();
		tr->SetPos(pos);

		if (cPos.x > 1200.0f)
			object::Destory(this);

	}
	void AbulAbbas::beforeGiveUp()
	{
		if (mAnimator->IsComplte())
		{
			mAnimator->Play(L"GiveUp", true);
			mState = eAbulAbbasState::GiveUp;
		}
	}
	void AbulAbbas::giveUp()
	{
	}
}