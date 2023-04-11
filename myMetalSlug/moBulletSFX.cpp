#include "moBulletSFX.h"
#include "moAnimator.h"
#include "momoEngine.h"
#include "moObject.h"
#include "moTransform.h"
#include "moResources.h"
#include "moImage.h"

namespace mo {
	BulletSFX::BulletSFX(eLayerType layer, Vector2 pos)
		: mLayerType(layer)
		, mPos(pos)
	{
	}

	BulletSFX::~BulletSFX()
	{
	}
	void BulletSFX::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(mPos);
		tr->SetDisToBottom(Vector2(0.0f, 49.0f));
		tr->SetScale(Vector2(2.0f, 2.0f));

		Image* weaponSFX = Resources::Load<Image>(L"weaponSFX", L"..\\Resources\\Weapon\\WeaponSFX.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"BulletSFX", weaponSFX, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 30, 30, 11, Vector2::Zero, 0.05);

		mAnimator->GetCompleteEvent(L"BulletSFX") = std::bind(&BulletSFX::destroySFX, this);

		GameObject::Initialize();
	}
	void BulletSFX::Update()
	{
		GameObject::Update();
	}
	void BulletSFX::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void BulletSFX::PlayAnimation()
	{
		//if(mLayerType == eLayerType::PlayerPistol)
			mAnimator->Play(L"BulletSFX", false);
	}
	void BulletSFX::destroySFX()
	{
		object::Destory(this);
	}
}