#include "moSelectScene.h"
#include "moInput.h"
#include "moSceneManager.h"
#include"moCollisionManager.h"
#include "moSelectBG.h"
#include "moSelectElevator.h"
#include "moSelectCharacters.h"
#include "moObject.h"
#include "moCamera.h"
#include "moTime.h"


namespace mo {
	SelectScene::SelectScene()
		: selectNum(1)
		, charactor1(nullptr)
		, charactor2(nullptr)
		, charactor3(nullptr)
		, charactor4(nullptr)
		, elevator1(nullptr)
		, elevator2(nullptr)
		, elevator3(nullptr)
		, elevator4(nullptr)
		, time(0.0f)
	{
	}
	SelectScene::~SelectScene()
	{
	}
	void SelectScene::Initialize()
	{
		elevator1 = new SelectElevator(Vector2(84.0f, 221.0f), 0.5f);
		AddGameObject(elevator1, eLayerType::BG2);
		elevator2 = new SelectElevator(Vector2(84.0f + (235 * 1), 221.0f), 1.0f);
		AddGameObject(elevator2, eLayerType::BG2);

		elevator3 = new SelectElevator(Vector2(84.0f + (235 * 2), 221.0f), 0.7f);
		AddGameObject(elevator3, eLayerType::BG2);

		elevator4 = new SelectElevator(Vector2(84.0f + (235 * 3), 221.0f), 1.3f);
		AddGameObject(elevator4, eLayerType::BG2);

		charactor1 = new SelectCharactor(Vector2(84.0f, 221.0f), Vector2(223.0f * 0, 0.0f));
		AddGameObject(charactor1, eLayerType::BG1);

		charactor2 = new SelectCharactor(Vector2(84.0f + (235 * 1), 221.0f), Vector2((223.0f * 1), 0.0f));
		AddGameObject(charactor2, eLayerType::BG1);

		charactor3 = new SelectCharactor(Vector2(84.0f + (235 * 2), 221.0f), Vector2((223.0f * 2), 0.0f));
		AddGameObject(charactor3, eLayerType::BG1);

		charactor4 = new SelectCharactor(Vector2(84.0f + (235 * 3), 221.0f), Vector2((223.0f * 3) , 0.0f));
		AddGameObject(charactor4, eLayerType::BG1);



		SelectBG* selectBG = new SelectBG();
		AddGameObject(selectBG, eLayerType::BG3);

		

		Scene::Initialize();

	}
	void SelectScene::Update()
	{
		if (!SceneChange)
		{
			if (selectNum == 1)
			{
				charactor1->SetImagePos(Vector2(223.0f * 0, 418.0f * 1));
				charactor2->SetImagePos(Vector2(223.0f * 1, 418.0f * 0));
				charactor3->SetImagePos(Vector2(223.0f * 2, 418.0f * 0));
				charactor4->SetImagePos(Vector2(223.0f * 3, 418.0f * 0));

			}
			else if (selectNum == 2)
			{
				charactor1->SetImagePos(Vector2(223.0f * 0, 418.0f * 0));
				charactor2->SetImagePos(Vector2(223.0f * 1, 418.0f * 1));
				charactor3->SetImagePos(Vector2(223.0f * 2, 418.0f * 0));
				charactor4->SetImagePos(Vector2(223.0f * 3, 418.0f * 0));
			}
			else if (selectNum == 3)
			{
				charactor1->SetImagePos(Vector2(223.0f * 0, 418.0f * 0));
				charactor2->SetImagePos(Vector2(223.0f * 1, 418.0f * 0));
				charactor3->SetImagePos(Vector2(223.0f * 2, 418.0f * 1));
				charactor4->SetImagePos(Vector2(223.0f * 3, 418.0f * 0));
			}
			else if (selectNum == 4)
			{
				charactor1->SetImagePos(Vector2(223.0f * 0, 418.0f * 0));
				charactor2->SetImagePos(Vector2(223.0f * 1, 418.0f * 0));
				charactor3->SetImagePos(Vector2(223.0f * 2, 418.0f * 0));
				charactor4->SetImagePos(Vector2(223.0f * 3, 418.0f * 1));
			}
		}

		if (Input::GetKeyDown(eKeyCode::Right) && selectNum < 4)
		{
			selectNum++;
		}
		if (Input::GetKeyDown(eKeyCode::Left) && selectNum > 1)
		{
			selectNum--;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			if (selectNum == 1)
			{
				charactor1->SetImagePos(Vector2(223.0f * 0, 418.0f * 2));
				elevator1->SetGoingBack();

			}
			else if (selectNum == 2)
			{
				charactor2->SetImagePos(Vector2(223.0f * 1, 418.0f * 2));
				elevator2->SetGoingBack();
			}
			else if (selectNum == 3)
			{
				charactor3->SetImagePos(Vector2(223.0f * 2, 418.0f * 2));
				elevator3->SetGoingBack();
			}
			else if (selectNum == 4)
			{
				charactor4->SetImagePos(Vector2(223.0f * 3, 418.0f * 2));
				elevator4->SetGoingBack();
			}
			SceneChange = true;
		}

		if (SceneChange)
		{
			time += Time::DeltaTime();

			if (time > 3.0f)
			{
				//Camera::RestartFadeIn();
				SceneManager::LoadScene(eSceneType::Mission1);
			}
		}

		Scene::Update();

	}
	void SelectScene::Render(HDC mHdc)
	{
		Scene::Render(mHdc);
	}
	void SelectScene::OnEnter()
	{
	}
	void SelectScene::OnExit()
	{
	}
}