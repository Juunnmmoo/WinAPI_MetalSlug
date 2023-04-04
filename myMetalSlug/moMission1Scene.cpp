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

		Marco* marco = new Marco(marcoBottom);
		Paraglider* paraglider = new Paraglider(marco);
		AddGameObject(paraglider, eLayerType::Player);
		AddGameObject(marco, eLayerType::Player);

		Mission1BG* mission1BG = new Mission1BG(this);
		AddGameObject(mission1BG, eLayerType::BG);

		MachinegunBox* M_Box = new MachinegunBox();
		AddGameObject(M_Box, eLayerType::BulletBox);

		ArabianCreator* aCreator = new ArabianCreator(marco);
		AddGameObject(aCreator, eLayerType::EnemyCreator);

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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Enemy, true);
		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::Bullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BulletBox, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::EnemyCreator, true);

	}
	void Mission1Scene::OnExit()
	{
		CollisionManager::Clear();
	}
}
