#include "moMarco.h"
#include "moImage.h"
#include "moSceneManager.h"
#include "moResources.h"
#include "moTransform.h"
#include "moInput.h"
#include "moTime.h"
#include "moAnimator.h"
#include "Collider.h"
#include "moScene.h"
#include "moCamera.h"
#include "moRigidBody.h"
#include "moApplication.h"
#include "moWeapon.h"
#include "moPistol.h"
#include "moMachinegun.h"
#include "moDropWeapon.h"
#include "moObject.h"
#include "moPlayerKnife.h"

extern mo::Application application;

namespace mo {
	Marco::Marco(MarcoBottom* obj, PlayerKnife* right, PlayerKnife* left)
		: isKnife(false)
		, mAnimator(nullptr)
		, mState(eMarcoState::Paraglider)
		, bottom(obj)
		, pistol(nullptr)
		, mWeaponState(eMarcoWeapon::Pistol)
		, bulletNum(-1)
		, rightKnife(right)
		, leftKnife(left)
		, bombNum(10)
	{
	}
	Marco::~Marco()
	{
		delete pistol;
		delete machinegun;
		pistol = nullptr;
		machinegun = nullptr;
	}
	void Marco::Initialize()
	{
		/*Image* mImageR = Resources::Load<Image>(L"PistolRight", L"..\\Resources\\Player\\PistolRight.bmp");
		Image* mImageL = Resources::Load<Image>(L"PistolLeft", L"..\\Resources\\Player\\PistolLeft.bmp");
		Image* test = Resources::Load<Image>(L"RipleRight", L"..\\Resources\\Player\\RipleRight.bmp");*/

		mAnimator = AddComponent<Animator>();
		mAnimator->SetAlpha(true);

		Transform* tr;
		tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 300.0f, 000.0f });
		//tr->SetPos(Vector2{ 4500.0f, 100.0f });

		tr->SetScale(Vector2{ 3.0f, 3.0f });
		tr->SetDisToBottom(Vector2{ 0.0f, 50.0f });


		Transform* bottomTr;
		bottomTr = bottom->GetComponent<Transform>();
		bottomTr->SetPos(tr->GetPos() + Vector2(0.0f, 40.0f));
		bottomTr->SetScale(Vector2{ 3.0f, 3.0f });
		bottomTr->SetDisToBottom(Vector2{ 0.0f, 50.0f });

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 60.0f, 110.0f });
		mCollider->SetLeftTop(Vector2{ -30.50f, -70.0f });

		mRigidbody = AddComponent<RigidBody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2(0.0f, 250.0f));


	

		pistol = new Pistol(this, bottom);
		pistol->Initialize();

		machinegun = new Machinegun(this, bottom);
		machinegun->Initialize();
		


		GameObject::Initialize();
	}
	void Marco::Update()
	{
		Collider* mCollider = GetComponent<Collider>();
		
		Transform* tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();
		Vector2 pos = tr->GetPos();
		
		Transform* bottomTr;
		bottomTr = bottom->GetComponent<Transform>();
		bottomTr->SetPos(tr->GetPos() + Vector2(0.0f, 40.0f));

		if (mState == eMarcoState::Sit)
		{
			mCollider->SetSize(Vector2{ 60.0f, 75.0f });
			mCollider->SetLeftTop(Vector2{ -30.50f, -35.0f });
		}
		else 
		{
			mCollider->SetSize(Vector2{ 60.0f, 110.0f });
			mCollider->SetLeftTop(Vector2{ -30.50f, -70.0f });
		}

		switch (mWeaponState) {
			case eMarcoWeapon::Pistol:
				pistol->Update();
				break;
			case eMarcoWeapon::Machinegun:
				machinegun->Update();
				break;
		}



		if (bulletNum == 0)
		{
		

			DropWeapon* drop = new DropWeapon();
			Scene* curScene = SceneManager::GetActiveScene();
			curScene->AddGameObject(drop, eLayerType::DropWeapon);

			drop->Initialize();
			drop->GetComponent<Transform>()->SetPos(tr->GetPos() );
			drop->PlayAnimation(mDirection);

			mWeaponState = eMarcoWeapon::Pistol;
			bottom->SetWeaponState(eMarcoWeapon::Pistol);

			if (mState == eMarcoState::Idle)
			{
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_IdleL", true);
				else if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_IdleR", true);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"P_IdleRT", true);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"P_IdleLT", true);
			}
			else if (mState == eMarcoState::Sit)
			{
				bottom->PlaySitAnimation();
				mAnimator->Play(L"None", true);
			}
			else if (mState == eMarcoState::Jump)
			{
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_IdleL", true);
				else if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_IdleR", true);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"P_IdleRT", true);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"P_IdleLT", true);
				else if (mDirection == eDirection::RBottom)
					mAnimator->Play(L"P_JumpDownR", true);
				else if (mDirection == eDirection::LBottom)
					mAnimator->Play(L"P_JumpDownL", true);
				
			}
			else 
			{
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_MoveL", true);
				else if (mDirection == eDirection::Right)
					mAnimator->Play(L"P_MoveR", true);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"P_IdleLT", true);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"P_IdleRT", true);
			}		
			bulletNum = -1;
		}

		rightKnife->SetPos(pos + Vector2(20.0f, -70.0f));
		leftKnife->SetPos(pos + Vector2(-90.0f, -70.0f));
		
		if (mDirection == eDirection::Right ||
			mDirection == eDirection::RTop ||
			mDirection == eDirection::RSit ||
			mDirection == eDirection::RBottom)
		{
			if (rightKnife->GetIsCollide())
			{
				isKnife = true;
				bottom->SetIsKnife(true);
				rightKnife->SetIsUse(true);
			}
			else
			{
				isKnife = false;
				bottom->SetIsKnife(false);
				rightKnife->SetIsUse(false);
			}
		}
		else if (mDirection == eDirection::Left ||
			     mDirection == eDirection::LTop ||
			     mDirection == eDirection::LSit || 
				 mDirection == eDirection::LBottom)
		{
			if (leftKnife->GetIsCollide())
			{
				isKnife = true;
				bottom->SetIsKnife(true);
				leftKnife->SetIsUse(true);
			}
			else
			{
				isKnife = false;
				bottom->SetIsKnife(false);
				leftKnife->SetIsUse(false);
			}
		}
		GameObject::Update();

	}
	void Marco::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}



	void Marco::OnCollisionEnter(Collider* other)
	{
		/*if ( other->GetOwner()->GetLayerType() == eLayerType::Monster)
			isKnife = true;*/

		if ((other->GetOwner()->GetLayerType() == eLayerType::EnemyBulletR || 
			other->GetOwner()->GetLayerType() == eLayerType::EnemyBullet))
		{
			if (other->GetOwner()->GetBulletType() == eBulletType::knife
				)
			{
				SetState(eState::Pause);
				Transform* tr = GetComponent<Transform>();
				eDirection mDirection = tr->GetDirection();

				if (mDirection == eDirection::Left ||
					mDirection == eDirection::LSit ||
					mDirection == eDirection::LBottom ||
					mDirection == eDirection::LTop)
				{
					mAnimator->Play(L"None", false);
					bottom->GetAnimator()->Play(L"KnifeDeathL", false);
				}
				else
				{
					mAnimator->Play(L"None", false);
					bottom->GetAnimator()->Play(L"KnifeDeathR", false);
				}
				mWeaponState = eMarcoWeapon::Pistol;
				bottom->SetWeaponState(eMarcoWeapon::Pistol);
				mState = eMarcoState::Death;
				bottom->SetBottomState(MarcoBottom::eMarcoState::Death);

			}

			else if (other->GetOwner()->GetBulletType() == eBulletType::Bullet
				)
			{
				SetState(eState::Pause);
				Transform* tr = GetComponent<Transform>();
				eDirection mDirection = tr->GetDirection();

				if (mDirection == eDirection::Left ||
					mDirection == eDirection::LSit ||
					mDirection == eDirection::LBottom ||
					mDirection == eDirection::LTop)
				{
					mAnimator->Play(L"None", false);
					bottom->GetAnimator()->Play(L"KnifeDeathL", false);
				}
				else
				{
					mAnimator->Play(L"None", false);
					bottom->GetAnimator()->Play(L"KnifeDeathR", false);
				}
				mWeaponState = eMarcoWeapon::Pistol;
				bottom->SetWeaponState(eMarcoWeapon::Pistol);
				mState = eMarcoState::Death;
				bottom->SetBottomState(MarcoBottom::eMarcoState::Death);

			}
			
		}
	}

	void Marco::OnCollisionStay(Collider* other)
	{
	}

	void Marco::OnCollisionExit(Collider* other)
	{
		/*if (other->GetOwner()->GetLayerType() == eLayerType::Monster)
			isKnife = false;*/
	}

	void Marco::ChangeWeapon(eMarcoWeapon state)
	{
		Transform* tr;
		tr = GetComponent<Transform>();
		eDirection mDirection = tr->GetDirection();

		mWeaponState = state;
		bottom->SetWeaponState(state);

		if (mState == eMarcoState::Sit) 
		{
			bottom->PlaySitAnimation();
			mAnimator->Play(L"None", true);
		}
		else if (mState == eMarcoState::Jump)
		{
			if (state == eMarcoWeapon::Pistol) {
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_IdleL", true);
				else if(mDirection == eDirection::Right)
					mAnimator->Play(L"P_IdleR", true);
				else if(mDirection == eDirection::RTop)
					mAnimator->Play(L"P_IdleRT", true);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"P_IdleLT", true);
				else if (mDirection == eDirection::RBottom)
					mAnimator->Play(L"P_JumpDownR", true);
				else if (mDirection == eDirection::LBottom)
					mAnimator->Play(L"P_JumpDownL", true);
			}
			else if (state == eMarcoWeapon::Machinegun) {
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"M_IdleL", true);
				else if (mDirection == eDirection::Right)
					mAnimator->Play(L"M_IdleR", true);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"M_IdleRT", true);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"M_IdleLT", true);
				else if (mDirection == eDirection::RBottom)
					mAnimator->Play(L"M_JumpDownR", true);
				else if (mDirection == eDirection::LBottom)
					mAnimator->Play(L"M_JumpDownL", true);
			}
			else if (state == eMarcoWeapon::Shotgun) {
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"S_IdleL", true);
				else if (mDirection == eDirection::Right)
					mAnimator->Play(L"S_IdleR", true);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"S_IdleRT", true);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"S_IdleLT", true);
				else if (mDirection == eDirection::RBottom)
					mAnimator->Play(L"S_JumpDownR", true);
				else if (mDirection == eDirection::LBottom)
					mAnimator->Play(L"S_JumpDownL", true);
			}
			else {
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"F_IdleL", true);
				else if (mDirection == eDirection::Right)
					mAnimator->Play(L"F_IdleR", true);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"F_IdleRT", true);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"F_IdleLT", true);
				else if (mDirection == eDirection::RBottom)
					mAnimator->Play(L"F_JumpDownR", true);
				else if (mDirection == eDirection::LBottom)
					mAnimator->Play(L"F_JumpDownL", true);
			}
		}
		else if (mState == eMarcoState::Move)
		{
			if (state == eMarcoWeapon::Pistol) {
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"P_MoveL", true);
				else if(mDirection == eDirection::Right)
					mAnimator->Play(L"P_MoveR", true);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"P_IdleLT", true);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"P_IdleRT", true);

			}
			else if (state == eMarcoWeapon::Machinegun) {
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"M_MoveL", true);
				else if (mDirection == eDirection::Right)
					mAnimator->Play(L"M_MoveR", true);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"M_IdleLT", true);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"M_IdleRT", true);
			}
			else if (state == eMarcoWeapon::Shotgun) {
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"S_MoveL", true);
				else if(mDirection == eDirection::Right)
					mAnimator->Play(L"S_MoveR", true);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"S_IdleLT", true);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"S_IdleRT", true);
			}
			else {
				if (mDirection == eDirection::Left)
					mAnimator->Play(L"F_MoveL", true);
				else if (mDirection == eDirection::Right)
					mAnimator->Play(L"F_MoveR", true);
				else if (mDirection == eDirection::LTop)
					mAnimator->Play(L"F_IdleLT", true);
				else if (mDirection == eDirection::RTop)
					mAnimator->Play(L"F_IdleRT", true);
			}
			mState = eMarcoState::Move;
		}
		
	}

}