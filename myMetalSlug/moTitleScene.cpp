#include "moTitleScene.h"
#include "moInput.h"
#include "moSceneManager.h"
#include"moCollisionManager.h"
#include "moTitleBG.h"

namespace mo
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		TitleBG* titleBG = new TitleBG();
		AddGameObject(titleBG, eLayerType::BG03);

		Scene::Initialize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Mission1);
		}
		Scene::Update();

	}
	void TitleScene::Render(HDC mHdc)
	{
		Scene::Render(mHdc);
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
		CollisionManager::Clear();
	}
}
