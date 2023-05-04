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
#include "moRebelTruckCreator.h"
#include "moMissionStart.h"
#include "moCharUI.h"
#include "moArmsUI.h"
#include "moBoss1_Base.h"
#include "moBoss1_Missile.h"
#include "moArabianFighter.h"
#include "moSound.h"
#include "moSoundManager.h"
#include "moResources.h"
#include "moBoss2_Base.h"
#include "moBoss1Creator.h"
#include "moBoss2Creator.h"

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
		mission1BGM = Resources::Load<Sound>(L"missionBGM", L"..\\Resources\\Sound\\mission1BGM.wav");
		missionStart = Resources::Load<Sound>(L"mission1Start", L"..\\Resources\\Sound\\mission1Start.wav");

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

		ArabianCreator* aCreator1 = new ArabianCreator(marco, Vector2(500.0f, 0.0f), Vector2(700.0f, 750.0f), Vector2(2100.0f, 200.0f));
		AddGameObject(aCreator1, eLayerType::EnemyCreator);

		ArabianCreator* aCreator2 = new ArabianCreator(marco, Vector2(900.0f, 0.0f), Vector2(900.0f, 750.0f), Vector2(2700.0f, 500.0f));
		AddGameObject(aCreator2, eLayerType::EnemyCreator);
		
		ArabianCreator* aCreator3 = new ArabianCreator(marco, Vector2(1300.0f, 0.0f), Vector2(700.0f, 750.0f), Vector2(2750.0f, 100.0f));
		AddGameObject(aCreator3, eLayerType::EnemyCreator);

		/*ArabianCreator* aCreator4 = new ArabianCreator(marco, Vector2(2200.0f, 0.0f), Vector2(600.0f, 750.0f), Vector2(3600.0f, 500.0f));
		AddGameObject(aCreator4, eLayerType::EnemyCreator);		*/

		ArabianCreator* aCreator5 = new ArabianCreator(marco, Vector2(2400.0f, 0.0f), Vector2(700.0f, 750.0f), Vector2(3800.0f, 500.0f));
		AddGameObject(aCreator5, eLayerType::EnemyCreator);

		ArabianCreator* aCreator6 = new ArabianCreator(marco, Vector2(3900.0f, 0.0f), Vector2(700.0f, 750.0f), Vector2(5500.0f, 500.0f));
		AddGameObject(aCreator6, eLayerType::EnemyCreator);

		ArabianCreator* aCreator7 = new ArabianCreator(marco, Vector2(2400.0f, 0.0f), Vector2(700.0f, 750.0f), Vector2(3800.0f, 500.0f));
		AddGameObject(aCreator7, eLayerType::EnemyCreator);

		Arabian* arabian1 = new Arabian(marco, this, Arabian::eArabianState::Idle);
		AddGameObject(arabian1, eLayerType::EnemyR_F);
		arabian1->GetComponent<Transform>()->SetPos(Vector2(2250.0f, 0.0f));

		Arabian* arabian2 = new Arabian(marco, this, Arabian::eArabianState::Idle);
		AddGameObject(arabian2, eLayerType::EnemyR_F);
		arabian2->GetComponent<Transform>()->SetPos(Vector2(4600.0f, 0.0f));

		Arabian* arabian4 = new Arabian(marco, this, Arabian::eArabianState::Idle);
		AddGameObject(arabian4, eLayerType::EnemyR_F);
		arabian4->GetComponent<Transform>()->SetPos(Vector2(4900.0f, 0.0f));

		Arabian* arabian3 = new Arabian(marco, this, Arabian::eArabianState::Idle);
		AddGameObject(arabian3, eLayerType::EnemyR_F);
		arabian3->GetComponent<Transform>()->SetPos(Vector2(5500.0f, 0.0f));	

		CamelArabianCreator* camelCreator = new CamelArabianCreator(marco);
		AddGameObject(camelCreator, eLayerType::EnemyCreator);

		RebelTruckCreator* truckCreator = new RebelTruckCreator(marco);
		AddGameObject(truckCreator, eLayerType::EnemyCreator);

		


		Slave* slave1 = new Slave(marco, this, Vector2(2200.0f, 0.0f), eMarcoWeapon::Bomb);
		AddGameObject(slave1, eLayerType::Slave);
		
		Slave* slave2 = new Slave(marco, this, Vector2(2300.0f, 600.0f), eMarcoWeapon::Shotgun);
		AddGameObject(slave2, eLayerType::Slave);

		Slave* slave3 = new Slave(marco, this, Vector2(4550.0f, 700.0f), eMarcoWeapon::Machinegun);
		AddGameObject(slave3, eLayerType::Slave);

		MissionStart* startUi = new MissionStart(eSceneType::Mission1);
		AddGameObject(startUi, eLayerType::UI);

		ArmsUI* armsUI = new ArmsUI(marco, this);
		AddGameObject(armsUI, eLayerType::UI);

		Slave* slave4 = new Slave(marco, this, Vector2(6700.0f, 700.0f), eMarcoWeapon::Machinegun);
		AddGameObject(slave4, eLayerType::Slave);
		
		Boss1Creator* boss1Creator = new Boss1Creator(marco);
		AddGameObject(boss1Creator, eLayerType::EnemyCreator);

		Boss2Creator* boss2Creator = new Boss2Creator(marco, mission1BGM);
		AddGameObject(boss2Creator, eLayerType::EnemyCreator);

		Slave* slave5 = new Slave(marco, this, Vector2(12000.0f, 700.0f), eMarcoWeapon::Machinegun);
		AddGameObject(slave5, eLayerType::Slave);
		//CharUI* ui = new CharUI(eCharType::M, Vector2(200.0f, 300.0f), Vector2(1.5f, 1.5f));
		//AddGameObject(ui, eLayerType::UI);


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
		mission1BGM->Play(true);
		missionStart->Play(false);

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

		CollisionManager::SetLayer(eLayerType::EnemyR_F, eLayerType::PlayerKnife, true);
		CollisionManager::SetLayer(eLayerType::EnemyR_F, eLayerType::PlayerBomb, true);
		CollisionManager::SetLayer(eLayerType::EnemyR_F, eLayerType::PlayerMachinegun, true);
		CollisionManager::SetLayer(eLayerType::EnemyR_F, eLayerType::PlayerPistol, true);

		CollisionManager::SetLayer(eLayerType::Enemy_F, eLayerType::PlayerKnife, true);
		CollisionManager::SetLayer(eLayerType::Enemy_F, eLayerType::PlayerBomb, true);
		CollisionManager::SetLayer(eLayerType::Enemy_F, eLayerType::PlayerMachinegun, true);
		CollisionManager::SetLayer(eLayerType::Enemy_F, eLayerType::PlayerPistol, true);

		CollisionManager::SetLayer(eLayerType::EnemyBullet, eLayerType::PlayerBomb, true);
		CollisionManager::SetLayer(eLayerType::EnemyBullet, eLayerType::PlayerMachinegun, true);
		CollisionManager::SetLayer(eLayerType::EnemyBullet, eLayerType::PlayerPistol, true);
	}
	void Mission1Scene::OnExit()
	{
		mission1BGM->Stop(true);

		CollisionManager::Clear();
	}
}
