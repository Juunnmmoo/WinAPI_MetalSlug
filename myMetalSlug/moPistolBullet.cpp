#include "moPistolBullet.h"
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
#include "moBoss1_Missile.h"

extern mo::Application application;
namespace mo {
	PistolBullet::PistolBullet() 
		: mDirection(eDirection::Right)
		, mDir(Vector2(5.0f, 0.0f))
	{
		mDir.Normalize();
	}
	PistolBullet::~PistolBullet()
	{
	}
	void PistolBullet::Initialize()
	{
		mImage = Resources::Load<Image>(L"OriginalBullet", L"..\\Resources\\Weapon\\Bullet\\OriginalBullet.bmp");
		
		

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 20.0f, 20.0f });

		SetBulletType(eBulletType::Bullet);

		GameObject::Initialize();

	}
	void PistolBullet::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (GetState() == eState::Active)
		{
			pos.y += 1000.0f * mDir.y * Time::DeltaTime();
			pos.x += 1000.0f * mDir.x * Time::DeltaTime();
			tr->SetPos(pos);
		}
		else if (GetState() == eState::Pause)
		{
			Scene* curScene = SceneManager::GetActiveScene();
			BulletSFX* bulletSFX = new BulletSFX(eSfxType::PlayerBulletGroundSFX, pos, Vector2(2.0f, 2.0f), Vector2(0.0f, 49.0f));
			curScene->AddGameObject(bulletSFX, eLayerType::Effect);
			bulletSFX->Initialize();
			bulletSFX->PlayAnimation();
			object::Destory(this);
		}
		
		// ÀÚµ¿ isChanged
		Vector2 cPos = Camera::CaluatePos(pos);
		if (cPos.x <  -100.0f || cPos.x > application.GetWidth() + 100.0f || cPos.y < -100.0f)			
			object::Destory(this);

		GameObject::Update();
	}

	void PistolBullet::Render(HDC mHdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = Camera::CaluatePos(tr->GetPos());
		TransparentBlt(mHdc, pos.x, pos.y , 20, 20, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(153, 217, 234)); 

		GameObject::Render(mHdc);
	}
	void PistolBullet::OnCollisionEnter(Collider* other)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();



		if (other->GetOwner()->GetLayerType() == eLayerType::EnemyR || other->GetOwner()->GetLayerType() == eLayerType::Enemy ||
			other->GetOwner()->GetLayerType() == eLayerType::EnemyR_F || other->GetOwner()->GetLayerType() == eLayerType::Enemy_F || 
			other->GetOwner()->GetLayerType() == eLayerType::Slave)
		{

			Scene* curScene = SceneManager::GetActiveScene();
			BulletSFX* bulletSFX = new BulletSFX(eSfxType::PlayerBulletEnemySFX, pos, Vector2(2.5f, 2.5f), Vector2(0.0f, 60.0f));
			curScene->AddGameObject(bulletSFX, eLayerType::Effect);
			bulletSFX->Initialize();
			bulletSFX->PlayAnimation();
			object::Destory(this);
		}
	

		Boss1_Missile* missile = dynamic_cast<Boss1_Missile*>(other->GetOwner());
		if (missile != nullptr)
		{
			Scene* curScene = SceneManager::GetActiveScene();
			BulletSFX* bulletSFX = new BulletSFX(eSfxType::PlayerBulletEnemySFX, pos, Vector2(2.5f, 2.5f), Vector2(0.0f, 60.0f));
			curScene->AddGameObject(bulletSFX, eLayerType::Effect);
			bulletSFX->Initialize();
			bulletSFX->PlayAnimation();
			object::Destory(this);
		}
	}

	void PistolBullet::OnCollisionStay(Collider* other)
	{
	}

	void PistolBullet::OnCollisionExit(Collider* other)
	{
	}
}