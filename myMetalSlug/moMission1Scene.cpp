#include "moMission1Scene.h"
#include "moInput.h"
#include "moSceneManager.h"
#include "moMarco.h"

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
		Marco* marco = new Marco();
		addGameObject(marco, eLayerType::Player);

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
	}
	void Mission1Scene::OnExit()
	{
	}
}
