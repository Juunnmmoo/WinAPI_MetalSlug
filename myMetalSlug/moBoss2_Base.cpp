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
namespace mo {
	Boss2_Base::Boss2_Base(Marco* marco, Scene* scene, Boss2_Door* door, Boss2_Weapon* energy, Boss2_Propeller* propeller)
		: mDoor(door)
		, mPropeller(propeller)
		, mWeapon(energy)
		, mPlayer(marco)
		, curScene(scene)
	{
	}
	Boss2_Base::~Boss2_Base()
	{
	}
	void Boss2_Base::Initialize()
	{

		deathSound = Resources::Load<Sound>(L"Boss1DeathSound", L"..\\Resources\\Sound\\Boss1DeathSound.wav");
		deathSound->SetVolume(80);

		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(12512.0f, 350.0f));
		tr->SetScale(Vector2(3.5f, 3.5f));
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

		/*abul = new AbulAbbas(Vector2(5800.0f, 0.0f), mo::AbulAbbas::eAbulAbbasState::Idle);
		curScene->AddGameObject(abul, eLayerType::EnemyR_F);
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
			mDoor->GetAnimator()->Play(L"Open", false);
			mState = eBoss2FSM::DropArabian;
		}
	}
	void Boss2_Base::dropArabian()
	{
	
	}
	void Boss2_Base::dropArmy()
	{
	}
	void Boss2_Base::beforeAttack()
	{
	}
	void Boss2_Base::attack()
	{
	}
	void Boss2_Base::afterAttack()
	{
	}
	void Boss2_Base::death()
	{
	}
}