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
		Vector2 pos = Camera::GetLookPosition();
		pos += Vector2(0.0f, 133.0f);
		Camera::SetLookPosition(pos);



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
		AddGameObject(mission1BG, eLayerType::BG);

		MachinegunBox* M_Box = new MachinegunBox();
		AddGameObject(M_Box, eLayerType::BulletBox);

		ArabianCreator* aCreator = new ArabianCreator(marco);
		AddGameObject(aCreator, eLayerType::EnemyCreator);

		CamelArabianCreator* camelCreator = new CamelArabianCreator(marco);
		AddGameObject(camelCreator, eLayerType::EnemyCreator);

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
		Vector2 pos = Camera::GetLookPosition();

		if (pos.x >= 3100.0f
			&& pos.y >= 455.0f
			&& Camera::GetIsMove)
		{
			pos.y--;
			Camera::SetLookPosition(pos);
		}

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

		CollisionManager::SetLayer(eLayerType::EnemyR, eLayerType::PlayerKnife, true);
		CollisionManager::SetLayer(eLayerType::EnemyR, eLayerType::PlayerBomb, true);
		CollisionManager::SetLayer(eLayerType::EnemyR, eLayerType::PlayerMachinegun, true);
		CollisionManager::SetLayer(eLayerType::EnemyR, eLayerType::PlayerPistol, true);

		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::PlayerKnife, true);
		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::PlayerBomb, true);
		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::PlayerMachinegun, true);
		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::PlayerPistol, true);


	}
	void Mission1Scene::OnExit()
	{
		CollisionManager::Clear();
	}
}
