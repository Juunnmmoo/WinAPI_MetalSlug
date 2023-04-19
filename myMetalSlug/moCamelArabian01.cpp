#include "moCamelArabian01.h"
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
#include "moCamel.h"
#include "moCamelArabian02.h"
#include "moEnemyPistolBullet.h"

extern mo::Application application;

namespace mo {
	CamelArabian01::CamelArabian01(Marco* p, Camel* camel, CamelArabian02* arbian, Scene* scene)
		: player(p)
		, mCamel(camel)
		, mSecond(arbian)
		, curScene(scene)
		, moveTime(0.0f)
		, bulletCnt(0)
		, heart(15)
	{
	}
	CamelArabian01::~CamelArabian01()
	{
	}
	void CamelArabian01::Initialize()
	{

		mT = GetComponent<Transform>();
		mT->SetPos(Vector2(1300.0f, 600.0f));
		mT->SetScale(Vector2{ 3.0f, 3.0f });
		mT->SetDisToBottom(Vector2{ 0.0f, 60.0f });
		mT->SetDirection(eDirection::Left);

	
		camelT = mCamel->GetComponent<Transform>();
		camelT->SetPos(mT->GetPos() + Vector2(0.0f, 125.0f));
		camelT->SetScale(Vector2{ 3.0f, 3.0f });
		camelT->SetDisToBottom(Vector2{ 0.0f, 60.0f });
		camelT->SetDirection(eDirection::Left);


		secondT = mSecond->GetComponent<Transform>();
		secondT->SetPos(mT->GetPos());
		secondT->SetScale(Vector2{ 3.0f, 3.0f });
		secondT->SetDisToBottom(Vector2{ 0.0f, 60.0f });
		secondT->SetDirection(eDirection::Left);

		RigidBody* mRigidbody = AddComponent<RigidBody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2(0.0f, 600.0f));
		mRigidbody->SetGround(true);

		Image* mImage = Resources::Load<Image>(L"CamelArabian", L"..\\Resources\\Enemy\\CamelArabian.bmp");

		mAnimator = AddComponent<Animator>();
		camelAnimator = mCamel->AddComponent<Animator>();
		secondAnimator = mSecond->AddComponent<Animator>();

		mAnimator->CreateAnimation(L"StartAnimation", mImage, Vector2(120.0f * 0, 120.0f * 0), 120.0f, 12, 22, 10, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"IdleL", mImage, Vector2(120.0f * 0, 120.0f * 1), 120.0f, 12, 22, 3, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"NS_IdleL", mImage, Vector2(120.0f * 3, 120.0f * 1), 120.0f, 12, 22, 3, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"TurnL", mImage, Vector2(120.0f * 0, 120.0f * 2), 120.0f, 12, 22, 4, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"NS_TurnL", mImage, Vector2(120.0f * 4, 120.0f * 2), 120.0f, 12, 22, 4, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"LostSwordL", mImage, Vector2(120.0f * 0, 120.0f * 7), 120.0f, 12, 22, 4, Vector2::Zero, 0.15);

		mAnimator->CreateAnimation(L"IdleR", mImage, Vector2(120.0f * 11, 120.0f * 12), -120.0f, 12, 22, 3, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"NS_IdleR", mImage, Vector2(120.0f * 8, 120.0f * 12), -120.0f, 12, 22, 3, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"TurnR", mImage, Vector2(120.0f * 11, 120.0f * 13), -120.0f, 12, 22, 4, Vector2::Zero, 0.03);
		mAnimator->CreateAnimation(L"NS_TurnR", mImage, Vector2(120.0f * 7, 120.0f * 13), -120.0f, 12, 22, 4, Vector2::Zero, 0.05);
		mAnimator->CreateAnimation(L"LostSwordR", mImage, Vector2(120.0f * 11, 120.0f * 18), -120.0f, 12, 22, 4, Vector2::Zero, 0.15);
		mAnimator->CreateAnimation(L"None", mImage, Vector2(120.0f * 11, 120.0f * 0), 120.0f, 12, 22, 1, Vector2::Zero, 0.1);
	



		mAnimator->Play(L"None", true);

		camelAnimator->CreateAnimation(L"MoveR", mImage, Vector2(120.0f * 0, 120.0f * 9), 120.0f, 12, 22, 12, Vector2::Zero, 0.04);
		camelAnimator->CreateAnimation(L"MoveL", mImage, Vector2(120.0f * 11, 120.0f * 9), -120.0f, 12, 22, 12, Vector2::Zero, 0.04);
		camelAnimator->CreateAnimation(L"Down", mImage, Vector2(120.0f * 0, 120.0f * 10), 120.0f, 12, 22, 3, Vector2::Zero, 0.05);
		camelAnimator->CreateAnimation(L"Idle", mImage, Vector2(120.0f * 0, 120.0f * 11), 120.0f, 12, 22, 4, Vector2::Zero, 0.05);

		camelAnimator->Play(L"MoveL", true);

		secondAnimator->CreateAnimation(L"DownL", mImage, Vector2(120.0f * 0, 120.0f * 4), 120.0f, 12, 22, 3, Vector2::Zero, 0.05);
		secondAnimator->CreateAnimation(L"NS_DownL", mImage, Vector2(120.0f * 3, 120.0f * 4), 120.0f, 12, 22, 3, Vector2::Zero, 0.05);
		secondAnimator->CreateAnimation(L"ShootL", mImage, Vector2(120.0f * 0, 120.0f * 5), 120.0f, 12, 22, 10, Vector2::Zero, 0.03);
		secondAnimator->CreateAnimation(L"NS_ShootL", mImage, Vector2(120.0f * 0, 120.0f * 3), 120.0f, 12, 22, 10, Vector2::Zero, 0.03);
		secondAnimator->CreateAnimation(L"IdleDownL", mImage, Vector2(120.0f * 0, 120.0f * 6), 120.0f, 12, 22, 3, Vector2::Zero, 0.05);
		secondAnimator->CreateAnimation(L"LostSwordDownL", mImage, Vector2(120.0f * 0, 120.0f * 8), 120.0f, 12, 22, 4, Vector2::Zero, 0.15);

		secondAnimator->CreateAnimation(L"DownR", mImage, Vector2(120.0f * 11, 120.0f * 15), -120.0f, 12, 22, 3, Vector2::Zero, 0.05);
		secondAnimator->CreateAnimation(L"NS_DownR", mImage, Vector2(120.0f * 8, 120.0f * 15), -120.0f, 12, 22, 3, Vector2::Zero, 0.05);
		secondAnimator->CreateAnimation(L"ShootR", mImage, Vector2(120.0f * 11, 120.0f * 16), -120.0f, 12, 22, 10, Vector2::Zero, 0.03);
		secondAnimator->CreateAnimation(L"NS_ShootR", mImage, Vector2(120.0f * 11, 120.0f * 14), -120.0f, 12, 22, 10, Vector2::Zero, 0.03);
		secondAnimator->CreateAnimation(L"IdleDownR", mImage, Vector2(120.0f * 11, 120.0f * 17), -120.0f, 12, 22, 3, Vector2::Zero, 0.05);
		secondAnimator->CreateAnimation(L"LostSwordDownR", mImage, Vector2(120.0f * 11, 120.0f * 19), -120.0f, 12, 22, 4, Vector2::Zero, 0.15);
		secondAnimator->CreateAnimation(L"None", mImage, Vector2(120.0f *11, 120.0f * 4), 120.0f, 12, 22, 1, Vector2::Zero, 0.05);
		secondAnimator->CreateAnimation(L"DeathL", mImage, Vector2(120.0f * 0, 120.0f * 20), 120.0f, 12, 22, 11, Vector2::Zero, 0.07);
		secondAnimator->CreateAnimation(L"DeathR", mImage, Vector2(120.0f * 11, 120.0f * 21), -120.0f, 12, 22, 11, Vector2::Zero, 0.07);
		mState = eCamelArabianState::Start;

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 100.0f, 100.0f });
		mCollider->SetLeftTop(Vector2{ -50.50f, -100.0f });


		GameObject::Initialize();
	}
	void CamelArabian01::Update()
	{
	
		switch (mState) {
		case mo::CamelArabian01::eCamelArabianState::Start:
			start();
			break;
		case mo::CamelArabian01::eCamelArabianState::Move:
			move();
			break;
		case mo::CamelArabian01::eCamelArabianState::Idle:
			idle();
			break;
		case mo::CamelArabian01::eCamelArabianState::Death:
			death();
			break;
		case mo::CamelArabian01::eCamelArabianState::Attack:
			attack();
			break;
		case mo::CamelArabian01::eCamelArabianState::Turn:
			turn();
			break;
		case mo::CamelArabian01::eCamelArabianState::Lost:
			lost();
			break;
		default:
			break;
		}

		Vector2 mPos = mT->GetPos();
		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();
		eDirection mDir = mT->GetDirection();

		if (heart == 1)
		{
			heart = 0;
			if (mState == eCamelArabianState::Move)
			{
				noHeart = true;
				if(mDir== eDirection::Left)
					mAnimator->Play(L"LostSwordL", false);
				else 
					mAnimator->Play(L"LostSwordR", false);

			}
			else if (mState == eCamelArabianState::Attack)
			{
				noHeart = true; 
				if (mDir == eDirection::Left)
					secondAnimator->Play(L"LostSwordDownL", false);
				else
					secondAnimator->Play(L"LostSwordDownR", false);

			}
			mState = eCamelArabianState::Lost;

		}
	
		if (mState != eCamelArabianState::Death)
		{
			camelT->SetPos(mPos + Vector2(-10.0f, 125.0f));
			secondT->SetPos(mPos);
		}
	

		//IdleÀÏ¶§¸¸?
		

		GameObject::Update();

	}
	void CamelArabian01::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void CamelArabian01::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetBulletType() == eBulletType::Bullet)
		{
			if( heart >= 2 && mState != eCamelArabianState::Start)
				heart--;
			else if (noHeart && mState != eCamelArabianState::Lost)
			{
				eDirection mDir = mT->GetDirection();

				mAnimator->Play(L"None", false);
				camelAnimator->Play(L"MoveL", true);
				if(mDir == eDirection::Left)
					secondAnimator->Play(L"DeathL", false);
				else 
					secondAnimator->Play(L"DeathR", false);
				
				SetState(eState::Pause);
				mState = eCamelArabianState::Death;
			}
		}
	}
	void CamelArabian01::OnCollisionStay(Collider* other)
	{
	}
	void CamelArabian01::OnCollisionExit(Collider* other)
	{
	}
	void CamelArabian01::start()
	{
		
		Vector2 mPos = mT->GetPos();
		mPos.x -= 300.0f * Time::DeltaTime();

		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();
		eDirection mDir = mT->GetDirection();
		Vector2 cPos = Camera::CaluatePos(mPos);

		if (cPos.x < application.GetWidth() - 150.0f && !isPlayed)
		{
			isPlayed = true;
			mAnimator->Play(L"StartAnimation", false);
		}
		if (isPlayed && mAnimator->IsComplte())
		{	
			mAnimator->Play(L"IdleL", true);
			mState = eCamelArabianState::Move;
		}
		mT->SetPos(mPos);
	}
	void CamelArabian01::move()
	{
		Vector2 mPos = mT->GetPos();
		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();
		eDirection mDir = mT->GetDirection();
		Vector2 cPos = Camera::CaluatePos(mPos);

		moveTime += Time::DeltaTime();


		if (!noHeart)
		{
			if (mPos.x >= playerPos.x && mDir == eDirection::Right)
			{
				mAnimator->Play(L"TurnR", false);
				mT->SetDirection(eDirection::Left);
				mState = eCamelArabianState::Turn;
			}
			else if (mPos.x < playerPos.x && mDir == eDirection::Left)
			{
				mAnimator->Play(L"TurnL", false);
				mT->SetDirection(eDirection::Right);
				mState = eCamelArabianState::Turn;
			}

			if (mDir == eDirection::Right)
			{
				if (moveTime < 2.5f)
				{
					if (cPos.x > 25.0f)
						mPos.x -= 300.0f * Time::DeltaTime();
					else
						moveTime = 2.5f;
				}
				else if (moveTime >= 2.5f && moveTime < 4.0f)
				{
					if (cPos.x < application.GetWidth() - 25.0f)
						mPos.x += 300.0f * Time::DeltaTime();
					else
						moveTime = 4.0f;
				}
				else
				{
					moveTime = 0.0f;
					mAnimator->Play(L"None", false);
					camelAnimator->Play(L"Down", false);
					secondAnimator->Play(L"DownR", false);
					mState = eCamelArabianState::Attack;

					Collider* mCollider = GetComponent<Collider>();
					mCollider->SetSize(Vector2{ 100.0f, 100.0f });
					mCollider->SetLeftTop(Vector2{ -50.50f, -20.0f });

				}
			}
			else
			{
				if (moveTime < 2.5f)
				{
					if (cPos.x < application.GetWidth()-25.0f )
						mPos.x += 300.0f * Time::DeltaTime();
					else
					{
						moveTime = 2.5f;
					}

				}
				else if (moveTime >= 2.5f && moveTime < 4.0f)
				{
					if (cPos.x > 25.0f)
						mPos.x -= 300.0f * Time::DeltaTime();
					else
						moveTime = 4.0f;

				}
				else
				{
					moveTime = 0.0f;
					mAnimator->Play(L"None", false);			
					camelAnimator->Play(L"Down", false);
					secondAnimator->Play(L"DownL", false);
					mState = eCamelArabianState::Attack;

					Collider* mCollider = GetComponent<Collider>();
					mCollider->SetSize(Vector2{ 100.0f, 100.0f });
					mCollider->SetLeftTop(Vector2{ -50.50f, -20.0f });

				}
			}
		}
		else
		{
			if (mPos.x >= playerPos.x && mDir == eDirection::Right)
			{
				mAnimator->Play(L"NS_TurnR", false);
				mT->SetDirection(eDirection::Left);
				mState = eCamelArabianState::Turn;
			}
			else if (mPos.x < playerPos.x && mDir == eDirection::Left)
			{
				mAnimator->Play(L"NS_TurnL", false);
				mT->SetDirection(eDirection::Right);
				mState = eCamelArabianState::Turn;
			}

			if (mDir == eDirection::Right)
			{
				if (moveTime < 3.0f)
				{
					if (cPos.x > 25.0f)
						mPos.x -= 300.0f * Time::DeltaTime();
					else
						moveTime = 3.0f;
				}
				else if (moveTime >= 3.0f && moveTime < 5.0f)
				{
					if (cPos.x < application.GetWidth() - 25.0f)
						mPos.x += 300.0f * Time::DeltaTime();
					else
						moveTime = 5.0f;
				}
				else
				{
					moveTime = 0.0f;
					mAnimator->Play(L"None", false);
					camelAnimator->Play(L"Down", false);
					secondAnimator->Play(L"NS_DownR", false);
					mState = eCamelArabianState::Attack;

					Collider* mCollider = GetComponent<Collider>();
					mCollider->SetSize(Vector2{ 100.0f, 100.0f });
					mCollider->SetLeftTop(Vector2{ -50.50f, -20.0f });

				}
			}
			else
			{
				if (moveTime < 3.0f)
				{
					if (cPos.x < application.GetWidth() - 25.0f)
						mPos.x += 300.0f * Time::DeltaTime();
					else
					{
						moveTime = 3.0f;
					}

				}
				else if (moveTime >= 3.0f && moveTime < 5.0f)
				{
					if (cPos.x > 25.0f)
						mPos.x -= 300.0f * Time::DeltaTime();
					else
						moveTime = 5.0f;

				}
				else
				{
					moveTime = 0.0f;
					mAnimator->Play(L"None", false);
					camelAnimator->Play(L"Down", false);
					secondAnimator->Play(L"NS_DownL", false);
					mState = eCamelArabianState::Attack;

					Collider* mCollider = GetComponent<Collider>();
					mCollider->SetSize(Vector2{ 100.0f, 100.0f });
					mCollider->SetLeftTop(Vector2{ -50.50f, -20.0f });

				}
			}
		}

		mT->SetPos(mPos);
	}
	void CamelArabian01::attack()
	{
		Vector2 mPos = mT->GetPos();
		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();
		eDirection mDir = mT->GetDirection();
		Vector2 cPos = Camera::CaluatePos(mPos);

		if (!noHeart)
		{
			if (secondAnimator->IsComplte())
			{
				if (bulletCnt >= 3)
				{
					bulletCnt = 0;

					Collider* mCollider = GetComponent<Collider>();
					mCollider->SetSize(Vector2{ 100.0f, 100.0f });
					mCollider->SetLeftTop(Vector2{ -50.50f, -100.0f });

					if (mDir == eDirection::Left)
					{

						secondAnimator->Play(L"None", false);
						mAnimator->Play(L"IdleL", true);
						camelAnimator->Play(L"MoveL", true);
						mState = eCamelArabianState::Move;
					}
					else
					{
						secondAnimator->Play(L"None", false);
						mAnimator->Play(L"IdleR", true);
						camelAnimator->Play(L"MoveL", true);
						mState = eCamelArabianState::Move;

					}
				}
				else 
				{
					bulletCnt++;
					if (mDir == eDirection::Right)
					{
						secondAnimator->Play(L"ShootR", false);

						EnemyPistolBullet* pistolBullet = new EnemyPistolBullet();

						pistolBullet->GetComponent<Transform>()->SetDirection(eDirection::Right);
						pistolBullet->GetComponent<Transform>()->SetPos(mT->GetPos() + Vector2(10.0f, 10.0f));
							
						curScene->AddGameObject(pistolBullet, eLayerType::EnemyBullet);
						pistolBullet->Initialize();
					}
					else
					{
						secondAnimator->Play(L"ShootL", false);

						EnemyPistolBullet* pistolBullet = new EnemyPistolBullet();

						pistolBullet->GetComponent<Transform>()->SetDirection(eDirection::Left);
						pistolBullet->GetComponent<Transform>()->SetPos(mT->GetPos() + Vector2(-10.0f, 10.0f));

						curScene->AddGameObject(pistolBullet, eLayerType::EnemyBullet);
						pistolBullet->Initialize();
					}
				}
			}
		}
		else
		{
			if (secondAnimator->IsComplte())
			{
				if (bulletCnt >= 3)
				{
					bulletCnt = 0;

					Collider* mCollider = GetComponent<Collider>();
					mCollider->SetSize(Vector2{ 100.0f, 100.0f });
					mCollider->SetLeftTop(Vector2{ -50.50f, -100.0f });

					if (mDir == eDirection::Left)
					{

						secondAnimator->Play(L"None", false);
						mAnimator->Play(L"NS_IdleL", true);
						camelAnimator->Play(L"MoveL", true);
						mState = eCamelArabianState::Move;
					}
					else
					{
						secondAnimator->Play(L"None", false);
						mAnimator->Play(L"NS_IdleR", true);
						camelAnimator->Play(L"MoveL", true);
						mState = eCamelArabianState::Move;

					}
				}
				else
				{
					bulletCnt++;
					if (mDir == eDirection::Right)
					{
						secondAnimator->Play(L"NS_ShootR", false);

						EnemyPistolBullet* pistolBullet = new EnemyPistolBullet();

						pistolBullet->GetComponent<Transform>()->SetDirection(eDirection::Right);
						pistolBullet->GetComponent<Transform>()->SetPos(mT->GetPos() + Vector2(10.0f, 10.0f));

						curScene->AddGameObject(pistolBullet, eLayerType::EnemyBullet);
						pistolBullet->Initialize();
					}
					else
					{
						secondAnimator->Play(L"NS_ShootL", false);

						EnemyPistolBullet* pistolBullet = new EnemyPistolBullet();

						pistolBullet->GetComponent<Transform>()->SetDirection(eDirection::Left);
						pistolBullet->GetComponent<Transform>()->SetPos(mT->GetPos() + Vector2(-10.0f, 10.0f));

						curScene->AddGameObject(pistolBullet, eLayerType::EnemyBullet);
						pistolBullet->Initialize();
					}
				}
			}
		}
	
	}

	void CamelArabian01::death()
	{
		Vector2 camelPos = camelT->GetPos();
		camelPos.x -= 300.0f * Time::DeltaTime();
		camelT->SetPos(camelPos);
		
		secondT->SetPos(mT->GetPos());

		if (secondAnimator->IsComplte())
			secondAnimator->Play(L"None", true);

		if (Camera::CaluatePos(camelPos).x < -150.0f)
		{
			object::Destory(this);
			object::Destory(mCamel);
			object::Destory(mSecond);
			Camera::SetStop(false);
		}

	}
	void CamelArabian01::idle()
	{
		Vector2 mPos = mT->GetPos();
		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();
		eDirection mDir = mT->GetDirection();
		Vector2 cPos = Camera::CaluatePos(mPos);
		if (!noHeart)
		{
			if (mAnimator->IsComplte())
			{
				if (mDir == eDirection::Left)
				{
					mAnimator->Play(L"IdleL", true);
					mState = eCamelArabianState::Move;
				}
				else
				{
					mAnimator->Play(L"IdleR", true);
					mState = eCamelArabianState::Move;

				}

			}
		}
		else
		{
			if (mAnimator->IsComplte())
			{
				if (mDir == eDirection::Left)
				{
					mAnimator->Play(L"NS_IdleL", true);
					mState = eCamelArabianState::Move;
				}
				else
				{
					mAnimator->Play(L"NS_IdleR", true);
					mState = eCamelArabianState::Move;

				}

			}
		}
	}
	void CamelArabian01::turn()
	{
		Vector2 mPos = mT->GetPos();
		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();
		eDirection mDir = mT->GetDirection();
		Vector2 cPos = Camera::CaluatePos(mPos);
		if (!noHeart)
		{
			if (mAnimator->IsComplte())
			{
				if (mDir == eDirection::Left)
				{
					mAnimator->Play(L"IdleL", false);
					mState = eCamelArabianState::Idle;
				}
				else
				{
					mAnimator->Play(L"IdleR", false);
					mState = eCamelArabianState::Idle;

				}

			}
		}
		else
		{
			if (mAnimator->IsComplte())
			{
				if (mDir == eDirection::Left)
				{
					mAnimator->Play(L"NS_IdleL", false);
					mState = eCamelArabianState::Idle;
				}
				else
				{
					mAnimator->Play(L"NS_IdleR", false);
					mState = eCamelArabianState::Idle;

				}

			}
		}
	}
	void CamelArabian01::lost()
	{
		Vector2 mPos = mT->GetPos();
		Vector2 playerPos = player->GetComponent<Transform>()->GetPos();
		eDirection mDir = mT->GetDirection();
		Vector2 cPos = Camera::CaluatePos(mPos);
		
		if (mAnimator->GetActiveAnimation()->GetName() == L"None")
		{
			if (secondAnimator->IsComplte())
			{
				bulletCnt = 0;

				Collider* mCollider = GetComponent<Collider>();
				mCollider->SetSize(Vector2{ 100.0f, 100.0f });
				mCollider->SetLeftTop(Vector2{ -50.50f, -100.0f });

				if (mDir == eDirection::Left)
				{
					secondAnimator->Play(L"None", false);
					mAnimator->Play(L"NS_IdleL", true);
					camelAnimator->Play(L"MoveL", true);
					mState = eCamelArabianState::Move;
				}
				else
				{
					secondAnimator->Play(L"None", false);
					mAnimator->Play(L"NS_IdleR", true);
					camelAnimator->Play(L"MoveL", true);
					mState = eCamelArabianState::Move;

				}
			}
		}
		else 
		{
			if (mAnimator->IsComplte())
			{
				moveTime = 0.0f;
				if (mDir == eDirection::Left)
				{
					mAnimator->Play(L"NS_IdleL", true);
					mState = eCamelArabianState::Move;
				}
				else
				{
					mAnimator->Play(L"NS_IdleR", true);
					mState = eCamelArabianState::Move;

				}
			}
		}

	}
}