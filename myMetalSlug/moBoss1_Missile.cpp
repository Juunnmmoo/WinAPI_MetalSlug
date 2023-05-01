#include "moBoss1_Missile.h"
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
#include "moMath.h"
#include "moBulletSFX.h"
#include "moSceneManager.h"
#include "moScene.h"
#include "moSound.h"
namespace mo {
	Boss1_Missile::Boss1_Missile(Marco* marco)
		: mPlayer(marco)
		, mTime(0.0f)
	{
	}
	Boss1_Missile::~Boss1_Missile()
	{
	}
	void Boss1_Missile::Initialize()
	{
		bombSound = Resources::Load<Sound>(L"bombSound", L"..\\Resources\\Sound\\bombSound.wav");
		bombSound->SetVolume(80);

		Transform* tr;
		tr = GetComponent<Transform>();
		tr->SetScale(Vector2(3.0f, 3.0f));
		tr->SetDisToBottom(Vector2(0.0f, 50.0f));
		tr->SetDirection(eDirection::Left);

		/*RigidBody* mRigidbody = AddComponent<RigidBody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2(0.0f, 700.0f));
		mRigidbody->SetGround(true);*/


		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 60.0f, 40.0f });
		mCollider->SetLeftTop(Vector2{ -30.0f, -30.0f });

		mImage = Resources::Load<Image>(L"Boss1_Missile", L"..\\Resources\\Enemy\\Boss1\\Boss1_Missile.bmp");

		mAnimator = AddComponent<Animator>();


		mAnimator->CreateAnimation(L"StartRight", mImage, Vector2(100.0f * 0, 100.0f * 0), 100.0f, 42, 17, 42, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"StartLeft", mImage, Vector2(100.0f * 41, 100.0f * 1), -100.0f, 42, 17, 42, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"RotateTopToBottomR", mImage, Vector2(100.0f * 0, 100.0f * 2), 100.0f, 42, 17, 24, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"RotateTopToBottomL", mImage, Vector2(100.0f * 23, 100.0f * 3), -100.0f, 42, 17, 24, Vector2::Zero, 0.05);
	/*	mAnimator->CreateAnimation(L"RotateBottomLeft", mImage, Vector2(100.0f * 23, 100.0f * 4), 100.0f, 42, 17, 24, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"RotateBottomRight", mImage, Vector2(100.0f * 0, 100.0f * 5), 100.0f, 42, 17, 24, Vector2::Zero, 0.05);*/
		mAnimator->CreateAnimation(L"RotateRightToBottom", mImage, Vector2(100.0f * 0, 100.0f * 6), 100.0f, 42, 17, 15, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"RotateLeftToBottom", mImage, Vector2(100.0f * 14, 100.0f * 7), -100.0f, 42, 17, 15, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MoveBottomLeft", mImage, Vector2(100.0f * 0, 100.0f * 8), 100.0f, 42, 17, 12, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MoveBottomRight", mImage, Vector2(100.0f * 11	, 100.0f * 9), -100.0f, 42, 17, 12, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MoveLeft", mImage, Vector2(100.0f * 0, 100.0f * 10), 100.0f, 42, 17, 12, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"MoveRight", mImage, Vector2(100.0f * 11, 100.0f * 11), -100.0f, 42, 17, 12, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"RotateLeftToTop", mImage, Vector2(100.0f * 14, 100.0f * 12), -100.0f, 42, 17, 15, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"RotateRightToTop", mImage, Vector2(100.0f * 0, 100.0f * 13), 100.0f, 42, 17, 15, Vector2::Zero, 0.05);
		//mAnimator->CreateAnimation(L"MoveBottomLeft", mImage, Vector2(100.0f * 0, 100.0f * 14), 100.0f, 42, 17, 24, Vector2::Zero, 0.05);
		//mAnimator->CreateAnimation(L"MoveBottomRight", mImage, Vector2(100.0f * 23, 100.0f * 15), -100.0f, 42, 17, 24, Vector2::Zero, 0.05);
		SetBulletType(eBulletType::Bomb);	

		GameObject::Initialize();
	}
	void Boss1_Missile::Update()
	{
	

		Transform* tr;
		tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Transform* playerTR = mPlayer->GetComponent<Transform>();
		Vector2 playerPos = playerTR->GetPos();

	

		switch (mState) {
		case mo::Boss1_Missile::eBoss1MisileState::Start:
			start();
			break;
		case mo::Boss1_Missile::eBoss1MisileState::RotateDown:
			rotateDown();
			break;
		case mo::Boss1_Missile::eBoss1MisileState::MoveDown:
			moveDown();
			break;
		case mo::Boss1_Missile::eBoss1MisileState::UnderStandard:
			underStandard();
			break;
		case mo::Boss1_Missile::eBoss1MisileState::MoveUp:
			moveUp();
			break;
		case mo::Boss1_Missile::eBoss1MisileState::RotateToBottom:
			rotateToBottom();
			break;
		}



		GameObject::Update();

	}
	void Boss1_Missile::Render(HDC mHdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 cPos = Camera::CaluatePos(tr->GetPos());
		TransparentBlt(mHdc, cPos.x, cPos.y, 20, 20, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(153, 217, 234));

		GameObject::Render(mHdc);

	}
	void Boss1_Missile::OnCollisionEnter(Collider* other)
	{
	
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (other->GetOwner()->GetLayerType() == eLayerType::PlayerPistol ||
			other->GetOwner()->GetLayerType() == eLayerType::PlayerMachinegun ||
			other->GetOwner()->GetLayerType() == eLayerType::PlayerShotgun ||
			other->GetOwner()->GetLayerType() == eLayerType::PlayerFiregun ||
			other->GetOwner()->GetLayerType() == eLayerType::PlayerBomb ||
			other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			bombSound->Play(false);
			Scene* curScene = SceneManager::GetActiveScene();
			BulletSFX* bulletSFX = new BulletSFX(eSfxType::NomalExplosionM, pos, Vector2(2.5f, 2.5f), Vector2(0.0f, 36.0f));
			curScene->AddGameObject(bulletSFX, eLayerType::Effect);
			bulletSFX->Initialize();
			bulletSFX->PlayAnimation();

			object::Destory(this);
		}


	}
	void Boss1_Missile::OnCollisionStay(Collider* other)
	{
	}
	void Boss1_Missile::OnCollisionExit(Collider* other)
	{
	}
	void Boss1_Missile::PlayAnimation(eDirection direction)
	{
	}
	void Boss1_Missile::start()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 playerPos = mPlayer->GetComponent<Transform>()->GetPos();
		Vector2 toDir = playerPos - pos;
		toDir.Normalize();

		eDirection mDir = tr->GetDirection();

		if (mDir == eDirection::Left)
		{
			pos.x -= 100.0f * Time::DeltaTime();
			tr->SetPos(pos);
		}
		else
		{
			pos.x += 100.0f * Time::DeltaTime();
			tr->SetPos(pos);
		}

		if (!isPlayed)
		{
			isPlayed = true;
			if (mDir == eDirection::Left)
			{
				mAnimator->Play(L"StartLeft", false);
			}
			else
			{
				mAnimator->Play(L"StartRight", false);

			}
		}
		else
		{
			if (mAnimator->IsComplte())
			{
				isPlayed = false;
				if (mDir == eDirection::Left)
				{
					dir = Vector2(-1.0f, 1.0f);
					dir.Normalize();
					mAnimator->Play(L"RotateLeftToBottom", false);
					mState = eBoss1MisileState::RotateDown;
				}
				else
				{
					dir = Vector2(1.0f, 1.0f);
					dir.Normalize();
					mAnimator->Play(L"RotateRightToBottom", false);
					mState = eBoss1MisileState::RotateDown;
					
				}
				
			}
		}

	}
	void Boss1_Missile::rotateDown()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 playerPos = mPlayer->GetComponent<Transform>()->GetPos();
		Vector2 toDir = playerPos - pos;
		toDir.Normalize();

		pos.x += 100.0f * dir.x * Time::DeltaTime();
		pos.y += 100.0f * dir.y * Time::DeltaTime();
		tr->SetPos(pos);

		if (mAnimator->IsComplte())
		{
			dir = toDir;
			if (toDir.x >= 0)
			{
				//dir = Vector2(1.0f, 1.0f);
				//dir.Normalize();
				mAnimator->Play(L"MoveBottomRight", true);
				mState = eBoss1MisileState::MoveDown;
			}
			else
			{
				//dir = Vector2(-1.0f, 1.0f);
				//dir.Normalize();
				mAnimator->Play(L"MoveBottomLeft", true);
				mState = eBoss1MisileState::MoveDown;
			}

		}
	}
	void Boss1_Missile::moveDown()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 cPos = Camera::CaluatePos(pos);
		Vector2 playerPos = mPlayer->GetComponent<Transform>()->GetPos();
		Vector2 toDir = playerPos - pos;
		toDir.Normalize();

		pos.x += 200.0f * dir.x * Time::DeltaTime();
		pos.y += 200.0f * dir.y * Time::DeltaTime();
		tr->SetPos(pos);

		if (cPos.y >= 650.0f)
		{
			if (dir.x >= 0)
			{
				dir = Vector2(1.0f, 0.0f);
				dir.Normalize();
				mAnimator->Play(L"MoveRight", true);
				mState = eBoss1MisileState::UnderStandard;
			}
			else
			{
				dir = Vector2(-1.0f, 0.0f);
				dir.Normalize();
				mAnimator->Play(L"MoveLeft", true);
				mState = eBoss1MisileState::UnderStandard;
			}
		}
		
	}
	void Boss1_Missile::underStandard()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 playerPos = mPlayer->GetComponent<Transform>()->GetPos();
		Vector2 toDir = playerPos - pos;
		toDir.Normalize();

		pos.x += 200.0f * dir.x * Time::DeltaTime();
		pos.y += 200.0f * dir.y * Time::DeltaTime();
		tr->SetPos(pos);

		if ((dir.x >= 0 && toDir.x < 0) || (dir.x < 0 && toDir.x >= 0))
		{
			if (dir.x >= 0)
			{
				dir = Vector2(1.0f, -1.0f);
				dir.Normalize();
				mAnimator->Play(L"RotateRightToTop", false);
				mState = eBoss1MisileState::MoveUp;
			}
			else
			{
				dir = Vector2(-1.0f, -1.0f);
				dir.Normalize();
				mAnimator->Play(L"RotateLeftToTop", false);
				mState = eBoss1MisileState::MoveUp;
			}
		}
	}
	void Boss1_Missile::moveUp()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 playerPos = mPlayer->GetComponent<Transform>()->GetPos();
		Vector2 toDir = playerPos - pos;
		toDir.Normalize();

		pos.x += 200.0f * dir.x * Time::DeltaTime();
		pos.y += 200.0f * dir.y * Time::DeltaTime();
		tr->SetPos(pos);

		if (mAnimator->IsComplte())
		{
			if (dir.x >= 0)
			{
				dir = Vector2(-1.0f, -2.0f);
				dir.Normalize();
				mAnimator->Play(L"RotateTopToBottomL", false);
				mState = eBoss1MisileState::RotateToBottom;
			}
			else
			{
				dir = Vector2(1.0f, -2.0f);
				dir.Normalize();
				mAnimator->Play(L"RotateTopToBottomR", false);
				mState = eBoss1MisileState::RotateToBottom;
			}
		}
	}
	void Boss1_Missile::rotateToBottom()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 playerPos = mPlayer->GetComponent<Transform>()->GetPos();
		Vector2 toDir = playerPos - pos;
		toDir.Normalize();

		dir.y += 1.0 * Time::DeltaTime();

		pos.x += 200.0f * dir.x * Time::DeltaTime();
		pos.y += 200.0f * dir.y * Time::DeltaTime();
		tr->SetPos(pos);

		if (mAnimator->IsComplte())
		{
			dir = toDir;
			if (toDir.x >= 0)
			{
				//dir = Vector2(1.0f, 1.0f);
				//dir.Normalize();
				mAnimator->Play(L"MoveBottomRight", true);
				mState = eBoss1MisileState::MoveDown;
			}
			else
			{
				//dir = Vector2(-1.0f, 1.0f);
				//dir.Normalize();
				mAnimator->Play(L"MoveBottomLeft", true);
				mState = eBoss1MisileState::MoveDown;
			}

		}
	}
	void Boss1_Missile::rotateLeft()
	{
	}
}