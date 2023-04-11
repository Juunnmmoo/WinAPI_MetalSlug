#include "moBulletSFX.h"
#include "moAnimator.h"
#include "momoEngine.h"
#include "moObject.h"
#include "moTransform.h"
#include "moResources.h"
#include "moImage.h"

namespace mo {
	BulletSFX::BulletSFX(eLayerType layer, Vector2 pos, Vector2 scale, Vector2 topdiff)
		: mLayerType(layer)
		, mPos(pos)
		, mScale(scale)
		, mTopdiff(topdiff)
	{
	}

	BulletSFX::~BulletSFX()
	{
	}
	void BulletSFX::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(mPos);
		tr->SetDisToBottom(mTopdiff);
		tr->SetScale(mScale);

		Image* weaponSFX = Resources::Load<Image>(L"weaponSFX", L"..\\Resources\\Weapon\\WeaponSFX.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"PlayerPistolBulletSFX", weaponSFX, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 30, 60, 11, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"PlayerBombBulletSFX", weaponSFX, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 30, 60, 24, Vector2::Zero, 0.05);

		mAnimator->GetCompleteEvent(L"PlayerPistolBulletSFX") = std::bind(&BulletSFX::destroySFX, this);
		mAnimator->GetCompleteEvent(L"PlayerBombBulletSFX") = std::bind(&BulletSFX::destroySFX, this);

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
		if(mLayerType == eLayerType::PlayerPistol)
			mAnimator->Play(L"PlayerPistolBulletSFX", false);
		else if (mLayerType == eLayerType::PlayerBomb)
			mAnimator->Play(L"PlayerBombBulletSFX", false);

		
	}
	void BulletSFX::destroySFX()
	{
		object::Destory(this);
	}
}