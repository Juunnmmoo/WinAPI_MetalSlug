#include "moBulletSFX.h"
#include "moAnimator.h"
#include "momoEngine.h"
#include "moObject.h"
#include "moTransform.h"
#include "moResources.h"
#include "moImage.h"

namespace mo {
	BulletSFX::BulletSFX(eSfxType type, Vector2 pos, Vector2 scale, Vector2 topdiff)
		: mSfxType(type)
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
		mAnimator->CreateAnimation(L"PlayerPistolBulletGroundSFX", weaponSFX, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 30, 60, 11, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"PlayerBombBulletSFX", weaponSFX, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 30, 60, 24, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"PlayerPistolBulletEnemySFX", weaponSFX, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 30, 60, 4, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"NomalExplosionM", weaponSFX, Vector2(120.0f * 0, 120.0f * 4), 120.0f, 30, 60, 26, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"Boss1SFX", weaponSFX, Vector2(120.0f * 0, 120.0f * 5), 120.0f, 30, 60, 30, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"Boss2SFX", weaponSFX, Vector2(120.0f * 0, 120.0f * 6), 120.0f, 30, 60, 23, Vector2::Zero, 0.05);


		mAnimator->GetCompleteEvent(L"PlayerPistolBulletGroundSFX") = std::bind(&BulletSFX::destroySFX, this);
		mAnimator->GetCompleteEvent(L"PlayerBombBulletSFX") = std::bind(&BulletSFX::destroySFX, this);
		mAnimator->GetCompleteEvent(L"PlayerPistolBulletEnemySFX") = std::bind(&BulletSFX::destroySFX, this);
		mAnimator->GetCompleteEvent(L"NomalExplosionM") = std::bind(&BulletSFX::destroySFX, this);
		mAnimator->GetCompleteEvent(L"Boss1SFX") = std::bind(&BulletSFX::destroySFX, this);
		mAnimator->GetCompleteEvent(L"Boss2SFX") = std::bind(&BulletSFX::destroySFX, this);


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
		if(mSfxType == eSfxType::PlayerBulletGroundSFX)
			mAnimator->Play(L"PlayerPistolBulletGroundSFX", false);
		else if (mSfxType == eSfxType::PlayerBombSFX)
			mAnimator->Play(L"PlayerBombBulletSFX", false);
		else if (mSfxType == eSfxType::PlayerBulletEnemySFX)
			mAnimator->Play(L"PlayerPistolBulletEnemySFX", false);
		else if (mSfxType == eSfxType::NomalExplosionM)
			mAnimator->Play(L"NomalExplosionM", false);
		else if (mSfxType == eSfxType::Boss1SFX)
			mAnimator->Play(L"Boss1SFX", false);
		else if(mSfxType == eSfxType::Boss2SFX)
			mAnimator->Play(L"Boss2SFX", false);

	}
	void BulletSFX::destroySFX()
	{
		object::Destory(this);
	}
}