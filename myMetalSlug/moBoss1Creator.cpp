#include "moBoss1Creator.h"
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
#include "moBoss1_Attackor.h"
#include "moBoss1_Base.h"
#include "moBoss1_CurtainIdle.h"
#include "moBoss1_CurtainOpen.h"
#include "moBoss1_Missile.h"
#include "moBoss1_towrd.h"
#include "moBoss1_WindowOpen.h"

namespace mo {
	Boss1Creator::Boss1Creator(Marco* marco)
		:player(marco)
	{
	}
	Boss1Creator::~Boss1Creator()
	{
	}
	void Boss1Creator::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(5200.0f, 0.0f));

		Collider* mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2{ 20.0f, 750.0f });

		GameObject::Initialize();
	}
	void Boss1Creator::Update()
	{
		GameObject::Update();

	}
	void Boss1Creator::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);

	}
	void Boss1Creator::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			if (!stopCreate)
			{
				stopCreate = true;

				Scene* curScene = SceneManager::GetActiveScene();

				ArabianFighter* fighter1 = new ArabianFighter(player, Vector2(5600.0f, 0.0f), 1, ArabianFighter::eArabianFighterState::Idle);
				curScene->AddGameObject(fighter1, eLayerType::EnemyR_F);
				fighter1->Initialize();
				fighter1->GetComponent<Transform>()->SetPos(Vector2(7300.0f, 0.0f));

				ArabianFighter* fighter12 = new ArabianFighter(player, Vector2(5660.0f, 0.0f), 2, ArabianFighter::eArabianFighterState::Idle);
				curScene->AddGameObject(fighter12, eLayerType::EnemyR_F);
				fighter12->Initialize();
				fighter12->GetComponent<Transform>()->SetPos(Vector2(7360.0f, 0.0f));

				ArabianFighter* fighter3 = new ArabianFighter(player, Vector2(5720.0f, 0.0f), 2, ArabianFighter::eArabianFighterState::Idle);
				curScene->AddGameObject(fighter3, eLayerType::EnemyR_F);
				fighter3->Initialize();
				fighter3->GetComponent<Transform>()->SetPos(Vector2(7420.0f, 0.0f));


				Boss1_Towrd* mLeftTowrd = new Boss1_Towrd(player, curScene, mo::Boss1_Towrd::TowrdDir::Left);
				Boss1_Towrd* mRightTowrd = new Boss1_Towrd(player, curScene, mo::Boss1_Towrd::TowrdDir::Middle);
				Boss1_Towrd* mMiddleTowrd = new Boss1_Towrd(player, curScene, mo::Boss1_Towrd::TowrdDir::Right);
				Boss1_Base* boss_Base = new Boss1_Base(player, curScene, mLeftTowrd, mMiddleTowrd, mRightTowrd, fighter3);
			
				curScene->AddGameObject(boss_Base, eLayerType::front);
				boss_Base->Initialize();

				curScene->AddGameObject(mLeftTowrd, eLayerType::BG1);
				mLeftTowrd->GetComponent<Transform>()->SetPos(Vector2(6950.0f, 730.0f) + Vector2(-160.0f, -250.0f));
				mLeftTowrd->Initialize();

				curScene->AddGameObject(mRightTowrd, eLayerType::BG1);
				mRightTowrd->GetComponent<Transform>()->SetPos(Vector2(6950.0f, 730.0f) + Vector2(130.0f, -250.0f));
				mRightTowrd->Initialize();

				curScene->AddGameObject(mMiddleTowrd, eLayerType::BG1);
				mMiddleTowrd->GetComponent<Transform>()->SetPos(Vector2(6950.0f, 730.0f) + Vector2(440.0f, -250.0f));
				mMiddleTowrd->Initialize();
				
				






				

			}
		}
	}
	void Boss1Creator::OnCollisionStay(Collider* other)
	{
	}
	void Boss1Creator::OnCollisionExit(Collider* other)
	{
	}
}