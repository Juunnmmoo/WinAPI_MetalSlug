#include "moMarco.h"
#include "moImage.h"
#include "moSceneManager.h"
#include "moResources.h"
#include "moTransform.h"
#include "moInput.h"
#include "moTime.h"
#include "moAnimator.h"
#include "Collider.h"
#include "moBaseBullet.h"
#include "moScene.h"
#include "moCamera.h"
#include "moRigidBody.h"
#include "moApplication.h"
#include "moWeapon.h"
#include "moPistol.h"
#include "moMachinegun.h"

extern mo::Application application;

namespace mo {
	Marco::Marco(MarcoBottom* obj)
		: isKnife(false)
		, mAnimator(nullptr)
		, mState(eMarcoState::Paraglider)
		, bottom(obj)
		, pistol(nullptr)
		, mWeaponState(eMarcoWeapon::Pistol)
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
		tr->SetPos(Vector2{ 300.0f, 200.0f });
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

		switch (mWeaponState) {
			case mo::Marco::eMarcoWeapon::Pistol:
				//pistol->Update();
				machinegun->Update();
				break;
			case mo::Marco::eMarcoWeapon::Machinegun:
				machinegun->Update();
				break;
		}
		

		// PlayerBottom À§Ä¡ update
		Transform* tr;
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Transform* bottomTr;
		bottomTr = bottom->GetComponent<Transform>();
		bottomTr->SetPos(tr->GetPos() + Vector2(0.0f, 40.0f));
		
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

		if (other->GetOwner()->GetLayerType() == eLayerType::Monster) {
			mAnimator->SetUseinvincibility(true);
			bottom->GetAnimator()->SetUseinvincibility(true);
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

}