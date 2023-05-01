#include "moTitleScene.h"
#include "moInput.h"
#include "moSceneManager.h"
#include"moCollisionManager.h"
#include "moTitleBG.h"
#include "moObject.h"
#include "moCamera.h"
#include "moResources.h"
#include "moSound.h"

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
		titleBGM = Resources::Load<Sound>(L"titleSound", L"..\\Resources\\Sound\\titleSound.wav");


		TitleBG* titleBG = new TitleBG();
		AddGameObject(titleBG, eLayerType::BG1);

		Scene::Initialize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::D))
		{
			Camera::RestartFadeIn();
			SceneManager::LoadScene(eSceneType::SelectPlayer);
		}

		Scene::Update();

	}
	void TitleScene::Render(HDC mHdc)
	{
		Scene::Render(mHdc);
	}
	void TitleScene::OnEnter()
	{
		titleBGM->Play(false);
	}
	void TitleScene::OnExit()
	{
		CollisionManager::Clear();
	}
}
