#include "moBoss2Creator.h"
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
#include "moRebelTruck1.h"
#include "moRebelTruck2.h"
#include "moArabianFighter.h"
#include "moAbulAbbas.h"
#include "moBoss2_Base.h"
#include "moBoss2_Door.h"
#include "moBoss2_Propeller.h"
#include "moBoss2_Weapon.h"
#include "moSound.h"
#include "moBoss2LaserCollider.h"
#include "moSlave.h"
namespace mo {
	Boss2Creator::Boss2Creator(Marco* marco, Sound* sound)
		: player(marco)
		, activeSound(sound)
	{
	}
	Boss2Creator::~Boss2Creator()
	{
	}
	void Boss2Creator::Initialize()
	{


		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(12300.0f, 0.0f));

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 20.0f, 750.0f });

		GameObject::Initialize();
	}
	void Boss2Creator::Update()
	{

		time += Time::DeltaTime();

		if (time >= 35.0f)
		{
			time = 0.0f;
			Scene* curScene = SceneManager::GetActiveScene();

			Slave* slave = new Slave(player, curScene, Vector2(10000.0f, 700.0f), eMarcoWeapon::Machinegun);
			curScene->AddGameObject(slave, eLayerType::Slave);
			slave->Initialize();
			slave->IndicateRight();
		}
		GameObject::Update();
	}
	void Boss2Creator::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void Boss2Creator::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			if (!stopCreate)
			{
				stopCreate = true;
				Scene* curScene = SceneManager::GetActiveScene();
				activeSound->Stop(true);
				//BossBGM->Play(true);
				player->SetBossZone(true);

				Boss2_Door* boss2_door = new Boss2_Door();
				Boss2_Weapon* boss2_weapon = new Boss2_Weapon();
				Boss2_Propeller* boss2_propeller = new Boss2_Propeller();

				Boss2LaserCollider* left = new Boss2LaserCollider(eDirection::Left);
				Boss2LaserCollider* right = new Boss2LaserCollider(eDirection::Right);

				Boss2_Base* boss2_Base = new Boss2_Base(player, curScene, boss2_door, boss2_weapon, boss2_propeller, left, right);
				
				curScene->AddGameObject(boss2_Base, eLayerType::Enemy);
				boss2_Base->Initialize();

				curScene->AddGameObject(boss2_door, eLayerType::Enemy);
				boss2_door->GetComponent<Transform>()->SetPos(Vector2(12512.0f, 350.0f));
				boss2_door->Initialize();

				curScene->AddGameObject(boss2_weapon, eLayerType::Enemy);
				boss2_weapon->GetComponent<Transform>()->SetPos(Vector2(12512.0f, 434.0f));
				boss2_weapon->Initialize();

				curScene->AddGameObject(boss2_propeller, eLayerType::Enemy);
				boss2_propeller->GetComponent<Transform>()->SetPos(Vector2(12512.0f, 350.0f));
				boss2_propeller->Initialize();


				curScene->AddGameObject(left, eLayerType::EnemyBullet);
				left->Initialize();

				curScene->AddGameObject(right, eLayerType::EnemyBullet);
				right->Initialize();


				
			}
		}
	}
	void Boss2Creator::OnCollisionStay(Collider* other)
	{
	}
	void Boss2Creator::OnCollisionExit(Collider* other)
	{
	}
}