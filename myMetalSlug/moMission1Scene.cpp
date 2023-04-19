#include "moMission1Scene.h"
#include "moInput.h"
#include "moSceneManager.h"
#include "moMarco.h"
#include "moMission1BG.h"
#include "moMarcoBottom.h"
#include "moCollisionManager.h"
#include "moTransform.h"
#include "moComponent.h"
#include "moArabian.h"
#include "moObject.h"
#include "moCamera.h"
#include "moTitleBG.h"
#include "moParaglider.h"
#include "moMachinegunBox.h"
#include "moArabianCreator.h"
#include "moPlayerKnife.h"
#include "moCamelArabian01.h"
#include "moCamelArabian02.h"
#include "moCamel.h"
#include "moCamelArabianCreator.h"
#include "moSlave.h"
#include "moRebelTruck1.h"
#include "moRebelTruck2.h"

namespace mo
{
	Mission1Scene::Mission1Scene()
	{
	}
	Mission1Scene::~Mission1Scene()
	{
	}
	void Mission1Scene::Initialize()
	{

		MarcoBottom* marcoBottom = new MarcoBottom();
		AddGameObject(marcoBottom, eLayerType::Player);

		PlayerKnife* rightKnife = new PlayerKnife();
		PlayerKnife* leftKnife = new PlayerKnife();
		AddGameObject(rightKnife, eLayerType::PlayerKnife);
		AddGameObject(leftKnife, eLayerType::PlayerKnife);

		Marco* marco = new Marco(marcoBottom, rightKnife, leftKnife);
		Paraglider* paraglider = new Paraglider(marco);
		AddGameObject(paraglider, eLayerType::Player);
		AddGameObject(marco, eLayerType::Player);

		Mission1BG* mission1BG = new Mission1BG(this);
		AddGameObject(mission1BG, eLayerType::BG1);

		ArabianCreator* aCreator1 = new ArabianCreator(marco, Vector2(700.0f, 0.0f), Vector2(700.0f, 750.0f), Vector2(2200.0f, 200.0f));
		AddGameObject(aCreator1, eLayerType::EnemyCreator);

		ArabianCreator* aCreator2 = new ArabianCreator(marco, Vector2(900.0f, 0.0f), Vector2(900.0f, 750.0f), Vector2(2600.0f, 500.0f));
		AddGameObject(aCreator2, eLayerType::EnemyCreator);
		
		ArabianCreator* aCreator3 = new ArabianCreator(marco, Vector2(1600.0f, 0.0f), Vector2(900.0f, 750.0f), Vector2(3400.0f, 500.0f));
		AddGameObject(aCreator3, eLayerType::EnemyCreator);

		ArabianCreator* aCreator4 = new ArabianCreator(marco, Vector2(2200.0f, 0.0f), Vector2(600.0f, 750.0f), Vector2(3600.0f, 500.0f));
		AddGameObject(aCreator4, eLayerType::EnemyCreator);

		CamelArabianCreator* camelCreator = new CamelArabianCreator(marco);
		AddGameObject(camelCreator, eLayerType::EnemyCreator);

		RebelTruck2* truck2 = new RebelTruck2();
		AddGameObject(truck2, eLayerType::front);

		RebelTruck1* truck1 = new RebelTruck1(marco, truck2, this, Vector2(800.0f, 0.0f));
		AddGameObject(truck1, eLayerType::Enemy);


		Slave* slave1 = new Slave(marco, this, Vector2(2200.0f, 0.0f), eMarcoWeapon::Machinegun);
		AddGameObject(slave1, eLayerType::Slave);
		
		Slave* slave2 = new Slave(marco, this, Vector2(2300.0f, 600.0f), eMarcoWeapon::Machinegun);
		AddGameObject(slave2, eLayerType::Slave);
		//MachinegunBox* M_Box = new MachinegunBox();
		//AddGameObject(M_Box, eLayerType::BulletBox);

		/*Camel* camel = new Camel();
		CamelArabian02* camelArabian02 = new CamelArabian02();
		CamelArabian01* camelArabian01 = new CamelArabian01(marco, camel, camelArabian02, this);

		AddGameObject(camelArabian01, eLayerType::Enemy);
		AddGameObject(camel, eLayerType::Enemy);
		AddGameObject(camelArabian02, eLayerType::Enemy);*/




		mission1BG->SetPlayer(marco);

		Camera::SetTarget(marco);

		Scene::Initialize();

	}
	void Mission1Scene::Update()
	{
		

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		Scene::Update();

	}
	void Mission1Scene::Render(HDC mHdc)
	{
		Scene::Render(mHdc);

	}
	void Mission1Scene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::EnemyBullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::EnemyBulletR, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BulletBox, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::EnemyCreator, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Slave, true);


		CollisionManager::SetLayer(eLayerType::EnemyR, eLayerType::PlayerKnife, true);
		CollisionManager::SetLayer(eLayerType::EnemyR, eLayerType::PlayerBomb, true);
		CollisionManager::SetLayer(eLayerType::EnemyR, eLayerType::PlayerMachinegun, true);
		CollisionManager::SetLayer(eLayerType::EnemyR, eLayerType::PlayerPistol, true);

		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::PlayerKnife, true);
		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::PlayerBomb, true);
		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::PlayerMachinegun, true);
		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::PlayerPistol, true);

		CollisionManager::SetLayer(eLayerType::Slave, eLayerType::PlayerKnife, true);
		CollisionManager::SetLayer(eLayerType::Slave, eLayerType::PlayerShotgun, true);
		CollisionManager::SetLayer(eLayerType::Slave, eLayerType::PlayerFiregun, true);
		CollisionManager::SetLayer(eLayerType::Slave, eLayerType::PlayerMachinegun, true);
		CollisionManager::SetLayer(eLayerType::Slave, eLayerType::PlayerPistol, true);

	}
	void Mission1Scene::OnExit()
	{
		CollisionManager::Clear();
	}
}
