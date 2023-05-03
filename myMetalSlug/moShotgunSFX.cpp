#include "moShotgunSFX.h"
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
#include "moArabian.h"
#include "moSceneManager.h"
#include "moObject.h"
#include "moAnimator.h"
#include "moSlave.h"
#include "moSound.h"

namespace mo {
	ShotgunSFX::ShotgunSFX()
	{
	}
	ShotgunSFX::~ShotgunSFX()
	{
	}
	void ShotgunSFX::Initialize()
	{
		shootgunSound = Resources::Load<Sound>(L"KnifeAttackSound", L"..\\Resources\\Sound\\KnifeAttackSound.wav");
		shootgunSound->SetVolume(80);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(3.0f, 3.0f));

		Image* mImage = Resources::Load<Image>(L"ShotgunSFX", L"..\\Resources\\Weapon\\ShotgunSFX.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"shoot", mImage, Vector2(200.0f * 0, 200.0f * 0), 200.0f, 12, 4, 12, Vector2::Zero, 0.1);
		
		mAnimator->Play(L"shoot", false);


		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 70.0f, 110.0f });

		SetBulletType(eBulletType::Bullet);

		GameObject::Initialize();
	}
	void ShotgunSFX::Update()
	{


		if (mAnimator->IsComplte())
			object::Destory(this);

		GameObject::Update();
	}
	void ShotgunSFX::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}
	void ShotgunSFX::OnCollisionEnter(Collider* other)
	{
	}
	void ShotgunSFX::OnCollisionStay(Collider* other)
	{
	}
	void ShotgunSFX::OnCollisionExit(Collider* other)
	{
	}
}