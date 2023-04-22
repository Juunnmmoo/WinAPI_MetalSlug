#include "moPlayerBomb.h"
#include "moResources.h"
#include "moImage.h"
#include "moApplication.h"
#include "moCamera.h"
#include "moTransform.h"
#include "moMarco.h"
#include "moRigidBody.h"
#include "moAnimator.h"
#include "moObject.h"
#include "moTime.h"
#include "Collider.h"
#include "moBulletSFX.h"

namespace mo {
	PlayerBomb::PlayerBomb()
	{
	}
	PlayerBomb::~PlayerBomb()
	{
	}
	void PlayerBomb::Initialize()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		tr->SetScale(Vector2{ 2.5f, 2.5f});
		tr->SetDisToBottom(Vector2{ 0.0f, 50.0f });

		RigidBody* mRigidbody = AddComponent<RigidBody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2(0.0f, 800.0f));



		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 30.0f, 40.0f });
		mCollider->SetLeftTop(Vector2{ 0.0f, -40.0f });

		Image* weaponSFX = Resources::Load<Image>(L"weaponSFX", L"..\\Resources\\Weapon\\WeaponSFX.bmp");

		SetBulletType(eBulletType::Bomb);


		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimation(L"MoveR", weaponSFX, Vector2(0.0f, 120.0f* 2), 120.0f, 30, 60, 30, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MoveL", weaponSFX, Vector2(120.0f * 29, 120.0f * 2), -120.0f, 30, 60, 30, Vector2::Zero, 0.05);

		SetBulletType(eBulletType::Bomb);

		GameObject::Initialize();

	}
	void PlayerBomb::Update()
	{
		switch (mState)
		{
		case eWeaponObjectState::First:
			first();
			break;
		case eWeaponObjectState::Second:
			second();
			break;
		case eWeaponObjectState::End:
			end();
			break;
		}
		GameObject::Update();
	}
	void PlayerBomb::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}
	void PlayerBomb::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::EnemyR || other->GetOwner()->GetLayerType() == eLayerType::EnemyR_F ||
			other->GetOwner()->GetLayerType() == eLayerType::Enemy || other->GetOwner()->GetLayerType() == eLayerType::Enemy_F)
		{
			Transform* tr;
			tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();

			Scene* curScene = SceneManager::GetActiveScene();
			BulletSFX* bulletSFX = new BulletSFX(eSfxType::PlayerBombSFX, pos, Vector2(5.0f, 5.0f), Vector2(0.0f, 49.0f));
			curScene->AddGameObject(bulletSFX, eLayerType::Effect);
			bulletSFX->Initialize();
			bulletSFX->PlayAnimation();

			object::Destory(this);
		}
	}
	void PlayerBomb::OnCollisionStay(Collider* other)
	{
	}
	void PlayerBomb::OnCollisionExit(Collider* other)
	{
	}
	void PlayerBomb::PlayAnimation(eDirection direction)
	{
		if(direction == eDirection::LTop ||
			direction == eDirection::Left || 
			direction == eDirection::LBottom || 
			direction == eDirection::LSit)
			mDir = eDirection::Left;
		else 
			mDir = eDirection::Right;

	}
	void PlayerBomb::first()
	{
		if (mDir == eDirection::Left)
		{
			mAnimator->Play(L"MoveL", true);
		}
		else
		{
			mAnimator->Play(L"MoveR", true);
		}
		RigidBody* mRigidbody = GetComponent<RigidBody>();
		Vector2 velocity = mRigidbody->GetVelocity();
		velocity.y -= 300.0f;
		mRigidbody->SetVelocity(velocity);
		mRigidbody->SetGround(false);

		mState = eWeaponObjectState::Second;
	}
	void PlayerBomb::second()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (mDir == eDirection::Left)
			pos.x -= 300.0f * Time::DeltaTime();
		else if (mDir == eDirection::Right)
			pos.x += 300.0f * Time::DeltaTime();

		tr->SetPos(pos);

		if (GetComponent<RigidBody>()->GetGround())
		{
			RigidBody* mRigidbody = GetComponent<RigidBody>();
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y -= 750.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			mState = eWeaponObjectState::End;
		}
	}
	void PlayerBomb::end()
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (mDir == eDirection::Left)
			pos.x -= 300.0f * Time::DeltaTime();
		else if (mDir == eDirection::Right)
			pos.x += 300.0f * Time::DeltaTime();

		tr->SetPos(pos);

		if (GetComponent<RigidBody>()->GetGround())
		{
			Scene* curScene = SceneManager::GetActiveScene();
			BulletSFX* bulletSFX = new BulletSFX(eSfxType::PlayerBombSFX, pos, Vector2(5.0f, 5.0f), Vector2(0.0f,49.0f));
			curScene->AddGameObject(bulletSFX, eLayerType::Effect);
			bulletSFX->Initialize();
			bulletSFX->PlayAnimation();

			object::Destory(this);
		}
	}
}