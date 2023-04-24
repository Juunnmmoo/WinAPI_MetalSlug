#include "moMissionStart.h"
#include "moAnimator.h"
#include "momoEngine.h"
#include "moObject.h"
#include "moTransform.h"
#include "moResources.h"
#include "moImage.h"
#include "moCharUI.h"
#include "moTime.h"
#include "moSceneManager.h"
#include "moScene.h"
namespace mo {
	MissionStart::MissionStart(eSceneType type)
		:mTime(0.0f)
		,charNum(0)
	{
	}
	MissionStart::~MissionStart()
	{
	}
	void MissionStart::Initialize()
	{
		GameObject::Initialize();
	}
	void MissionStart::Update()
	{
		mTime += Time::DeltaTime();

		if (mTime >= 0.15f)
		{
			curScene = SceneManager::GetActiveScene();
			mTime = 0.0f;


			if (charNum == 0)
			{
				CharUI* ui1 = new CharUI(eCharType::M, Vector2(150.0f, 150.0f), Vector2(3.0f, 3.0));
				curScene->AddGameObject(ui1, eLayerType::UI2);
				ui1->SetName(L"m");
				ui1->Initialize();
				ui1->GetAnimator()->Play(L"M_B", false);
				ui1->PlayStartAnimation(2.8f, Vector2(-3.0f, -1.0f));
			}
			else if (charNum == 1)
			{
				CharUI* ui2= new CharUI(eCharType::I, Vector2(250.0f, 150.0f), Vector2(3.0f, 3.0));
				curScene->AddGameObject(ui2, eLayerType::UI2);
				ui2->SetName(L"i");
				ui2->Initialize();
				ui2->GetAnimator()->Play(L"I_B", false);
				ui2->PlayStartAnimation(2.6f, Vector2(-2.0f, -1.0f));
			}
			else if (charNum == 2)
			{
				CharUI* ui3 = new CharUI(eCharType::S, Vector2(350.0f, 150.0f), Vector2(3.0f, 3.0));
				curScene->AddGameObject(ui3, eLayerType::UI2);
				ui3->SetName(L"s");
				ui3->Initialize();
				ui3->GetAnimator()->Play(L"S_B", false);
				ui3->PlayStartAnimation(2.4f, Vector2(-1.0f, -1.0f));
			}
			else if (charNum == 3)
			{
				CharUI* ui4 = new CharUI(eCharType::S, Vector2(450.0f, 150.0f), Vector2(3.0f, 3.0));
				curScene->AddGameObject(ui4, eLayerType::UI2);
				ui4->Initialize();
				ui4->GetAnimator()->Play(L"S_B", false);
				ui4->PlayStartAnimation(2.2f, Vector2(0.0f, -1.0f));
			}
			
			else if (charNum == 4)
			{
				CharUI* ui5 = new CharUI(eCharType::I, Vector2(550.0f, 150.0f), Vector2(3.0f, 3.0));
				curScene->AddGameObject(ui5, eLayerType::Effect);
				ui5->Initialize();
				ui5->GetAnimator()->Play(L"I_B", false);
				ui5->PlayStartAnimation(2.0f, Vector2(1.0f, -1.0f));
			}
			else if (charNum == 5)
			{
				CharUI* ui6 = new CharUI(eCharType::O, Vector2(650.0f, 150.0f), Vector2(3.0f, 3.0));
				curScene->AddGameObject(ui6, eLayerType::Effect);
				ui6->Initialize();
				ui6->GetAnimator()->Play(L"O_B", false);
				ui6->PlayStartAnimation(1.8f, Vector2(2.0f, -1.0f));
			}
			else if (charNum == 6)
			{
				CharUI* ui7 = new CharUI(eCharType::N, Vector2(750.0f, 150.0f), Vector2(3.0f, 3.0));
				curScene->AddGameObject(ui7, eLayerType::Effect);
				ui7->Initialize();
				ui7->GetAnimator()->Play(L"N_B", false);
				ui7->PlayStartAnimation(1.6f, Vector2(3.0f, -1.0f));
			}
			else if (charNum == 7)
			{
				CharUI* ui8 = new CharUI(eCharType::S, Vector2(200.0f, 300.0f), Vector2(3.0f, 3.0));
				curScene->AddGameObject(ui8, eLayerType::Effect);
				ui8->Initialize();
				ui8->GetAnimator()->Play(L"S_B", false);
				ui8->PlayStartAnimation(1.4f, Vector2(-3.0f, 1.0f));
			}
			else if (charNum == 8)
			{
				CharUI* ui9 = new CharUI(eCharType::T, Vector2(300.0f, 300.0f), Vector2(3.0f, 3.0));
				curScene->AddGameObject(ui9, eLayerType::Effect);
				ui9->Initialize();
				ui9->GetAnimator()->Play(L"T_B", false);
				ui9->PlayStartAnimation(1.2f, Vector2(-2.0f, 1.0f));
			}
			else if (charNum == 9)
			{
				CharUI* ui10 = new CharUI(eCharType::A, Vector2(400.0f, 300.0f), Vector2(3.0f, 3.0));
				curScene->AddGameObject(ui10, eLayerType::Effect);
				ui10->Initialize();
				ui10->GetAnimator()->Play(L"A_B", false);
				ui10->PlayStartAnimation(1.0f, Vector2(-1.0f, 1.0f));
			}
			else if (charNum == 10)
			{
				CharUI* ui11 = new CharUI(eCharType::R, Vector2(500.0f, 300.0f), Vector2(3.0f, 3.0));
				curScene->AddGameObject(ui11, eLayerType::Effect);
				ui11->Initialize();
				ui11->GetAnimator()->Play(L"R_B", false);
				ui11->PlayStartAnimation(0.8f, Vector2(1.0f, 1.0f));
			}
			else if (charNum == 11)
			{
				CharUI* ui12 = new CharUI(eCharType::T, Vector2(600.0f, 300.0f), Vector2(3.0f, 3.0));
				curScene->AddGameObject(ui12, eLayerType::Effect);
				ui12->Initialize();
				ui12->GetAnimator()->Play(L"T_B", false);
				ui12->PlayStartAnimation(0.6f, Vector2(2.0f,1.0f));
			}
			else if (charNum == 12)
			{
				CharUI* ui13 = new CharUI(eCharType::ExclamationMark, Vector2(750.0f, 300.0f), Vector2(3.0f, 3.0));
				curScene->AddGameObject(ui13, eLayerType::Effect);
				ui13->Initialize();
				ui13->GetAnimator()->Play(L"!_B", false);
				ui13->PlayStartAnimation(0.4f, Vector2(3.0f, 3.0f));
			}
			
			charNum++;
		}

		GameObject::Update();
	}
	void MissionStart::Render(HDC mHdc)
	{
		GameObject::Render(mHdc);
	}
}