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
#include "moParaglider.h";

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

		Marco* marco = new Marco(marcoBottom);
		

		Arabian* arabian = new Arabian(Vector2(1200.0f, 700.0f));
		AddGameObject(arabian, eLayerType::Monster);

		Mission1BG* mission1BG = new Mission1BG();
		AddGameObject(mission1BG, eLayerType::BG03);

		Paraglider* paraglider = new Paraglider(marco);
		AddGameObject(paraglider, eLayerType::Player);
		AddGameObject(marco, eLayerType::Player);

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

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);

		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Bullet, true);
	}
	void Mission1Scene::OnExit()
	{
		CollisionManager::Clear();
	}
}
