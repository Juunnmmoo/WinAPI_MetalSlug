#include "moEnemyPistolBullet.h"
#include "moImage.h"
#include "moResources.h"
#include "moTransform.h"
#include "moTime.h"
#include "Collider.h"
#include "moObject.h"
#include "moInput.h"
#include "moCamera.h"
#include "moAnimator.h"
#include "moRigidBody.h"
#include "moBulletSFX.h"
#include "moSceneManager.h"
#include "moScene.h"
#include "moCamera.h"
#include "moApplication.h"
#include "moBulletSFX.h"

extern mo::Application application;

namespace mo {
	EnemyPistolBullet::EnemyPistolBullet()
	{
	}
	EnemyPistolBullet::~EnemyPistolBullet()
	{
	}
	void EnemyPistolBullet::Initialize()
	{
		mImage = Resources::Load<Image>(L"OriginalBullet", L"..\\Resources\\Weapon\\Bullet\\OriginalBullet.bmp");

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 20.0f, 20.0f });

		SetBulletType(eBulletType::Bullet);
		GameObject::Initialize();
	}
	void EnemyPistolBullet::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		eDirection mDir = tr->GetDirection();

		if (GetState() == eState::Active)
		{
			if(mDir == eDirection::Right)
				pos.x += 1000.0f * Time::DeltaTime();
			else 
				pos.x -= 1000.0f * Time::DeltaTime();
			
			tr->SetPos(pos);
		}
	/*	else if (GetState() == eState::Pause)
		{
			Scene* curScene = SceneManager::GetActiveScene();
			BulletSFX* bulletSFX = new BulletSFX(eSfxType::PlayerBulletGroundSFX, pos, Vector2(2.0f, 2.0f), Vector2(0.0f, 49.0f));
			curScene->AddGameObject(bulletSFX, eLayerType::Effect);
			bulletSFX->Initialize();
			bulletSFX->PlayAnimation();
			object::Destory(this);
		}*/

		// �ڵ� isChanged
		Vector2 cPos = Camera::CaluatePos(pos);
		if (cPos.x <  -100.0f || cPos.x > application.GetWidth() + 100.0f || cPos.y < -100.0f)
			object::Destory(this);
		GameObject::Update();

	}
	void EnemyPistolBullet::Render(HDC mHdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = Camera::CaluatePos(tr->GetPos());
		TransparentBlt(mHdc, pos.x, pos.y, 20, 20, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(153, 217, 234));

		GameObject::Render(mHdc);

	}
	void EnemyPistolBullet::OnCollisionEnter(Collider* other)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (other->GetOwner()->GetLayerType() == eLayerType::Player )
		{
			Scene* curScene = SceneManager::GetActiveScene();
			BulletSFX* bulletSFX = new BulletSFX(eSfxType::PlayerBulletEnemySFX, pos, Vector2(2.5f, 2.5f), Vector2(0.0f, 60.0f));
			curScene->AddGameObject(bulletSFX, eLayerType::Effect);
			bulletSFX->Initialize();
			bulletSFX->PlayAnimation();
			object::Destory(this);
		}
	}
	void EnemyPistolBullet::OnCollisionStay(Collider* other)
	{
	}
	void EnemyPistolBullet::OnCollisionExit(Collider* other)
	{
	}
}